#include <stdint.h>
#include <syscall.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE 6

 static const char *registers[] = {"RAX:", "RBX:", "RCX:"
 , "RDX:", "RBP:", "RDI:", "RSI:", "R8 :", "R9 :", "R10:", "R11:", "R12:", "R13:", "R14:", "R15:"};

//void printRegisters(uint64_t rip, uint64_t rsp);
void exceptionDispatcher(int exceptionSelector,uint64_t rsp){
    switch (exceptionSelector)
    {
    case ZERO_EXCEPTION_ID:
        sysWrite(2,"Excepcion: Division por cero\n",29);
        //PRINT REGISTROS
        break;
    case INVALID_OP_CODE:
        sysWrite(2,"Excepcion: Codigo Invalido\n",26);
        //PRINT REGISTROS
    default:
        break;
    }
    return ;
}

static void zero_division() {
	// Handler para manejar excepcíon
}

