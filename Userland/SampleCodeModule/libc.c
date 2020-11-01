

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
                    intToStr(va_arg(args, int),tmp,10);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
                case 's':
                {
                    str_arg = (char *)va_arg(args, char *);
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
                bufferIdx++;
            }
        }
        else
        {
            fmtIdx++;
            switch (format[fmtIdx])
            {
                case 'd':
                    *(int *)va_arg(args, int *) = strToInt(&buffer[bufferIdx], &auxNum);
                    bufferIdx += auxNum;
                    break;
                case 'c':
                    *(char *)va_arg(args, char *) = buffer[bufferIdx];
                    bufferIdx++;
                    break;
                case 's': //String hasta espacio
                    auxStr = (char *)va_arg(args, char *);
                    strcpyTilSpace(auxStr,&buffer[bufferIdx]);
                    bufferIdx += strlen(auxStr);
                    break;

                default:
                    flag = -1;
                    break;
                
            }
        }
        fmtIdx++;
    }
    va_end(args);
    return bufferIdx;
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

 //Copia del destino HASTA el espacio
 char *strcpyTilSpace(char *destination, const char *source)
 {


     char *ptr = destination;

     while (*source != '\0' && *source!= ' ')
     {
         *destination = *source;
         destination++;
         source++;
     }

     *destination = '\0';
     return ptr;
 }

 int strcmp(const char *str1, const char *str2)
 {
     if (str1==0 || str2==0)
        return 0;

     while (*str1)
     {
         
         if (*str1 != *str2)
             break;

         str1++;
         str2++;
     }

     return *(const unsigned char *)str1 - *(const unsigned char *)str2;
 }

 //https://www.geeksforgeeks.org/write-your-own-atoi/
 int strToInt(char *str, int* size)
 {

    *size=0;
     int res = 0;
     int i = 0;

     for (; str[i] != '\0'; i++)
     {
         if (str[i] < '0' || str[i] > '9')
             return res;
         res = res * 10 + str[i] - '0';
         *size += 1;
     }

     return res;
}

void swap(char *x, char *y)
{
    char t = *x;
    *x = *y;
    *y = t;
}

// function to reverse buffer[i..j]
char *reverse(char *buffer, int i, int j)
{
    while (i < j)
        swap(&buffer[i++], &buffer[j--]);

    return buffer;
}

// Iterative function to implement itoa() function in C
char *intToStr(int value, char *buffer, int base)
{
    // invalid input
    if (base < 2 || base > 32)
        return buffer;

    // consider absolute value of number
    int n = abs(value);

    int i = 0;
    while (n)
    {
        int r = n % base;

        if (r >= 10)
            buffer[i++] = 65 + (r - 10);
        else
            buffer[i++] = 48 + r;

        n = n / base;
    }

    // if number is 0
    if (i == 0)
        buffer[i++] = '0';

    // If base is 10 and value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10)
        buffer[i++] = '-';

    buffer[i] = '\0'; // null terminate string

    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}

void clearBuff(){
    buffSize = 0;
    do {
        reader(0,buffer,512);
    }
    while (getChar()!=-1);
}

int abs(int num){
    return num < 0? -num : num;
}