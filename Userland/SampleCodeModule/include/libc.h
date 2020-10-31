// WRAPPEO DE FUNCIONES DE ASM Y ALGUNAS PRECISIONES PARA USO DE USUARIO

#ifndef LIB_C_H
#define LIB_C_H

int print(char *str, ...) ;
int putChar(char c);
int scan(const char *format, ...);
int getChar();
int readLn();
int strlen(const char *s);
char *strcpy(char *destination, const char *source);
int strToInt(char *str, int *size);
void clearBuff();

#endif
