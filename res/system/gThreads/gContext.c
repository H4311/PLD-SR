#include <stdlib.h>
#include <stdio.h>

#include "gContext.h"

void gSaveContext(gContext *ctx)
{
	asm("movl %%esp, %0" "\n" "movl %%ebp, %1"
            :"=r"(ctx->esp),
            "=r"(ctx->ebp) 
        );
}

void gLoadContext(gContext *ctx)
{
	asm("movl %0, %%esp" "\n" "movl %1, %%ebp"
        :
        :"r"(ctx->esp),
         "r"(ctx->ebp)
    );
}
