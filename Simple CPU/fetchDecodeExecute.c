#include <stdio.h>
#include "registers.h"
#include "instructions.h"

int temp = 0;
int print_after_each_instruction = 0;

int opcode = 0;
int address = 0;

void fetch(void) {
    
    if (!temp) {
        char response;
        printf("Print the memory after each cycle? y/n\n");
        scanf("%c", &response);
        fflush(stdout);
        
        if (response == 'y' || response == 'Y')
            print_after_each_instruction = 1;
        temp = 1;
    }
    
    write_MAR(PC);
    printf("MAR <- PC (%d)", PC);
    
    data_bus = mem_read(MAR);
    
    write_IR(data_bus);
    printf("IR <- M[MAR] (%d)", IR);
    write_PC(PC + 1);
    printf("PC <- PC (%d) + 1", PC - 1);
}

void decode(void) {
    
    opcode = (IR >> 12) & 0xF;
    printf("Decode IR[15 - 12]");
    write_MAR(IR & 0x0FFF);
    printf("MAR <- IR[11 - 0]");
    
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
    
    if (print_after_each_instruction)
        print_cpu_state();
}
