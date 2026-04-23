// registers.h: Declarations for CPU register variables and functions

#ifndef REGISTERS_H
#define REGISTERS_H

// Register variables
extern int AC;
extern int IR;
extern int MBR;
extern int InREG;
extern int OutREG;
extern int PC;
extern int MAR;
extern int data_bus;
extern int memory[4096];

// Register mask macros
#define MASK16(val) ((val)&0xFFFF)
#define MASK12(val) ((val)&0xFFF)

// Register write functions
void write_AC(int val);
void write_PC(int val);
void write_MAR(int val);
void write_IR(int val);
void write_MBR(int val);
void mem_write(int address, int value);
int mem_read(int address);

#endif // REGISTERS_H
