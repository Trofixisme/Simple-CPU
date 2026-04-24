#include <stdio.h>
#include "registers.h"
#include "instructions.h"

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
    write_MAR(IR & 0x0FFF);
    
}

void execute(void) {
    
    switch (opcode) {
        case 0x1:
            LOAD();
            break;
        case 0x2:
            STORE();
            break;
        case 0x3:
            ADD();
            break;
        case 0x4:
            SUBT();
            break;
        case 0x5:
            IN();
            break;
        case 0x6:
            OUT();
            break;
        case 0x7:
            HALT();
            break;
        case 0x8:
            SKIPCOND();
            break;
        case 0x9:
            JUMP();
            break;
        case 0xA:
            CLEAR();
            break;
    }
}
