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
    address = IR & 0x0FFF;
    
}

void execute(void) {
    
    switch (opcode) {
    case 1:
        LOAD();
        break;
    case 2:
        STORE();
        break;
    case 3:
        ADD();
        break;
    case 4:
        SUBT();
        break;
    }
}
