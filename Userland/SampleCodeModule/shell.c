#include <shell.h>
#include <mainLib.h>
#include <libc.h>
#include <timeUtils.h>

int static runningState = 1;
int static fontColor = NICE_WHITE;
int static colors[] = {NICE_WHITE,NICE_RED,NICE_YELLOW,NICE_BLUE,NICE_GREEN,NICE_PINK};
enum colorPick {WHITE, RED, YELLLOW, BLUE, GREEN, PINK};

void shellWelcome();
void shellMainLoop();
void shellExit();
void help();
void printTime();

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
        else if (strcmp(command, "exit") == 0) 
            return;
        else{
            chFont(NICE_YELLOW);
            print("No entendi tu comando! escriba ");
            chFont(NICE_PINK);
            print("!help ");
            chFont(NICE_YELLOW);
            print("para mas informacion.\n");
            chFont(fontColor);
    
        }
    }
    return;
}
void printTime(){
    print("\n  El tiempo actual es: \n");
    print("   %d/%d/%d  %d-%d-%d\n\n", getDays(), getMonth(), getYear(), getHours(), getMinutes(), getSeconds());
}
void printLogo(){
    print("\n\n");
    print(" _______  _______  ___      ___      _______         _______  _______ \n");
    print("|       ||       ||   |    |   |    |       |       |       ||       |\n");
    print("|    _  ||   _   ||   |    |   |    |   _   | ____  |   _   ||  _____|\n");
    print("|   |_| ||  | |  ||   |    |   |    |  | |  ||____| |  | |  || |_____ \n");
    print("|    ___||  |_|  ||   |___ |   |___ |  |_|  |       |  |_|  ||_____  |\n");
    print("|   |    |       ||       ||       ||       |       |       | _____| |\n");
    print("|___|    |_______||_______||_______||_______|       |_______||_______|\n");
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
    print("Hola y bienvenido a Pollo-OS! Este es un trabajo practico especial para\n la materia Arquitectura de Computadoras.\n\n");
    print("Para conocer los comandos habilitados, escriba ");
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

void help(){
    scClear();
    chFont(NICE_YELLOW);
    print("   Todos los comandos comienzan con un signo de exclamacion!\n    Esta es la lista de los posibles parametros: \n\n");
    printCommandDesc("help", "Informacion de comandos");
    printCommandDesc("chess","Jugar una partida de ajedrez");
    printCommandDesc("time","Se imprime el tiempo actual");
    printCommandDesc("color (numero del 0 al 5 )","Cambiar color de la fuente");
    print("\n\n\n");
}

