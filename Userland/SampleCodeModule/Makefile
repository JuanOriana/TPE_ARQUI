include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
SOURCES_ASM=$(wildcard asm/*.asm)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)

all: $(MODULE)



$(MODULE): $(SOURCES) $(OBJECTS) $(OBJECTS_ASM)
	$(LD) -T sampleCodeModule.ld _loader.o $(OBJECTS) $(OBJECTS_ASM) -o ../$(MODULE)


%.o:%.c
	$(GCC) $(GCCFLAGS) -I./include -c _loader.c  $(SOURCES)

%.o:%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o asm/*.o

.PHONY: all clean print
