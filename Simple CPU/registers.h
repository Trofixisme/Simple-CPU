// registers.h: Declarations for CPU register variables and functions

#ifndef REGISTERS_H
#define REGISTERS_H

extern int cpuClock;
#define MAXSIZE 4096

extern int AC;
extern int IR;
extern int MBR;
extern int InREG;
extern int OutREG;
extern int PC;
extern int MAR;
extern int data_bus;
extern int memory[MAXSIZE];

#define MASK16(val) ((val)&0xFFFF)
#define MASK12(val) ((val)&0xFFF)
#define MASK8(val) ((val)&0xFF)

void write_PC(int val);
void write_IR(int val);

void write_AC(int val);

void write_MAR(int val);
void write_MBR(int val);

void mem_write(int address, int value);
int mem_read(int address);

void write_InREG(int value);
void write_OutREG(int value);

#endif // REGISTERS_H
