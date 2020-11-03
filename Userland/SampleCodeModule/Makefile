include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
SOURCES_ASM=$(wildcard asm/*.asm)
SOURCES_CHESS=$(wildcard chess/*c)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_CHESS=$(SOURCES_CHESS:.c=.o)

all: $(MODULE)




$(MODULE): $(SOURCES) $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_CHESS) _loader.o
	$(LD) -T sampleCodeModule.ld _loader.o $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_CHESS) -o ../$(MODULE)

_loader.o:_loader.c
	$(GCC) $(GCCFLAGS) -c _loader.c

%.o:%.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@



%.o:%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o asm/*.o chess/*.o

.PHONY: all clean print
