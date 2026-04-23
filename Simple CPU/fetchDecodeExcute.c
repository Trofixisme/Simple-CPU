#include<stdio.h>
#include "registers.c"
int opcode = 0;
int address = 0;

void fetch(void) {
    
    write_MAR(PC);
    
    data_bus = mem_read(MAR);
    
    write_IR(data_bus);
    write_PC(PC + 1);
}

void decode(void) {
    
    opcode = (IR >> 12) & 0xF;
    address = IR & 0x0FFF;
    
}