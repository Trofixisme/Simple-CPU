#include <stdio.h>

//Macros for defining 16-bit and 12-bit addresses
#define MASK16(val) ((val)&0xFFFF)
#define MASK12(val) ((val)&0xFFF)
#define MASK8(val) ((val)&0xFF)

int clock = 0;

// 16-bit registers
int AC = 0;
int IR = 0;
int MBR = 0;

// 12-bit registers (stored in 16-bit but masked on write)
int PC = 0;
int MAR = 0;

// 8-bit registers
int InREG = 0;
int OutREG = 0;

int data_bus = 0;

// Memory, 8192 bytes in size
int memory[4096];


void write_AC(int val) {
    AC = MASK16(val);
    clock++;
}

void write_PC(int val) {
    PC = MASK12(val);
    clock++;
}

void write_MAR(int val) {
    MAR = MASK12(val);
    clock++;
}

void write_IR(int val) {
    IR = MASK16(val);
    clock++;
}

void write_MBR(int val) {
    MBR = MASK16(val);
    clock++;
}

void mem_write(int address, int value) {
    memory[MASK12(address)] = MASK16(value);
    clock++;
}

int mem_read(int address) {
    return memory[MASK12(address)];
    clock++;
}

void write_IN(int value) {
    InREG = MASK8(value)
    clock++;
}

void write_OUT(int value) {
    OutREG = MASK8(value)
    clock++;
}
