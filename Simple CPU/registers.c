#include <stdio.h>
#define registers

#define MASK16(val) ((val)&0xFFFF)
#define MASK12(val) ((val)&0xFFFF)

// 16-bit registers
int AC = 0;
int IR = 0;
int MBR = 0;
int InREG = 0;
int OutREG = 0;

// 12-bit registers (stored in 16-bit but masked on write)
int PC = 0;
int MAR = 0;

// Data bus
int data_bus = 0;

// Memory
int memory[4096];


void write_AC(int val) {
    AC = MASK16(val);
}

void write_PC(int val) {
    PC = MASK12(val);   // PC can never exceed 4095
}

void write_MAR(int val) {
    MAR = MASK12(val);  // MAR can never exceed 4095
}

void write_IR(int val) {
    IR = MASK16(val);
}

void write_MBR(int val) {
    MBR = MASK16(val);
}

void mem_write(int address, int value) {
    memory[MASK12(address)] = MASK16(value);
}

int mem_read(int address) {
    return memory[MASK12(address)];
}
