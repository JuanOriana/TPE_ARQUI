

#include <libc.h>
#include <mainLib.h>
#include <stdarg.h>

// WRAPPEO DE FUNCIONES DE ASM Y ALGUNAS PRECISIONES PARA USO DE USUARIO

#define BUFFER_SIZE 512
char buffer[BUFFER_SIZE] = {0};
int buffSize=0;
int print(char *str, ...)
{
    va_list args;
    int i = 0, j = 0;  // i lectura en str  - j pos en buffer
    char buff[100] = {0}, tmp[20];
    char *str_arg;
    va_start(args, str);
    while (str && str[i])
    {
        if (str[i] == '%')
        {
            i++;
            switch (str[i])
            {
                case 'c':
                {
                    buff[j] = (char)va_arg(args, int);
                    j++;
                    break;
                }
                case 'd':
                {
                    intToStr(tmp, va_arg(args, int));
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
                case 's':
                {
                    str_arg = va_arg(args, char *);
                    strcpy(&buff[j], str_arg);
                    j += strlen(str_arg);
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
    writer(1,buff,j);
    va_end(args);
    return j;
}


int putChar(char c){
    char buff[2] = {0};
    buff[0] = c;
    return writer(1,buff,2);
}

int readLn()
{
    int c;

    while ((c = getChar()) != '\n' )
    {
        if (c == '\b')
        {
            if (buffSize > 0)
            {
                buffSize--;
                putChar('\b');
            }
        }
        else if (c != -1)
        {
            if (buffSize < BUFFER_SIZE - 1)
            {
                buffer[buffSize++] = c;
            }
            putChar(c);
        }
    }
    putChar('\n');
    buffer[buffSize++] = '\0';
    return buffSize;
}

int scan(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    clearBuff();
    readLn();
    int fmtIdx = 0;
    int bufferIdx=0;
    int ret=0;
    int flag = 0;

    char *auxStr;
    int auxNum =0;
    while (format[fmtIdx] != '\0' &&  buffer[bufferIdx] != '\0' && !flag)
    {
        if (format[fmtIdx] != '%')
        {
            if (format[fmtIdx] != buffer[bufferIdx])
            {
                flag = -1;
            }
            else
            {
                fmtIdx++;
                bufferIdx++;
            }
        }
        else
        {
            fmtIdx++;
            switch (format[fmtIdx])
            {
            case 'd':
            case 'i':
                *(int *)va_arg(args, int *) = strToInt(&buffer[bufferIdx], &auxNum);
                bufferIdx += auxNum;
                ret++;
                break;
            case 'c':
                *(char *)va_arg(args, char *) = buffer[bufferIdx];
                bufferIdx++;
                ret++;
                break;
            case 's': //String hasta espacio
                auxStr = va_arg(args, char *);
                strcpy(auxStr,& buffer[bufferIdx]);
                bufferIdx += strlen(auxStr);
                break;

            default:
                flag = -1;
                break;
            }
        }
    }
    return ret * flag;
}

int getChar()
{
    char buff[2] = {0};
    int ret = reader(0, buff, 2);
    if (ret <= 0)
        return -1;
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

 //https://www.geeksforgeeks.org/write-your-own-atoi/
 int strToInt(char *str, int* size)
 {
     if (*str == '\0')
         return 0;
    *size=0;
     int res = 0;
     int sign = 1;
     int i = 0;

     if (str[0] == '-')
     {
         sign = -1;
         i++;
         *size +=1;
     }
     for (; str[i] != '\0'; ++i)
     {
         if (str[i] <= '0' || str[i] >= '9')
             return sign * res;
         res = res * 10 + str[i] - '0';
         *size += 1;
     }

     return sign * res;
}

void clearBuff(){
    buffSize = 0;
    do {
        reader(0,buffer,512);
    }   
    while (getChar()!=-1);
}