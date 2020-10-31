

#include <libc.h>
#include <mainLib.h>
#include <stdarg.h>

// WRAPPEO DE FUNCIONES DE ASM Y ALGUNAS PRECISIONES PARA USO DE USUARIO


int print(char *str, ...)
{
    va_list vl;
    int i = 0, j = 0;  // i lectura en str  - j pos en buffer
    char buff[100] = {0}, tmp[20];
    va_start(vl, str);
    while (str && str[i])
    {
        if (str[i] == '%')
        {
            i++;
            switch (str[i])
            {
                case 'c':
                {
                    buff[j] = (char)va_arg(vl, int);
                    j++;
                    break;
                }
                case 'd':
                {
                    intToStr(tmp,va_arg(vl,int));
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
            }
        }
        else
        {
            buff[j] = str[i];
            j++;
        }
        i++;
    }
    write(1,buff,j);
    va_end(vl);
    return j;
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

int strlen(const char *s)
{
    int i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}


char *strcpy(char *destination, const char *source)
{
    
    if (destination == (void *)0)
        return destination;

    char *ptr = destination;

    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';
    return ptr;
}
