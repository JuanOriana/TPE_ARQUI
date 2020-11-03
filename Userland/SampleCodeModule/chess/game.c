#include <game.h>
#include <board.h>
#include <timeUtils.h>
#include <mainLib.h>
#include <libc.h>

int activeGame=0;
int player1Time = 60;
int player2Time = 60;
int currentTurn = 1;

static int gameBoard[SIZE][SIZE] ={
    {BROOK,BKNIGHT,BBISHOP,BQUEEN,BKING,BBISHOP,BKNIGHT,BROOK}, //0
    {BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,BPAWN},
    {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
    {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
    {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
    {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
    {WPAWN,WPAWN,WPAWN,WPAWN,WPAWN,WPAWN,WPAWN,WPAWN},
    {WROOK,WKNIGHT,WBISHOP,WQUEEN,WKING,WBISHOP,WKNIGHT,WROOK}  //7
};


int movePiece(int fromX, int fromY, int toX, int toY)
{
    int fX = fromX - 'A';
    int tX = toX - 'A';
    int fY = 8 -(fromY - '0');
    int tY = 8 - (toY - '0');
    if (checkMove(gameBoard, fX, fY, tX, tY))
    {
        gameBoard[tY][tX] = gameBoard[fY][fX];
        gameBoard[fY][fX] = 0;
        return 1;
    }
    return 0;
}

void initializeGame(){
    activeGame=1;
    player1Time=player2Time=60;
    currentTurn=1;
    initializeBoard(gameBoard);
}

void play(){
    //IMPLEMENTAR;
    scClear();
    printBoard(gameBoard);
    hold(3);
    scClear();
    movePiece('A', '7', 'A', '5');
    printBoard(gameBoard);
    return;
}

void welcomeMessage(){
    chFont(WCOLOR);
    print("Bienvenido a \"CHESS - The Game!\"\n\n\n");
    print("Este es un juego de ajedrez para dos jugadores con un minuto de tiempo maximo por jugador.\n\n");
    print("Puedes usar ");
    chFont(0x8844FF);
    print("newgame");
    chFont(WCOLOR);
    print(" para comenzar un juego nuevo, ");
    chFont(0x8844FF);
    print("continue");
    chFont(WCOLOR);
    print(" para continuar uno ya comenzado o ");
    chFont(0xFF00);
    print("exit");
    chFont(WCOLOR);
    print(" para salir de la aplicacion.\n Gracias por jugar!!!\n\n\n");
    return;
}


void chess(){
    scClear();
    welcomeMessage();
    char command[120] = {0};
    while(1){
        print("\n\nCHESS - The Game\n");
        command[0] = 0;
        scan("%s", command);
        if (strcmp(command,"newgame")==0){
            initializeGame();
            play();
        }
        else if (strcmp(command,"continue")==0){
            if (activeGame)
                play();
            else
                print("No se comenzo un juego!\n");
        }
        else if (strcmp(command,"exit")==0){
            scClear();
            return;
        }
        else
            print("No entendi tu comando! proba con uno de estos: newgame - continue - exit\n");
    }
    return;
}