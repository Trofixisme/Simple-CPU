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
    
}

void ADDI(void) {
    
}

void SUBTI(void) {
    
}

void STOREI(void) {

}

void LOADI(void) {

}
