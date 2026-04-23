#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fetchDecodeExecute.h"
#include "instructions.h"

int main(void) {
    
    int clock=0;
    
    while(!halted) {
        
        fetch();
        decode();
        execute();
        
        clock++;
        sleep(1);
        
    }
}
