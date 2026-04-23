#include <stdio.h>
#include <stdlib.h>
#include "registers.c"
#include "fetchDecodeExcute.c"
int halted=0;

void LOAD(void) {
    write_MAR(address);
    data_bus=mem_read(MAR);
    write_MBR(data_bus);
    data_bus=MBR;
    write_AC(data_bus);
}

void STORE(void) {
    data_bus=AC;
    write_MBR(data_bus);
    data_bus=MBR;
    mem_write(MAR,data_bus);
}

void ADD(void) {
    write_MAR(address);
    data_bus=mem_read(MAR);
    write_MBR(data_bus);
    data_bus=MBR;
    write_AC(AC+data_bus);
}

void Subt(void) {
    write_MAR(address);
    data_bus=mem_read(MAR);
    write_MBR(data_bus);
    data_bus=MBR;
    write_AC(AC-data_bus);
}

void JUMP(void) {
    write_PC(address);
}

void input(void) {
    printf("input: ");
    int input_value;
    scanf("%d", &input_value);
    data_bus = input_value;
    write_AC(data_bus);
}

void output(void) {
    data_bus = AC;
    printf("output: %d\n", data_bus);
}
 
void HALT(void) {
    halted=1;
    exit(0);
}

void ADDI(void) {
    
}
