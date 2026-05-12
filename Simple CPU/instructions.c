#include <stdio.h>
#include <stdlib.h>
#include "registers.h"
#include "fetchDecodeExecute.h"

int halted = 0;

//NOT an instruction, but it's called after each instruction to show the memory (our array of 4096 ints)
void print_cpu_state(void) {
    printf("Memory:\n");
    printf("AC %04X   IR %04X   MAR %03X   MBR %04X   PC %03X   IN %04X   OUT %04X\n",
           MASK16(AC), MASK16(IR), MASK12(MAR), MASK16(MBR), MASK12(PC), MASK16(InREG), MASK16(OutREG));
    printf("\n");
    printf("       +0   +1   +2   +3   +4   +5   +6   +7   +8   +9   +A   +B   +C   +D   +E   +F\n");
    for (int i = 0; i < MAXSIZE; i += 16) {
        int has_data = 0;
        if (i <= 0x040) {
            has_data = 1;
        } else {
            for (int j = 0; j < 16; j++) {
                if (memory[i + j] != 0) {
                    has_data = 1;
                    break;
                }
            }
        }
        
        if (has_data) {
            printf(" %03X  ", i);
            for (int j = 0; j < 16; j++) {
                printf("%04X ", MASK16(memory[i + j]));
            }
            printf("\n");
        }
    }
    printf("\n");
}

void LOAD(void) {
    
    data_bus = mem_read(MAR);
    write_MBR(data_bus);
    printf("MBR <- M[MAR] (%d)\n", MBR);
    
    data_bus = MBR;
    write_AC(data_bus);
    printf("AC <- MBR (%d)\n", AC);
}

void STORE(void) {
    
    data_bus = AC;
    write_MBR(data_bus);
    printf("MBR <- AC (%d)\n", AC);
    
    data_bus = MBR;
    mem_write(MAR, data_bus);
    
    printf("%d has been written into (0x%04X)\n", MBR, MASK16(MAR));
}

void ADD(void) {
    
    data_bus = mem_read(MAR);
    write_MBR(data_bus);
    printf("MBR <- M[MAR] (%d)\n", MBR);
    
    data_bus = MBR;
    printf("AC <- AC (%d) + MBR (%d)\n", AC, MBR);
    write_AC(AC + data_bus);
}

void SUBT(void) {
    
    data_bus = mem_read(MAR);
    write_MBR(data_bus);
    printf("MBR <- M[MAR] (%d)\n", MBR);
    
    data_bus = MBR;
    printf("AC <- AC (%d) - MBR (%d)\n", AC, MBR);
    write_AC(AC - data_bus);
}

void JUMP(void) {
    write_PC(MAR);
    printf("PC <- MAR (0x%04X)\n", MASK16(MAR));
}

void IN(void) {
    printf("input: ");
    fflush(stdout);
    
    int temp;
    char buffer;
    scanf("%d", &temp);
    scanf("%c", &buffer);
    
    data_bus = temp;
    write_InREG(temp);
    data_bus = InREG;
    
    write_AC(data_bus);
    printf("AC <- IN (%d)\n", InREG);
}

void OUT(void) {
    
    data_bus = AC;
    write_OutREG(data_bus);
    printf("OUT <- AC (%d)\n", OutREG);
    
    printf("\nOutput: %d (0x%04X)\n", OutREG, MASK16(OutREG));
}

void HALT(void) {
    halted = 1;
}

void CLEAR(void) {
    write_AC(0);
    printf("AC <- 0\n");
}

void SKIPCOND(void) {
   
    // MAR holds the condition code set during decode
    if (MAR == 0x000 && AC < 0)  {
        printf("PC <- PC (%d) + 1\n", PC);
        write_PC(PC + 1);
    } else if (MAR == 0x400 && AC == 0) {
        printf("PC <- PC (%d) + 1\n", PC);
        write_PC(PC + 1);
    } else if (MAR == 0x800 && AC > 0) {
        printf("PC <- PC (%d) + 1\n", PC);
        write_PC(PC + 1);
    }
}

void ADDI(void) {
    // indirect: address field points to address that holds the real address
    data_bus = mem_read(MAR);
    write_MAR(data_bus);          // follow the pointer
    printf("MAR <- M[MAR] (0x%04X)\n", MASK16(MAR));
    data_bus = mem_read(MAR);
    write_MBR(data_bus);
    printf("MBR <- M[MAR] (%d)\n", MBR);
    printf("AC <- AC (%d) + MBR (%d)\n", AC, MBR);
    write_AC(MASK16(AC + MBR));
}

void LOADI(void) {
    data_bus = mem_read(MAR);
    write_MAR(data_bus);
    printf("MAR <- M[MAR] (0x%04X)\n", MASK16(MAR));
    data_bus = mem_read(MAR);
    write_MBR(data_bus);
    printf("MBR <- M[MAR] (%d)\n", MBR);
    write_AC(MBR);
    printf("AC <- MBR (%d)\n", MBR);
}

void STOREI(void) {
    data_bus = mem_read(MAR);
    write_MAR(data_bus);
    printf("MAR <- M[MAR] (0x%04X)\n", MASK16(MAR));
    data_bus = AC;
    write_MBR(data_bus);
    printf("MBR <- AC (%d)\n", AC);
    mem_write(MAR, MBR);
    printf("M[MAR] <- MBR (%d)\n", MBR);
    
    printf("%d has been written into (0x%04X)\n", MBR, MASK16(MAR));
}


void SUBTI(void) {
     // indirect: address field points to address that holds the real address
    data_bus = mem_read(MAR);
    write_MAR(data_bus);
    printf("MAR <- M[MAR] (0x%04X)\n", MASK16(MAR));
    data_bus = mem_read(MAR);
    write_MBR(data_bus);
    printf("MBR <- M[MAR] (%d)\n", MBR);
    printf("AC <- AC (%d) - MBR (%d)\n", AC, MBR);
    write_AC(MASK16(AC - MBR));
}

void JUMPI(void) {
    data_bus = mem_read(MAR);
    write_MAR(data_bus);
    printf("MAR <- M[MAR] (0x%04X)\n", MASK16(MAR));
    write_PC(MAR);
    printf("PC <- MAR (0x%04X)\n", MASK16(MAR));
}

