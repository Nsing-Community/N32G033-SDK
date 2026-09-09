;/**
  ;**************************************************************************
  ;* File   : n32_cm0_STLcpustartKEIL.s
  ;* Version: V1.0.0
  ;* Date   : 2024-04-25
  ;* Brief  : This file contains procedures written in assembler for full
  ;           and partial transparent Marching RAM tests to be called during
  ;           start-up and run time
  ;**************************************************************************
  ;*/

   THUMB
  REQUIRE8
  PRESERVE8

  AREA |.text|, CODE, READONLY, ALIGN=2

  ; Reference to the FailSafe routine to be executed in case of non-recoverable
  ; failure									
  IMPORT FailSafePOR

    ; C variables for control flow monitoring
  IMPORT CtrlFlowCnt
  IMPORT CtrlFlowCntInv

;*******************************************************************************
; Function Name  : STL_StartUpCPUTest
; Description    : Full Cortex-M0 CPU test at start-up
;                  Note: when possible, BRANCH are 16-bit only (depending on
;                  relative offset to final BL instruction)
; Input          : None.
; Output         : Branch directly to a Fail Safe routine in case of failure
; Return         : TEST_SUCCESSFULL (=1)
; WARNING        : all registers destroyed when exiting this function (including
;                  preserved registers R4 to R11) and excluding stack point R13)
;*******************************************************************************/
conAA       DCD     0xAAAAAAAA
con55       DCD     0x55555555
con80       DCD     0x80000000
conA8       DCD     0xAAAAAAA8
con54       DCD     0x55555554

  EXPORT conAA
  EXPORT con55
      
STL_StartUpCPUTest PROC
    EXPORT STL_StartUpCPUTest

    PUSH {R4-R7}              ; Safe critical registers

    ; Register R0 
    ; Immediate permitted values are 0x00 to 0xFF
    LDR R0, =0x55000000
    LSRS R0, R0, #24
    CMP R0, #0x55
    BNE CPUTestFail

    LDR R0, =0xAA000000
    LSRS R0, R0, #24
    CMP R0, #0xAA
    BNE CPUTestFail

    LDR R0, =0x00550000
    LSRS R0, R0, #16
    CMP R0, #0x55
    BNE CPUTestFail

    LDR R0, =0x00AA0000
    LSRS R0, R0, #16
    CMP R0, #0xAA
    BNE CPUTestFail

    LDR R0, =0x00005500
    LSRS R0, R0, #8
    CMP R0, #0x55
    BNE CPUTestFail

    LDR R0, =0x0000AA00
    LSRS R0, R0, #8
    CMP R0, #0xAA
    BNE CPUTestFail

    MOVS R0, #0xA5
    CMP R0, #0xA5
    BNE CPUTestFail  

   	; This is for control flow test (ENTRY point)
	LDR R0,=CtrlFlowCnt
	; Assumes R1 OK; If not, error will be detected by R1 test and Ctrl flow test later on
	LDR R1,[R0]
	ADDS R1,R1,#0x3	 ; CtrlFlowCnt += 0x03
	STR R1,[R0]
    
    ; Register R1
    LDR R0, =conAA
	LDR R1,[R0]
    LDR R0,[R0]
    CMP R0,R1
    BNE CPUTestFail
    LDR R0, =con55
	LDR R1,[R0]
    LDR R0,[R0]
    CMP R0,R1
    BNE CPUTestFail
    
    MOVS R0, #0x00      	  
	UXTB R0,R0
	ADDS R0,#0				  ; Set Z(ero) Flag
    BNE CPUTestFail           ; Fails if Z clear
    BMI CPUTestFail           ; Fails if N is set
    SUBS R0,#1                ; Set N(egative) Flag
    BPL CPUTestFail           ; Fails if N clear
    ADDS R0,#2                ; Set C(arry) Flag and do not set Z
    BCC CPUTestFail           ; Fails if C clear
    BEQ CPUTestFail           ; Fails if Z is set
    BMI CPUTestFail           ; Fails if N is set

    LDR R0,=con80      	  	  ; Prepares Overflow test
	LDR R0,[R0]
    ADDS R0, R0, R0           ; Set V(overflow) Flag
    BVC CPUTestFail           ; Fails if V clear
  
    BAL CPUTstCont

CPUTestFail
	BLAL FailSafePOR

CPUTstCont
	
    ; register PRIMASK
    MOVS R0, #0x1
    MSR PRIMASK, R0
    MRS R1, PRIMASK
    CMP R1, #0x1
    BNE CPUTestFail
    MOVS R0, #0x0
    MSR PRIMASK, R0
    MRS R1, PRIMASK
    CMP R1, #0x0
    BNE CPUTestFail
        
    ; Register R14
    MOV R0, LR             ; Contains the return address and must be saved
    LDR R1, =conAA
    MOV LR, R1
    CMP LR, R1
    BNE CPUTestFail
    LDR R1, =con55
    MOV LR, R1
    CMP LR, R1
    BNE CPUTestFail
    MOV LR, R0              ; Restore LR saved address
    
    ; Process Stack pointer (banked Register R13)
    MRS R0,PSP          ; Save process stack value
    LDR R1, =conA8      ; Test is different (PSP is word aligned, 2 LSB cleared)
    MSR PSP,R1          ; load process stack value
    MRS R2,PSP          ; Get back process stack value
    CMP R2,R1           ; Verify value
    BNE CPUTestFail
    LDR R1, =con54      ; Test is different (PSP is word aligned, 2 LSB cleared)
    MSR PSP,R1          ; load process stack value
    MRS R2,PSP          ; Get back process stack value
    CMP R2,R1           ; Verify value
    BNE CPUTestFail
    MSR PSP, R0         ; Restore process stack value

    ; Stack pointer (Register R13)
    MRS R0,MSP          ; Save stack pointer value
    LDR R1, =conA8      ; Test is different (SP is word aligned, 2 LSB cleared)
    MSR MSP,R1			; load SP value
	MRS R2,MSP			; Get back SP value
    CMP R2,R1			; Verify value
    BNE CPUTestFail
    LDR R1, =con54	
    MSR MSP,R1			; load SP value
    MRS R2,MSP			; Get back SP value
    CMP R2,R1           ; Verify value
    BNE CPUTestFail
    MSR MSP,R0			; Restore stack pointer value

  	; Control flow test (EXIT point)
	LDR R0,=CtrlFlowCntInv
	LDR R1,[R0]
	SUBS R1,R1,#0x3	    ; CtrlFlowCntInv -= 0x03
	STR R1,[R0]

	POP {R4-R7}			; Restore critical registers

    ; If next instruction is not executed, R0 will hold a value different from 0
    MOVS R0, #0x1       ; CPUTEST_SUCCESS
    BX LR               ; return to the caller

    ALIGN

	ENDP


  END


;******************* (C) COPYRIGHT  *****END OF FILE*****
