
#include <kbDriver.h>
#include <lib.h>

static const char keyMap[128] =
    {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8',                   /* 9 */
        '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',              /* 19 */
        't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,                 /* 29   - Control */
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',                /* 39 */
        '\'', '`', 0, /*Left Shift*/ '\\', 'z', 'x', 'c', 'v', 'b', 'n', /* 49 */
        'm', ',', '.', '/', 0, /*Right Shift*/ '*',                      /*55*/
        0,                                                               /* Alt -56*/
        ' ',                                                             /* Space bar -57*/
        0,                                                               /* Caps lock -58*/
        /*- F1 key ... > */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                /* < ... F10 */
        0,                                                               /* Num lock -68*/
        0,                                                               /* Scroll Lock -69*/
        0,                                                               /* Home key -70*/
        17,                                                              /* Up Arrow -71*/
        0,                                                               /* Page Up -72*/
        '-',                                                             /* Minus -73*/
        18,                                                              /* Left Arrow */
        0,
        20,  /* Right Arrow */
        '+', /* Plus -78*/
        0,   /* 79 - End key*/
        19,  /* Down Arrow */
        0,   /* Page Down */
        0,   /* Insert Key */
        0,   /* Delete Key */
        0, 0, 0,
        0, /* F11 Key */
        0, /* F12 Key */
        0, /* All other keys are undefined */
};

static int buffer[BUFFER_SIZE] = {0};
static int readIndex = 0;
static int writeIndex = 0;
static int elemCount = 0;



void keyboardHandler()
{
    if (_inRead(0x64) != 0) // verificamos que se pueda leer del port
    {
        unsigned char keyCode = _inRead(0x60);
        if (keyCode & 0X80)
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
    int c;
    c = buffer[readIndex];
    readIndex = (readIndex + 1) % BUFFER_SIZE;
    elemCount--;
    return c;
}