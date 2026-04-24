//
//  FetchDecodeExecute.h
//  Simple CPU
//
//  Created by Ziad on 23/04/2026.
//

#ifndef Instructions_h
#define Instructions_h

extern int halted;

void LOAD(void);
void STORE(void);

void ADD(void);
void SUBT(void);

void HALT(void);
void JUMP(void);

void ADDI(void);
void STOREI(void);

void IN(void);
void OUT(void);

void SKIPCOND(void);
void CLEAR(void);

#endif /* FetchDecodeExecute_h */
