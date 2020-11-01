#include <shell.h>
#include <mainLib.h>
#include <libc.h>

int static runningState = 1;
int static fontColor = NICE_WHITE;
int static colors[] = {NICE_WHITE,NICE_RED,NICE_YELLOW,NICE_BLUE,NICE_PINK};
enum colorPick {WHITE, RED, YELLLOW, BLUE, PINK};

void shellWelcome();
void shellMainLoop();
void shellExit();
void help();

void shellRun(){
    
    shellWelcome();
    shellMainLoop();
    shellExit();
}

void shellMainLoop(){
    char command[120] = {0};
    char param[120] = {0};
    int aux=0;
    while (runningState){
        print("$  > ");
        command[0]=0;
        param[0]=0;

        scan("\\%s %s",command,param);
        if (strcmp(command,"help")==0)
            help();
        else if (strcmp(command,"color")==0){
            int newColor = strToInt(param,&aux);
            fontColor = colors[newColor];
            chFont(fontColor);
            } 
        else{
            chFont(NICE_YELLOW);
            print("No entendi tu comando! escriba ");
            chFont(NICE_PINK);
            print("\\help ");
            chFont(fontColor);
            print("para mas informacion.\n");

        }




    }
    return;
}

void shellExit(){
    return;
}

void shellWelcome()
{
    scClear();
    chFont(NICE_YELLOW);
    print(" _______  _______  ___      ___      _______         _______  _______ \n");
    print("|       ||       ||   |    |   |    |       |       |       ||       |\n");
    print("|    _  ||   _   ||   |    |   |    |   _   | ____  |   _   ||  _____|\n");
    print("|   |_| ||  | |  ||   |    |   |    |  | |  ||____| |  | |  || |_____ \n");
    print("|    ___||  |_|  ||   |___ |   |___ |  |_|  |       |  |_|  ||_____  |\n");
    print("|   |    |       ||       ||       ||       |       |       | _____| |\n");
    print("|___|    |_______||_______||_______||_______|       |_______||_______|\n");
    print("\n\n\n\n");
    print("Hola y bienvenido a Pollo-OS! Este es un trabajo practico especial para\n la materia Arquitectura de Computadoras.\n\n");
    print("Para conocer los comandos habilitados, escriba ");
    chFont(NICE_PINK);
    print("\\help \n\n\n");
    chFont(NICE_WHITE);
}

void printCommandDesc(char *name, char *desc)
{
    chFont(NICE_GREEN);
    print("\\%s  ---  ", name);
    chFont(NICE_PINK);
    print("%s\n", desc);
    chFont(fontColor);
}

void help(){
    scClear();
    chFont(NICE_YELLOW);
    print("   Todos los comandos comienzan con backslash!\n    Esta es la lista de los posibles parametros: \n\n");
    printCommandDesc("help", "Informacion de comandos");
    printCommandDesc("chess","Jugar una partida de ajedrez");
    printCommandDesc("time","Se imprime el tiempo actual");
    printCommandDesc("color (numero del 0 al 5 )","Cambiar color de la fuente");
    print("\n\n\n");
}
