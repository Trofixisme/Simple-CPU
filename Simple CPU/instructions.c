#include <stdio.h>
#include <stdlib.h>
#include "registers.h"
#include "fetchDecodeExecute.h"

int halted = 0;

void LOAD(void) {
    
    data_bus = mem_read(MAR);
    write_MBR(data_bus);
    
    data_bus = MBR;
    write_AC(data_bus);
}

void STORE(void) {
    
    data_bus = AC;
    write_MBR(data_bus);
    
    data_bus = MBR;
    mem_write(MAR, data_bus);
}

void ADD(void) {
    
    data_bus = mem_read(MAR);
    write_MBR(data_bus);
    
    data_bus = MBR;
    write_AC(AC + data_bus);
}

void SUBT(void) {
    
    data_bus = mem_read(MAR);
    write_MBR(data_bus);
    
    data_bus = MBR;
    write_AC(AC - data_bus);
}

void JUMP(void) {
    write_PC(MAR);
}

void IN(void) {
    printf("input: ");
    
    int temp;
    scanf("%d", &temp);
    
    data_bus = temp;
    write_InREG(temp);
    data_bus = InREG;
    
    write_AC(data_bus);
}

void OUT(void) {
    
    data_bus = AC;
    write_OutREG(data_bus);
    
    printf("Output: %d\n", OutREG);
}

void HALT(void) {
    halted = 1;
}

void CLEAR(void) {
    write_AC(0);
}

void SKIPCOND(void) {
   
    // MAR holds the condition code set during decode
    if      (MAR == 0x000 && AC < 0)  write_PC(PC + 1);
    else if (MAR == 0x400 && AC == 0) write_PC(PC + 1);
    else if (MAR == 0x800 && AC > 0)  write_PC(PC + 1);

}
void ADDI(void) {
    // indirect: address field points to address that holds the real address
    data_bus = mem_read(MAR);
    write_MAR(data_bus);          // follow the pointer
    data_bus = mem_read(MAR);
    write_MBR(data_bus);
    write_AC(MASK16(AC + MBR));
}

void LOADI(void) {
    data_bus = mem_read(MAR);
    write_MAR(data_bus);
    data_bus = mem_read(MAR);
    write_MBR(data_bus);
    write_AC(MBR);
}

void STOREI(void) {
    data_bus = mem_read(MAR);
    write_MAR(data_bus);
    data_bus = AC;
    write_MBR(data_bus);
    mem_write(MAR, MBR);
}



void SUBTI(void) {
     // indirect: address field points to address that holds the real address
    data_bus = mem_read(MAR);
    write_MAR(data_bus);          // follow the pointer
    data_bus = mem_read(MAR);
    write_MBR(data_bus);
    write_AC(MASK16(AC - MBR));
}

void JUMPI(void) {
    data_bus = mem_read(MAR);
    write_PC(data_bus);
}