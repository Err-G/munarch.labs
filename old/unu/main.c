#include <stdio.h>

#include "unu.h"

void
status(unu *u) {
	printf("here: %d\n", u->h);
	printf("dptr: %d\n", u->d.p);
	printf("rptr: %d\n", u->r.p);
	printf("dval: %d\n", stk_tos(&u->d));
	printf("rval: %d\n\n", stk_tos(&u->r));
}

void
exec(unu *u) {
	byte on = TRUE;
	while (on) {
		byte instr = u->m[u->h];
		if (instr == BRK) { // HALT
			on = FALSE;
		} else {
			unu_eval(u);
			status(u);
		}
	}
}

int
main(void) {
	byte rom[256] = {
		GTH, LIT, 1, ADD, JMP, BRK,
	};
	
	unu unu;
	unu_init(&unu, rom);
	exec(&unu);
	status(&unu);

	return 0;
}
