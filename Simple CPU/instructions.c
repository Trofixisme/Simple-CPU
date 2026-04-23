#include<stdio.h>
#include "registers.c"
#include "fetchDecodeExcute.c"
int halted=0;
void LOAD(){
    write_MAR(address);
    data_bus=mem_read(MAR);
    write_MBR(data_bus);
    data_bus=MBR;
    write_AC(data_bus);
}
void STORE(){
    data_bus=AC;
    write_MBR(data_bus);
    data_bus=MBR;
    mem_write(MAR,data_bus);
}
void ADD(){
    write_MAR(address);
    data_bus=mem_read(MAR);
    write_MBR(data_bus);
    data_bus=MBR;
    write_AC(AC+data_bus);
}
void Subt(){
    write_MAR(address);
    data_bus=mem_read(MAR);
    write_MBR(data_bus);
    data_bus=MBR;
    write_AC(AC-data_bus);
}
void JUMP(){
    write_PC(address);
}
void input(){
    printf("input: ");
    int input_value;
    scanf("%d", &input_value);
    data_bus = input_value;
    write_AC(data_bus);
}
void output(){
    data_bus = AC;
    printf("output: %d\n", data_bus);
}
void HALT(){
    halted=1;
    exit(0);
}
void ADDI()
{
    
}