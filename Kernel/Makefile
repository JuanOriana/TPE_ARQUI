include Makefile.inc

KERNEL=kernel.bin
SOURCES=$(wildcard *.c)
SOURCES_ASM=$(wildcard asm/*.asm)
SOURCES_DRIVERS=$(wildcard drivers/*.c)
SOURCES_INT_EXT=$(wildcard interruptsAndExtensions/*.c)
SOURCES_MEM_EXT=$(wildcard memory/*.c)
SOURCES_PROCESS_EXT=$(wildcard processes/*.c)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_DRIVERS=$(SOURCES_DRIVERS:.c=.o)
OBJECTS_INT_EXT=$(SOURCES_INT_EXT:.c=.o)
OBJECTS_MEM_EXT=$(SOURCES_MEM_EXT:.c=.o)
OBJECT_PROCESS_EXT=$(SOURCES_PROCESS_EXT:.c=.o)

LOADERSRC=loader.asm

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: $(KERNEL)

# $@ representa lo que previo a los :
# $^ representa TODOS los prerrequisitos
$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM) $(OBJECTS_DRIVERS) $(OBJECTS_INT_EXT) $(OBJECTS_MEM_EXT) $(OBJECT_PROCESS_EXT)
	$(LD) $(LDFLAGS) -T kernel.ld -o $@ $^

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

clean:
	rm -rf asm/*.o *.o *.bin drivers/*.o interruptsAndExtensions/*.o

.PHONY: all clean
