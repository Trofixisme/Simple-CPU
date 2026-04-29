#include <stdlib.h>
#include <stdio.h>
#include "unistd.h"
#include "registers.h"
#include "instructions.h"
#include "fetchDecodeExecute.h"
#include "assembler.h"
void load_program(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", filename);
        return;
    }
    char line[256];      // buffer to hold each line
    int  address = 0;    // where in memory to store

    while (fgets(line, sizeof(line), file) != NULL) {
        
        // skip empty lines and comments
        if (line[0] == '\n' || line[0] == '#') continue;

        // send line to assembler, get back 16-bit instruction
        int instruction = assemble(line);

        // store result in memory
        mem_write(address, instruction);
        address = MASK12(address + 1);
    }

    fclose(file);
}
int main(int argc, const char * argv[]) {
   
    load_program("program.txt");
    while (!halted) {
        
        fetch();
        
        decode();
        
        execute();
  
    }
}
