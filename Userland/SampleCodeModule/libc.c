

#include <libc.h>
#include <mainLib.h>
#include <stdarg.h>

// WRAPPEO DE FUNCIONES DE ASM Y ALGUNAS PRECISIONES PARA USO DE USUARIO


char buffer[256]= {0};

int print(char *str, ...)
{
    va_list vl;
    int i = 0, j = 0;  // i lectura en str  - j pos en buffer
    char buff[100] = {0}, tmp[20];
    char *str_arg;
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
                case 's':
                {
                    str_arg = va_arg(vl, char *);
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
    write(1,buff,j);
    va_end(vl);
    return j;
}


int putChar(char c){
    char buff[2] = {0};
    buff[0] = c;
    return write(1,buff,2);
}

int scan(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    readLine(buffer);
    int buffIdx = 0;
    int fmtIdx = 0;

    int result = 0;
    int flag = 0;

    int auxIdx = 0;
    char *auxStr;
    int *auxNum;

    while (format[fmtIdx] != '\0' && buffer[buffIdx] != '\0' && !flag)
    {
        if (format[fmtIdx] != '%')
        {
            if (format[fmtIdx] != buffer[buffIdx])
            {
                flag = -1;
            }
            else
            {
                fmtIdx++;
                buffIdx++;
            }
        }
        else
        {
            fmtIdx++;
            switch (format[fmtIdx])
            {
            case 'd':
            case 'i':
                *(int *)va_arg(args, int *) = itoa(&buff[j], &out_loc, 10);
                buffIdx += out_loc - &buffer[buffIdx];
                fmtIdx++;
                break;
            case 'c':
                *(char *)va_arg(args, char *) = buffer[j];
                j++;
                ret++;
                break;
            case 's': //String hasta espacio
                auxStr = va_arg(args, char *);
                auxIndex = bufferIndex;
                while (buffer[bufferIndex] != ' ' && buffer[bufferIndex] != '\0')
                {
                    *auxStr = buffer[bufferIndex];
                    auxStr++;
                    bufferIndex++;
                }
                if (bufferIndex > auxIndex)
                {
                    auxStr[auxIndex] = '\0';
                    result++;
                }
                else
                {
                    auxStr[auxIndex] = '\0';
                    flag = 1;
                }
                formatIndex++;
                break;

            default:
                flag = -1;
                break;
            }
        }
        return flag;
    }

    char getChar()
    {
        char buff[2] = {0};
        return read(0, buff, 2);
        return buff[0];
    }

    int strlen(const char *s)
    {
        int i;
        for (i = 0; s[i] != '\0'; i++)
            ;
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
