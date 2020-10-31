

#include <libc.h>
#include <mainLib.h>

// WRAPPEO DE FUNCIONES DE ASM Y ALGUNAS PRECISIONES PARA USO DE USUARIO

int printStd(char* buff, int length){
    return write(1, buff, length);
}

int printErr(char *buff, int length){
    return write(2, buff, length);
}

int putChar(char c){
    char buff[2] = {0};
    buff[0] = c;
    return write(1,buff,2);
}

int scan(char* buff, int length){
    return read(0,buff,length);
}

char getChar(){
    char buff[2] = {0};
    return read(0, buff, 2);
    return buff[0];
}