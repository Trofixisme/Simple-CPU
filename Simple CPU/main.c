#include <stdlib.h>
#include <stdio.h>
#include "unistd.h"
#include "registers.h"
#include "instructions.h"
#include "fetchDecodeExecute.h"

int main(int argc, const char * argv[]) {
    
    while (!halted) {
        
        fetch();
        
        decode();
        
        execute();
        
        sleep(1);
    }
}
