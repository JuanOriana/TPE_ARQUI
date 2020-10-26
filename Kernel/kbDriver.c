
#include <kbDriver.h>
#include <lib.h>
#include <keyMap.h>

static int buffer[BUFFER_SIZE] = {0};
static int readIndex = 0;
static int writeIndex = 0;
static int elemCount = 0;


void keyboardHandler()
{
    if (_inRead(0x64) != 0) // Se puede leer el port?
    {
        unsigned char keyCode = _inRead(0x60); 
        if (keyCode & 0X80) // No es una tecla levantandose
        {
            return;
        }

        char c = keyMap[keyCode];
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