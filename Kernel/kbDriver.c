
#include <kbDriver.h>
#include <lib.h>
#include <keyMap.h>

#define TRUE 1
#define FALSE 0
static int buffer[BUFFER_SIZE] = {0};
static int readIndex = 0;
static int writeIndex = 0;
static int elemCount = 0;

int isShifted=FALSE;
int capsEnabled=FALSE;

void initKb(){
    isShifted = capsEnabled= FALSE;
}


void keyboardHandler()
{
    if (_inRead(0x64) != 0) // Se puede leer el port?
    {
        unsigned char keyCode = _inRead(0x60); 

        if (keyCode==LSHIFT_PRESSED || keyCode==RSHIFT_PRESSED){
            isShifted=TRUE;
            return;
        }
        if (keyCode==LSHIFT_RELEASED || keyCode == RSHIFT_RELEASED){
            isShifted = FALSE;
            return;
        }
        if (keyCode == CAPSLOCK){
            capsEnabled = 1 - capsEnabled;
            return;
        }
        if (keyCode >= 58 || keyCode & 0X80) //No tiene representacion ascii y no es una tecla levantandose
            return;

        int shiftState =  isShifted==capsEnabled?0:1; //Uno solo esta encendido
        char c = scanToAscii[keyCode][shiftState];
        if (c != 0)
        {
            buffer[writeIndex] = c;
            writeIndex = (writeIndex + 1) % BUFFER_SIZE;
            if (elemCount < BUFFER_SIZE)
            {
                elemCount++;
            }
            else
            {
                readIndex = (readIndex + 1) % BUFFER_SIZE;
            }
        }
        
    }
}


int getChar()
{
    if (elemCount == 0)
    {
        return -1;
    }
    int c = buffer[readIndex];
    readIndex = (readIndex + 1) % BUFFER_SIZE;
    elemCount--;
    return c;
}