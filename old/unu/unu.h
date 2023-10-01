#ifndef UNU_H
#define UNU_H

/* TYPES & DEFINES */

#include "platform.h"
#include "stk.h"

typedef struct unu {
	byte *m,h; // memory & here
	stk  d, r; // (data & return) stacks
} unu;


typedef void (*impl)(unu *u);

enum {
	// noop
	NOP,
	// stack manipulation
	LIT, GTH, JMP, TOR, FRR, JCN, 
	DRP, NIP, SWP, ROT, DUP, OVR,
	// arithmetic
	ADD, SUB, MUL, DIV, 
	BRK,
};

/* FUNCTIONS */

void unu_init(unu *u, byte *m);
void unu_eval(unu *u);
void unu_exec(unu *u);

#endif
