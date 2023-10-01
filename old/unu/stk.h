#ifndef STK_H
#define STK_H

// types & defines

#include "platform.h"

#define STK_SIZE 0x100 // 8 bit

// structure

typedef struct stk {
	byte d[STK_SIZE], p;
} stk;

// prototypes

void stk_psh(stk *s, byte v);
byte stk_pop(stk *s);
byte stk_tos(stk *s);

// implementation

#ifdef STK_IMPL

void
stk_psh(stk *s, byte v) {
	s->d[s->p++]=v;
}

byte
stk_pop(stk *s) {
	return s->d[--s->p];
}

byte
stk_tos(stk *s) {
	if(s->p==0) return 0;
	return s->d[s->p-1];
}

#endif

#endif
