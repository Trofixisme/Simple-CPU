#include <stdlib.h>
#include <stdio.h>
#include "unistd.h"
#include "registers.h"
#include "instructions.h"
#include "fetchDecodeExecute.h"
#include "assembler.h"

int load_program(const char *filename) {
    
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", filename);
        return 0;
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
    return 1;
}

int main(int argc, const char * argv[]) {
   
    
    //Be sure to temporarily replace this with the absolute filepath if you're using Xcode until someone figures out how to use the relative filepath with Xcode without failing
    while (!halted && load_program("program.txt")) {
        
        fetch();
        
        decode();
        
        execute();
  
    }
}
