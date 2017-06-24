#include "syard.h"
#include <stdio.h>

static int map_operator_precendence(char a) {
    switch (a) {
    case '^': return 10;
    case '*':
    case '/': return 6;
    case '+':
    case '-': return 3;
    default: return -1;
    }
}

static int map_operator_associativity(char a) {
    switch(a) {
    case '^': return 0;
    default: return 1;
    }
}

static int operator_is_preceding(char a, char b) {
    return map_operator_associativity(b) ?
            map_operator_precendence(a) >= map_operator_precendence(b):
            map_operator_precendence(a) >  map_operator_precendence(b);
}

char *strdup(const char *a) {
    size_t len;
    char *dup;

    len = strlen(a) + 1;
    dup = malloc(sizeof(char) * len);
    if (!dup) return dup;

    memcpy(dup, a, len);
    return dup;
}

static void *create_double_data(char *repr) {
    struct syard_var *v = malloc(sizeof(struct syard_var) + sizeof(double));
    v->type = TYPE_DOUBLE;
    /* advance past the type variable to reach the data storage for double */
    sscanf(repr, "%lf", ((double *)(v + 1)));
    return v;
}

static void *create_char_data(char in) {
    struct syard_var *v = malloc(sizeof(struct syard_var) + sizeof(char));
    v->type = TYPE_CHAR;
    /* advance past the type variable to reach the data storage for char */
    *((char *)(v + 1)) = in;
    return v;
}

/* reverse polish https://en.wikipedia.org/wiki/Shunting-yard_algorithm */
queue *syard_run(const char *in) {
    /* init */
    stack *s;
    queue *q;
    tokenizer_ctx *tkc;
    char *tok, *op, *newstr;

    s = stack_new();
    q = queue_new();
    tkc = tokenizer_new();
    newstr = strdup(in);
    tokenizer_reset(tkc, newstr);

    /* while there are tokens to be read, read a token. */
    while ((tok = tokenizer_next(tkc)) != NULL) {
        switch (tkc->type) {
        /* if the token is a number, then push it to the output queue. */
        case TOKEN_NUMBER:
            queue_enqueue(q, create_double_data(tok));
            break;
        /* if the token is an operator, then: */
        case TOKEN_OPERATOR:
            /* while there is an operator at the top of the operator stack with
			   greater than or equal to precedence: */
            while (((op = stack_top(s)) != NULL) && operator_is_preceding(*op, *tok)) {
                /* pop operators from the operator stack, onto the output queue; */
                queue_enqueue(q, create_char_data(*(char *)stack_pop(s)));
            }
            /* push the read operator onto the operator stack. */
            stack_push(s, (void *)tok);
            break;
        /* if the token is a left bracket (i.e. "("), then: */
        case TOKEN_LBRACKET:
            /* push it onto the operator stack */
            stack_push(s, tok);
            break;
        /* if the token is a right bracket (i.e. ")"), then: */
        case TOKEN_RBRACKET:
            /* while the operator at the top of the operator stack is not a left bracket: */
            while (((op = stack_top(s)) != NULL) && *op != '(') {
                /* pop operators from the operator stack onto the output queue. */
                queue_enqueue(q, create_char_data(*(char *)stack_pop(s)));
            }
            /* if the stack runs out without finding a left bracket, then there are
		       mismatched parentheses. */
		    if (op == NULL || (op != NULL && *op != '(')) {
		        /* mismatched parentheses */
		        printf("mismatched parentheses; extra )\n");
		        goto err_cleanup;
		    }
		    /* pop the left bracket from the stack. */
	        stack_pop(s);
            break;
        default:
            break;
        }
    }
    
    /* if there are no more tokens to read: */
    if (tkc->type == TOKEN_END) {
        /* while there are still operator tokens on the stack: */
        while (((op = stack_top(s)) != NULL) && *op != '(') {
            /* pop the operator onto the output queue. */
            queue_enqueue(q, create_char_data(*(char *)stack_pop(s)));
        }
        /* if the operator token on the top of the stack is a bracket, then
		there are mismatched parentheses. */
		if (op != NULL && *op == '(') {
            printf("mismatched parentheses; extra (\n");
            goto err_cleanup;
		}
    } else {
        printf("unknown character `%c` in equation\n", *(tkc->pos));
        goto err_cleanup;
    }

    stack_destroy(s);
    tokenizer_destroy(tkc);
    free(newstr);
    return q;

    err_cleanup:
    stack_destroy(s);
    tokenizer_destroy(tkc);
    queue_foreach(q, syard_queue_cleanup, NULL);
    queue_destroy(q);
    free(newstr);
    return NULL;
}


void syard_queue_cleanup(void *d, void *c) {
    free(d);
}
