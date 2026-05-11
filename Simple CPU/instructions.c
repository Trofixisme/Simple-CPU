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
    fflush(stdout);
    
    int temp;
    char buffer;
    scanf("%d", &temp);
    scanf("%c", &buffer);
    
    data_bus = temp;
    write_InREG(temp);
    data_bus = InREG;
    
    write_AC(data_bus);
}

void print_cpu_state(void) {
    printf("\n===============================================================================\n");
    printf("   AC %04X   IR %04X   MAR %03X   MBR %04X   PC %03X   IN %04X   OUT %04X\n", 
           MASK16(AC), MASK16(IR), MASK12(MAR), MASK16(MBR), MASK12(PC), MASK16(InREG), MASK16(OutREG));
    printf("\n");
    printf("       +0   +1   +2   +3   +4   +5   +6   +7   +8   +9   +A   +B   +C   +D   +E   +F\n");
    for (int i = 0; i < MAXSIZE; i += 16) {
        int has_data = 0;
        // Always show the first 5 rows (0x000 to 0x040) to match the screenshot
        if (i <= 0x040) {
            has_data = 1;
        } else {
            // Check if there's any non-zero value in this row (e.g. data section)
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
    printf("===============================================================================\n");
}

void OUT(void) {
    
    data_bus = AC;
    write_OutREG(data_bus);
    
    printf("\nOutput: %d (0x%04X)\n", OutREG, MASK16(OutREG));
    print_cpu_state();
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
