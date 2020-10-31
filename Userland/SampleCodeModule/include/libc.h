// WRAPPEO DE FUNCIONES DE ASM Y ALGUNAS PRECISIONES PARA USO DE USUARIO

#ifndef LIB_C_H
#define LIB_C_H

int print(char *str, ...) ;
int putChar(char c);
int scan(char *buff, int length);
char getChar();
int strlen(const char *s);
char *strcpy(char *destination, const char *source);
int atoi(char* str);

#endif