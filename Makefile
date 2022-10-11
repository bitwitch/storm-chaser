PROG     := stormchaser
CFLAGS   := -Wall -std=c99 -O2 -I./include $(shell sdl2-config --cflags --libs)
DBGFLAGS := -Wall -std=c99 -ggdb -Og -I./include $(shell sdl2-config --cflags --libs)
LFLAGS   := -L/usr/local/lib -lSDL2_mixer -lm
SOURCES  := $(wildcard ./src/*.c)

.PHONY: $(PROG)

$(PROG):
	gcc -o $(PROG) $(SOURCES) $(LFLAGS) $(CFLAGS)

debug:
	gcc -o $(PROG).debug $(SOURCES) $(LFLAGS) $(DBGFLAGS)
