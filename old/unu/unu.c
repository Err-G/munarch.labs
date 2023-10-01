#include <stdio.h>

#define STK_IMPL
#include "stk.h"
#include "unu.h"

void
unu_init(unu *u, byte *m) {
	char *p=(char*)u;
	long unsigned int i;
	for(i=0;i<sizeof(*u);i++)
		p[i]=0;
	u->m=m;
}

void
impl_nop(unu *u) {
	u->h++;
}

#define NEXT impl_nop(u);

void
impl_lit(unu *u) {
	stk_psh(&u->d, u->m[++u->h]);
	NEXT
}

void
impl_gth(unu *u) {
	stk_psh(&u->d, u->h);
	NEXT
}

void
impl_jmp(unu *u) {
	u->h = stk_pop(&u->d);
	NEXT
}

void
impl_tor(unu *u) {
	stk_psh(&u->r, stk_pop(&u->d));
	NEXT
}

void
impl_frr(unu *u) {
	stk_psh(&u->d, stk_pop(&u->r));
	NEXT
}

void
impl_jcn(unu *u) {
	if (stk_pop(&u->d)!=0)
		impl_jmp(u);
	else
		stk_pop(&u->d);
	NEXT
}

void
impl_drp(unu *u) {
	stk_pop(&u->d);
	NEXT
}

void
impl_nip(unu *u) {
	byte a = stk_pop(&u->d);
	impl_drp(u);
	stk_psh(&u->d, a);
	NEXT
}

void
impl_swp(unu *u) {
	byte a = stk_pop(&u->d);
	byte b = stk_pop(&u->d);
	stk_psh(&u->d, a);
	stk_psh(&u->d, b);
	NEXT
}

void
impl_rot(unu *u) {
	byte a = stk_pop(&u->d);
	byte b = stk_pop(&u->d);
	byte c = stk_pop(&u->d);
	stk_psh(&u->d, b);
	stk_psh(&u->d, a);
	stk_psh(&u->d, c);
	NEXT
}

void
impl_dup(unu *u) {
	byte a = stk_pop(&u->d);
	stk_psh(&u->d, a);
	stk_psh(&u->d, a);
	NEXT
}

void
impl_ovr(unu *u) {
	byte a = stk_pop(&u->d);
	byte b = stk_pop(&u->d);
	stk_psh(&u->d, b);
	stk_psh(&u->d, a);
	stk_psh(&u->d, b);
	NEXT
}

void
impl_add(unu *u) {
	byte a = stk_pop(&u->d);
	byte b = stk_pop(&u->d);
	stk_psh(&u->d, b+a);
	NEXT
}

void
impl_sub(unu *u) {
	byte a = stk_pop(&u->d);
	byte b = stk_pop(&u->d);
	stk_psh(&u->d, b-a);
	NEXT
}

void
impl_mul(unu *u) {
	byte a = stk_pop(&u->d);
	byte b = stk_pop(&u->d);
	stk_psh(&u->d, b*a);
	NEXT
}

void
impl_div(unu *u) {
	byte a = stk_pop(&u->d);
	byte b = stk_pop(&u->d);
	if(a==0) stk_psh(&u->d, 0);
	else stk_psh(&u->d, b/a);
	NEXT
}

impl instr[] = {
	impl_nop, // noop
	// stack
	impl_lit, impl_gth, impl_jmp, impl_tor, impl_frr, impl_jcn,
	impl_drp, impl_nip, impl_swp, impl_rot, impl_dup, impl_ovr,
	// arithmetic
	impl_add, impl_sub, impl_mul, impl_div,
};

void
unu_eval(unu *u) {
  instr[u->m[u->h]](u);
}

void
unu_exec(unu *u) {
	byte on = TRUE;
	while (on) {
		byte instr = u->m[u->h];
		if (instr == BRK) { // HALT
			on = FALSE;
		} else {
			unu_eval(u);
		}
	}
}
