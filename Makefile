INCLUDES=-Iinclude/
CFLAGS=$(INCLUDES) -Wall -Werror -pedantic -fPIC

OBJ=objs/queue.o objs/stack.o objs/syard.o objs/tokenizer.o objs/rpn_calc.o
OBJ_NONANSI=objs/run_function.o
OUTPUT=libleo.a

.PHONY: debug
default: $(OUTPUT)
debug: CFLAGS += -g -O0 -D__DEBUG
debug: $(OUTPUT)

################################################################################
#                                SOURCES STUFF                                 #
################################################################################

src/run_function.c:
	cd src/template; ./run_function.sh; cd ../../;

objs/%.o: src/%.c
	@mkdir -p objs/
	$(CC) -c -o $@ $< $(CFLAGS) -ansi $(EXTRA)

objs/run_function.o: src/run_function.c
	@mkdir -p objs/
	$(CC) -c -o $@ $< $(CFLAGS) $(EXTRA)

$(OUTPUT): $(OBJ) $(OBJ_NONANSI)
	ar rcs $(OUTPUT) $^

.PHONY: clean
clean:
	-rm -f $(OBJ) $(OBJ_NONANSI) objs/repl.o objs/hashmap.o
	-rm -f $(OUTPUT)
	-rm -f leo

################################################################################
#                             COMMAND LINE STUFF                               #
################################################################################

repl: $(OUTPUT) objs/repl.o objs/hashmap.o
	$(CC) objs/repl.o objs/hashmap.o -L. -lleo -lm -ldl -o leo $(CFLAGS)

.PHONY: drepl
drepl: CFLAGS += -g -O0 -D__DEBUG
drepl: debug objs/repl.o objs/hashmap.o
	$(CC) objs/repl.o objs/hashmap.o -L. -lleo -lm -ldl -o leo $(CFLAGS)
