include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
# SOURCES_ASM=$(carpeta/*.asm)

OBJECTS=$(SOURCES:.c=.o)
# OBJECTS=$(SOURCES_ASM:.asm=.o)

all: $(MODULE)



$(MODULE): $(SOURCES) $(OBJECTS)
	$(LD) -T sampleCodeModule.ld _loader.o $(OBJECTS) -o ../$(MODULE)


%.o:%.c
	$(GCC) $(GCCFLAGS) -I./include -c _loader.c  $(SOURCES)

#%.o:%.asm
# $(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o

.PHONY: all clean print
