//
//  FetchDecodeExecute.h
//  Simple CPU
//
//  Created by Ziad on 23/04/2026.
//

#ifndef FetchDecodeExecute_h
#define FetchDecodeExecute_h

extern int address;
extern int opcode;

void fetch(void);
void decode(void);
void execute(void);

#endif /* FetchDecodeExecute_h */
