#include <shell.h>
#include <mainLib.h>
#include <libc.h>
#include <timeUtils.h>
#include <game.h>

int static runningState = 1;
int static fontColor = NICE_WHITE;
int static colors[] = {NICE_WHITE,NICE_RED,NICE_YELLOW,NICE_BLUE,NICE_GREEN,NICE_PINK};
enum colorPick {WHITE, RED, YELLLOW, BLUE, GREEN, PINK};
static const char *registers[] = {"RAX:", "RBX:", "RCX:", "RDX:", "RBP:", "RDI:", "RSI:", "R8 :", "R9 :", "R10:", "R11:", "R12:", "R13:", "R14:", "R15:"};
void shellWelcome();
void shellMainLoop();
void shellExit();
void help();
void printTime();
void printMem(char *hexa);
void printRegisters();
void divExc();

void shellRun()
{

    shellWelcome();
    shellMainLoop();
    shellExit();
    return;
}

void shellMainLoop(){
    char command[120] = {0};
    char param[120] = {0};
    int aux=0;
    while (runningState){
        print("$  > ");
        command[0]=0;
        param[0]=0;

        scan("!%s %s",command,param);
        if (strcmp(command,"help")==0)
            help();
        else if (strcmp(command,"color")==0){
            int newColor = strToInt(param,&aux);
            if (newColor<0 || newColor>PINK) //PINK == color maximo
                continue;
            fontColor = colors[newColor];
            chFont(fontColor);
            }
        else if (strcmp(command,"time")==0)
            printTime();
        else if(strcmp(command,"clear")==0)
            scClear();
        else if (strcmp(command, "printmem") == 0){
            if (param[0]=='0'&& param[1]=='x')
                printMem(param);
            else print("Se necesita un parametro en hexa valido\n");
        }
        else if (strcmp(command, "chess") == 0)
            chess();
        else if (strcmp(command, "inforeg") == 0)
            printRegisters();
        else if (strcmp(command,"divex") == 0)
            divExc();
        else if(strcmp(command,"opex")==0)
            opCodeExc();
        else if (strcmp(command, "exit") == 0)
            return;
        else{
            chFont(NICE_YELLOW);
            print("   No entendi tu comando! escriba ");
            chFont(NICE_PINK);
            print("!help ");
            chFont(NICE_YELLOW);
            print("para mas informacion.\n");
            chFont(fontColor);
    
        }
    }
    return;
}

void printLogo(){
    print("\n\n");
    print("       __//      _______  _______  ___      ___      _______         _______  _______ \n");
    print("      /.__.\\    |       ||       ||   |    |   |    |       |       |       ||       |\n");
    print("      \\ \\/ /    |    _  ||   _   ||   |    |   |    |   _   | ____  |   _   ||  _____|\n");
    print("   \'__/    \\    |   |_| ||  | |  ||   |    |   |    |  | |  ||____| |  | |  || |_____ \n");
    print("    \\-      )   |    ___||  |_|  ||   |___ |   |___ |  |_|  |       |  |_|  ||_____  |\n");
    print("     \\_____/    |   |    |       ||       ||       ||       |       |       | _____| |\n");
    print("  _____|_|____  |___|    |_______||_______||_______||_______|       |_______||_______|\n");
    print("\n\n\n\n");
}

void shellExit(){
    
    scClear();
    chFont(NICE_YELLOW);
    printLogo();
    print("\n\n\n");
    chFont(NICE_BLUE);
    print("      Muchas gracias por usar Pollo-OS! Nos vemos!");
    hold(5);
    scClear();

    return;
}

void shellWelcome()
{
    scClear();
    chFont(NICE_YELLOW);
    printLogo();
    print("   Hola y bienvenido a Pollo-OS! Este es un trabajo practico especial para\n la materia Arquitectura de Computadoras.\n\n");
    print("   Para conocer los comandos habilitados, escriba ");
    chFont(NICE_PINK);
    print("!help \n\n\n");
    chFont(NICE_WHITE);
}

void printCommandDesc(char *name, char *desc)
{
    chFont(NICE_GREEN);
    print("!%s  ---  ", name);
    chFont(NICE_PINK);
    print("%s\n", desc);
    chFont(fontColor);
}

void printMem(char* hexa){
    long long address = hexaToInt(hexa);
    unsigned char buff[33];
    char byte[10];
    getMem(buff,address,32);
    print("\n");
    print("Memoria en address %s :\n\n",hexa);
    for (int i=0;i<32;i++){
        if (i==16)
            print("\n");
        intToHexa((char)buff[i], byte, 1);
        print("%s ", byte);
    }
    print("\n\n");
}

void printRegisters(){
    unsigned long long buff[17];
    char hexa[20];
    print("\n");
    getRegs(buff);
    for (int i=14;i>=0;i--){
        intToHexa((long long)buff[i],hexa,8);
        chFont(NICE_YELLOW);
        print("%s",registers[14-i]);
        chFont(NICE_WHITE);
        print("%s\n",hexa);
        chFont(fontColor);
    }
    print("\n\n");
}

void help(){
    chFont(NICE_YELLOW);
    print("   Todos los comandos comienzan con un signo de exclamacion!\n    Esta es la lista de los posibles parametros: \n\n");
    printCommandDesc("help", "Informacion de comandos");
    printCommandDesc("chess","Jugar una partida de ajedrez");
    printCommandDesc("time","Se imprime el tiempo actual");
    printCommandDesc("clear", "Se limpia la pantalla");
    printCommandDesc("color (numero del 0 al 5 )","Cambiar color de la fuente");
    printCommandDesc("printmem (direcciones)","Dump de 32 bytes desde la direccion dada");
    printCommandDesc("inforeg","Se imprime el valor de los registros capturados con CTRL");
    printCommandDesc("divex","Para lanzar una excepcion por division por cero");
    printCommandDesc("opex","Para lanzar una excepcion por operador de codigo invalido");
    printCommandDesc("exit","Finaliza la ejecucion");
    print("\n\n\n");
    chFont(fontColor);
}

// N positivo!
void printTwoDig(int n){
    char num[3] ={0};
    num[0]=n/10+'0';
    num[1]=n%10+'0';
    print("%s",num);
}

void printTime()
{
    chFont(NICE_YELLOW);
    print("\n  El tiempo actual es: \n\n");
    chFont(NICE_BLUE);
    print("     ");
    printTwoDig(getDays());
    print("/");
    printTwoDig(getMonth());
    print("/%d  ",getYear());
    printTwoDig(getHours());
    print(":");
    printTwoDig(getMinutes());
    print(":");
    printTwoDig(getSeconds());
    print("\n\n");
    chFont(fontColor);
}

void divExc(){
    int a = 1, b = 0 ;
    a = a/b;
}
