
#include <kbDriver.h>
#include <lib.h>
#include <keyMap.h>
#include <syscalls.h>

#define TRUE 1
#define FALSE 0

static char buffer[BUFF_SIZE] = {0};
static int rdIdx = 0; //Posicion de escritura
static int wrIdx = 0; //Posicion de lectura
static int activeSize = 0; //Elementos legibles en el buffer

void foo();
void (*keyFuncs[])() = {foo,foo};

static int isShifted=FALSE;
static int capsEnabled = FALSE;

void initKb(){
    isShifted = capsEnabled= FALSE;
    rdIdx = wrIdx = activeSize = 0;
}

void keyboardHandler(uint64_t rsp)
{
    if (_inRead(0x64) != 0) // Se puede leer el port?
    {
        unsigned char keyCode = _inRead(0x60); 

        if (keyCode>=F1 && keyCode<=F2){ //Tecla de funcion!
            (*keyFuncs[keyCode-F1])();
            return;
        }

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
        if (keyCode == CTRL){
            loadRegs((uint64_t*)rsp);
            return;
         }
        if (keyCode >= 58 || keyCode & 0X80) //No tiene representacion ascii y no es una tecla levantandose
            return;

        int shiftState =  isShifted==capsEnabled?0:1; //Uno solo esta encendido
        char c = scanToAscii[keyCode][shiftState];

        loadChar(c);

    }
}

void loadChar(char c){

    if (c == '\r') //Normal\izado de saltos de linea.
        c = '\n';

    if (c != 0)
    {
        buffer[wrIdx] = c;
        wrIdx = (wrIdx + 1) % BUFF_SIZE; //Ciclo circularmente por el buffer

        // Si no llene el buffer, aumento su tamaño, si lo llene, agrego igual pero pierdo su ultimo valor
        // "lectura artificial"
        if (activeSize < BUFF_SIZE)
            activeSize++;
        else
            rdIdx = (rdIdx + 1) % BUFF_SIZE;
    }
}


int dumpChar()
{
    if (activeSize <= 0) 
        return -1;

    int c = buffer[rdIdx];
    rdIdx = (rdIdx + 1) % BUFF_SIZE;
    activeSize--;
    return c;
}

int dumpBuffer(char* destination, int size){
    //Se dumpea la cantidad de elementos posibles!
    //Si la destinacion es muy pequeña el buffer NO se vacia, solo lee los elementos pertinentes

    // Si el tamaño es 0 ni si quiera es posible devolver un string legible!
    if (size<=0 || activeSize<=0)
        return -1;

    int idx=0;
    while (idx<size-1 && activeSize){
        destination[idx] = dumpChar();
        idx++;
    }
    destination[idx]=0;
    return idx;
}

void loadRegs(uint64_t* rsp){
    uint64_t * regs = getRegs();
    for (int i =0 ; i<15;i++)
        regs[i] = rsp[i];
}

int setKeyFun(int key, void (*f)())
{
    if (key>= F1 && key<=F2){ //Valor aceptados son hasta f2 (podria agregarse mas en un futuro)
        keyFuncs[key-F1]=f;
        return 0;
    }
    return -1;
}

int cleanKeyFun(int key){
    return setKeyFun(key,foo);
}

void foo(){
    return;
}