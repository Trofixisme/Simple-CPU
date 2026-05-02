#include <stdio.h>
#include <string.h>
#define MASK16(val) ((val)&0xFFFF)
#define MASK12(val) ((val)&0xFFF)
#define MASK8(val) ((val)&0xFF)

int assemble(char *line) {
    char mnemonic[10];
    int  operand = 0;
    sscanf(line, "%s %d", mnemonic, &operand);

    if
        (strcmp(mnemonic, "LOAD") == 0) return MASK16((0x1 << 12) | MASK12(operand));
    else if
        (strcmp(mnemonic, "STORE") == 0) return MASK16((0x2 << 12) | MASK12(operand));
    else if
        (strcmp(mnemonic, "ADD") == 0) return MASK16((0x3 << 12) | MASK12(operand));
    else if
        (strcmp(mnemonic, "SUBT") == 0) return MASK16((0x4 << 12) | MASK12(operand));
    else if
        (strcmp(mnemonic, "INPUT") == 0) return MASK16((0x5 << 12));
    else if
        (strcmp(mnemonic, "OUTPUT") == 0) return MASK16((0x6 << 12));
    else if
        (strcmp(mnemonic, "HALT") == 0) return MASK16((0x7 << 12));
    else if
        (strcmp(mnemonic, "SKIPCOND") ==0) return MASK16((0x8 << 12) | MASK12(operand));
    else if
        (strcmp(mnemonic, "JUMP") == 0) return MASK16((0x9 << 12) | MASK12(operand));
    else if
        (strcmp(mnemonic, "CLEAR") == 0) return MASK16((0xA << 12));
    else if
        (strcmp(mnemonic, "ADDI") == 0) return MASK16((0xB << 12) | MASK12(operand));
    else if
        (strcmp(mnemonic, "JUMPI") == 0) return MASK16((0xC << 12) | MASK12(operand));
    else if
        (strcmp(mnemonic, "LOADI") == 0) return MASK16((0xD << 12) | MASK12(operand));
    else {
        printf("Unknown: %s\n", mnemonic);
        return 0;
    }
}
