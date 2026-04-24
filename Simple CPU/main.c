#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fetchDecodeExecute.h"
#include "instructions.h"

int main(void) {
    
    while(!halted) {
        
        fetch();
        decode();
        execute();
        sleep(1);
        
    }
}
