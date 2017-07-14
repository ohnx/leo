/*
 * DO NOT EDIT THIS FILE DIRECTLY! This file is automatically generated from
 * the file `template/run_function.c`. The generated file was last updated
 * Fri Jul 14 2017 at 05:35 AM.
 */
#include "run_function.h"

/*
 * call a x86-64 cdecl function
 * 
 * cdecl specifies that the first few program args are, in order:
 * `rdi, rsi, rdx, rcx, r8, r9`. If it's doubles/floats, we use
 * "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7"
 * (aka our case :p)
 * further args are passed in the stack, which is not yet implemented.
 */
double *run_function(const char *name, size_t argc, double *argv) {
    void *f, *handle;
    double ret, *rt;

    rt = malloc(sizeof(double));

    /* open libm */
    handle = dlopen(NULL, RTLD_LAZY);
    if (!handle) { /* verify success */
        fprintf(stderr, "Failed to open self: %s\n", dlerror());
        return NULL;
    }

    /* find the address of function */
    f = dlsym(handle, name);
    if (f == NULL) { /* verify success */
        fprintf(stderr, "Failed to find function `%s`: %s\n", name, dlerror());
        return NULL;
    }
    
    switch (argc) {/* generated code */
    case 0:
        asm __volatile__ (
            /* create new stack frame */
            "pushq %%rbp\n\t"
            "mov %%rsp, %%rbp\n\t"

            /* put the right items in corresponding registers */

            /* call function */
            "call *%1\n\t"
            "movq %%xmm0, %0\n\t"

            /* restore old stack frame */
            "popq %%rbp\n\t"
            : "=r"(ret)
            : "r"(f)
            : "xmm0", "r15"
        );
        
        break;
    case 1:
        asm __volatile__ (
            /* create new stack frame */
            "pushq %%rbp\n\t"
            "mov %%rsp, %%rbp\n\t"

            /* put the right items in corresponding registers */
            "movq %2, %%xmm0\n\t"

            /* call function */
            "call *%1\n\t"
            "movq %%xmm0, %0\n\t"

            /* restore old stack frame */
            "popq %%rbp\n\t"
            : "=r"(ret)
            : "r"(f), "r"(argv[0]) 
            : "xmm0", "xmm0", "r15"
        );
        
        break;
    case 2:
        asm __volatile__ (
            /* create new stack frame */
            "pushq %%rbp\n\t"
            "mov %%rsp, %%rbp\n\t"

            /* put the right items in corresponding registers */
            "movq %2, %%xmm0\n\t"
            "movq %3, %%xmm1\n\t"

            /* call function */
            "call *%1\n\t"
            "movq %%xmm0, %0\n\t"

            /* restore old stack frame */
            "popq %%rbp\n\t"
            : "=r"(ret)
            : "r"(f), "r"(argv[0]) , "r"(argv[1]) 
            : "xmm0", "xmm1", "xmm0", "r15"
        );
        
        break;
    case 3:
        asm __volatile__ (
            /* create new stack frame */
            "pushq %%rbp\n\t"
            "mov %%rsp, %%rbp\n\t"

            /* put the right items in corresponding registers */
            "movq %2, %%xmm0\n\t"
            "movq %3, %%xmm1\n\t"
            "movq %4, %%xmm2\n\t"

            /* call function */
            "call *%1\n\t"
            "movq %%xmm0, %0\n\t"

            /* restore old stack frame */
            "popq %%rbp\n\t"
            : "=r"(ret)
            : "r"(f), "r"(argv[0]) , "r"(argv[1]) , "r"(argv[2]) 
            : "xmm0", "xmm1", "xmm2", "xmm0", "r15"
        );
        
        break;
    case 4:
        asm __volatile__ (
            /* create new stack frame */
            "pushq %%rbp\n\t"
            "mov %%rsp, %%rbp\n\t"

            /* put the right items in corresponding registers */
            "movq %2, %%xmm0\n\t"
            "movq %3, %%xmm1\n\t"
            "movq %4, %%xmm2\n\t"
            "movq %5, %%xmm3\n\t"

            /* call function */
            "call *%1\n\t"
            "movq %%xmm0, %0\n\t"

            /* restore old stack frame */
            "popq %%rbp\n\t"
            : "=r"(ret)
            : "r"(f), "r"(argv[0]) , "r"(argv[1]) , "r"(argv[2]) , "r"(argv[3]) 
            : "xmm0", "xmm1", "xmm2", "xmm3", "xmm0", "r15"
        );
        
        break;
    case 5:
        asm __volatile__ (
            /* create new stack frame */
            "pushq %%rbp\n\t"
            "mov %%rsp, %%rbp\n\t"

            /* put the right items in corresponding registers */
            "movq %2, %%xmm0\n\t"
            "movq %3, %%xmm1\n\t"
            "movq %4, %%xmm2\n\t"
            "movq %5, %%xmm3\n\t"
            "movq %6, %%xmm4\n\t"

            /* call function */
            "call *%1\n\t"
            "movq %%xmm0, %0\n\t"

            /* restore old stack frame */
            "popq %%rbp\n\t"
            : "=r"(ret)
            : "r"(f), "r"(argv[0]) , "r"(argv[1]) , "r"(argv[2]) , "r"(argv[3]) , "r"(argv[4]) 
            : "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm0", "r15"
        );
        
        break;
    case 6:
        asm __volatile__ (
            /* create new stack frame */
            "pushq %%rbp\n\t"
            "mov %%rsp, %%rbp\n\t"

            /* put the right items in corresponding registers */
            "movq %2, %%xmm0\n\t"
            "movq %3, %%xmm1\n\t"
            "movq %4, %%xmm2\n\t"
            "movq %5, %%xmm3\n\t"
            "movq %6, %%xmm4\n\t"
            "movq %7, %%xmm5\n\t"

            /* call function */
            "call *%1\n\t"
            "movq %%xmm0, %0\n\t"

            /* restore old stack frame */
            "popq %%rbp\n\t"
            : "=r"(ret)
            : "r"(f), "r"(argv[0]) , "r"(argv[1]) , "r"(argv[2]) , "r"(argv[3]) , "r"(argv[4]) , "r"(argv[5]) 
            : "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm0", "r15"
        );
        
        break;
    default:
        asm __volatile__ (
            /* create new stack frame */
            "pushq %%rbp\n\t"
            "mov %%rsp, %%rbp\n\t"

            /* put the right items in corresponding registers */
            "movq %2, %%xmm0\n\t"
            "movq %3, %%xmm1\n\t"
            "movq %4, %%xmm2\n\t"
            "movq %5, %%xmm3\n\t"
            "movq %6, %%xmm4\n\t"
            "movq %7, %%xmm5\n\t"

            /* call function */
            "call *%1\n\t"
            "movq %%xmm0, %0\n\t"

            /* restore old stack frame */
            "popq %%rbp\n\t"
            : "=r"(ret)
            : "r"(f), "r"(argv[0]) , "r"(argv[1]) , "r"(argv[2]) , "r"(argv[3]) , "r"(argv[4]) , "r"(argv[5]) 
            : "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm0", "r15"
        );
        return NULL;
        break;
    }

    *rt = ret;
    return rt;
}

/* debug code - to use, compile with
 * `gcc src/run_function.c -Iinclude/ -Wall -ldl -Werror -g -D__RUNFUNC_DEBUG -rdynamic`
 * to run, run `LD_PRELOAD=/lib/x86_64-linux-gnu/libm.so.6 ./a.out `
 */
#ifdef __RUNFUNC_DEBUG
#include <stdio.h>
int main() {
    double vars[] = {3.1415926535f / 2.0f, 1.2f};
    double *nbr = run_function("sin", 2, vars);
    if (nbr) {
        printf("Result: %lf\n", *nbr);
        free(nbr);
    }
    return 0;
}
#endif
