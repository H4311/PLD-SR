#ifndef _GCONTEXT_H_
#define _GCONTEXT_H_

struct gContext
{
	int esp; /* stack pointer */
	int ebp; /* base pointer */
	
};

typedef struct gContext gContext;

void gSaveContext(gContext *ctx);
void gLoadContext(gContext *ctx);


#endif
