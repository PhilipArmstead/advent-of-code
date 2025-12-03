CC := clang
CCFLAGS += -std=c99 -Wall -Werror -Wstrict-prototypes -Wno-pointer-sign
LDFLAGS += -lm
DEBUG_FLAGS := -O0 -g -DIS_DEBUG -Wno-unused-variable -Wno-unused-but-set-variable

all: main.c
	$(CC) main.c -o aoc $(CCFLAGS) $(LDFLAGS) -O3

day-1:
	$(CC) -c $@/$@.c -o $@/$@.o $(CCFLAGS) $(DEBUG_FLAGS)
	$(CC) $@/$@.o -o $@/$@.out $(LDFLAGS) $(DEBUG_FLAGS)

day-2:
	$(CC) -c $@/$@.c -o $@/$@.o $(CCFLAGS) $(DEBUG_FLAGS)
	$(CC) $@/$@.o -o $@/$@.out $(LDFLAGS) $(DEBUG_FLAGS)

day-3:
	$(CC) -c $@/$@.c -o $@/$@.o $(CCFLAGS) $(DEBUG_FLAGS)
	$(CC) $@/$@.o -o $@/$@.out $(LDFLAGS) $(DEBUG_FLAGS)

clean:
	rm aoc

.PHONY: all clean day-1 day-2 day-3
