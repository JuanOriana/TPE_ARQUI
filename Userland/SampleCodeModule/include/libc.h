// WRAPPEO DE FUNCIONES DE ASM Y ALGUNAS PRECISIONES PARA USO DE USUARIO

#ifndef LIB_C_H
#define LIB_C_H

#define SEC 0
#define MIN 1

//IN: String, Parametros variables (formatos)
//OUT: Longitud del string
int print(char *str, ...) ;

int putChar(char c);
int scan(const char *format, ...);
int getChar();
int readLn();
int strlen(const char *s);
char *strcpy(char *destination, const char *source);
char *strcpyTilSpace(char *destination, const char *source);
int strToInt(char *str, int *size);
char *intToStr(int num, char *str, int base);
void clearBuff();
int abs(int n);
int strcmp(const char *str1, const char *str2);

#endif
