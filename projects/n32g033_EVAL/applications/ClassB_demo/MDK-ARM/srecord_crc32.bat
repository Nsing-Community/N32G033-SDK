.\SREC\srec_cat .\Objects\SelfTest.hex -intel -crop 0x08000000 0x0800FF00 -fill 0x00 0x08000000 0x0800FF00 ^
-crc32-l-e 0x0800FF00 -o .\Objects\SelfTest_CRC.hex -intel
