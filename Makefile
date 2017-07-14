INCLUDES=-Iinclude/
CFLAGS=$(INCLUDES) -Wall -Werror -pedantic

OBJ=objs/queue.o objs/stack.o objs/syard.o objs/tokenizer.o objs/rpn_calc.o objs/run_function.o
OUTPUT=libleo.a

.PHONY: debug
default: $(OUTPUT)
debug: CFLAGS += -g -O0 -D__DEBUG
debug: $(OUTPUT)

################################################################################
#                                SOURCES STUFF                                 #
################################################################################

objs/%.o: src/%.c
	@mkdir -p objs/
	$(CC) -c -o $@ $< $(CFLAGS) $(EXTRA)

$(OUTPUT): $(OBJ)
	ar rcs $(OUTPUT) $(OBJ)

.PHONY: clean
clean:
	-rm -f $(OBJ) objs/repl.o
	-rm -f $(OUTPUT)
	-rm -f leo

################################################################################
#                             COMMAND LINE STUFF                               #
################################################################################

repl: $(OUTPUT) objs/repl.o
	$(CC) objs/repl.o -L. -lleo -lm -ldl -o leo $(CFLAGS)

.PHONY: drepl
drepl: debug
	$(CC) objs/repl.o -L. -lleo -lm -ldl -o leo $(CFLAGS)
