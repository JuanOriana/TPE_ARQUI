#include <game.h>
#include <board.h>
#include <timeUtils.h>
#include <mainLib.h>
#include <libc.h>
#include <stdlib.h>

int activeGame=0;
int player1Time = 60;
int player2Time = 60;
// 1 blanco, -1 negro
int currentPlayer = 1;
int surrounded=0;
char* players[] = {"negro","","blanco"};

char log[512] = {0};
int logSize=0;
char initials[] = {'P','B','N','R','Q','K'};

//Resulta mas conveniente por chequeos de jaques ir llevando posicion de los reyes (GUARDADO EN X,Y)
int wKingPos[2] = {4,7};
int bKingPos[2] = {4,0};
int checked =0;
int winner=0; // -1 gana negro / 0 esta en juego / 1 gana blanco / >1 tablas

static int gameBoard[SIZE][SIZE] = {
    {BROOK, BKNIGHT, BBISHOP, BQUEEN, BKING, BBISHOP, BKNIGHT, BROOK}, //0
    {BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN},
    {WROOK, WKNIGHT, WBISHOP, WQUEEN, WKING, WBISHOP, WKNIGHT, WROOK} //7
};

void movePiece(char *from, char *to)
{
    if (from[0] >= 'A' && from[0] <= 'Z')
        from[0] += ('a' - 'A');
    if (to[0] >= 'A' && to[0] <= 'Z')
        to[0] += ('a' - 'A');

    int fX = from[0] - 'a';
    int tX = to[0] - 'a';
    int fY = 8 - (from[1] - '0');
    int tY = 8 - (to[1] - '0');

    //Cargo inicial pieza
    log[logSize++] = initials[abs(gameBoard[fY][fX]) - 1];
    //Cargo mov
    log[logSize++] = to[0];
    log[logSize++] = tY + '0';
    log[logSize++] = 0;

    //Asumo que no es MI rey porque el movimiento debe ser valido
    if (abs(gameBoard[tY][tX])==KING)
        winner=currentPlayer;

    if (gameBoard[fY][fX]==WKING){
        wKingPos[0]=tX;
        wKingPos[1]=tY;
    }
    if (gameBoard[fY][fX] == BKING)
    {
        bKingPos[0] = tX;
        bKingPos[1] = tY;
    }
    if (gameBoard[fY][fX]==WPAWN && tY==7)
        gameBoard[fY][fX]=WQUEEN;
    if (gameBoard[fY][fX] == BPAWN &&tY == 0)
        gameBoard[fY][fX] = BQUEEN;
    gameBoard[tY][tX] = gameBoard[fY][fX];
    gameBoard[fY][fX] = 0;
}

void initializeGame(){
    wKingPos[0]=4;wKingPos[1]=7;bKingPos[0]=3;bKingPos[1]=0;
    activeGame=1;
    player1Time=player2Time=60;
    currentPlayer=1;
    surrounded=winner=checked=0;
    logSize=0;
    initializeBoard(gameBoard);
}

int wellFormatedIn(char* input){
    if (input[0] == 0 || input[1] == 0 || input[2] != 0)
        return 0;
    return 1;
}

int  checkInput(char* from, char* to){

    //Mal formato?
    if (!wellFormatedIn(from)||!wellFormatedIn(to))
        return -1;

    int fX = from[0] - 'A';
    if (from[0]>='a' && from[0]<='z')
        fX+= ('A'-'a');
    int fY = 8 - (from[1] - '0');

    //La pieza no es de quien mueve?
    if (gameBoard[fY][fX] * currentPlayer < 0)
        return -2;

    int tX = to[0] - 'A';
    if (to[0] >= 'a' && to[0] <= 'z')
        tX += ('A' - 'a');
    int tY = 8 - (to[1] - '0');

    //Es valido el movimiento?
    int flag = checkMove(gameBoard, fX, fY, tX, tY);
    if (!flag)
        return -3;
    return 1;
}
void endGame(){
    chFont(0xDD5599);
    if (winner<=1){
        if (surrounded&&checked){
            print("\n                                                    ---- CHECK MATE ------\n");
        }
        print(" \n\n\n\n                                  El ganador fue el %s!!!\n\n",players[winner+1]);
    }
    else{
        print("\n                                                    TABLAS!\n");
        print("                                            Hubo empate por ");
        if (surrounded)
            print("rey ahogado\n\n");
        else
            print("jugadas repetidas\n\n");

    }
    print("                               Muchas gracias por jugar a \"Chess - The Game\". Nos vemos!\n");
    hold(6);
    scClear();
    chFont(WCOLOR);
    activeGame = 0;
}

void checkConditions(){
    checked=surrounded=0;
    int * kingPos = currentPlayer==WHITE?wKingPos:bKingPos;
    checked= isAttacked(gameBoard,kingPos[0],kingPos[1],currentPlayer*-1);
    surrounded= isSurrounded(gameBoard,kingPos[0],kingPos[1],currentPlayer*-1);
    if (surrounded){
        if (checked)
            winner= currentPlayer*-1;
        //STALEMATE NO NECESARIAMENTE CUMPLE ESTA CONDICION
        // else
        //     winner=2;
    }   
    return;
}

void play(){
    //IMPLEMENTAR;
    char from[4];
    char to[4];
    int flag=0;
    while(!winner){
        from[1]=0;
        to[1]=0;
        scClear();
        printBoard(gameBoard);
        chFont(0xDD22DD);
        if (checked)
            print("\n\n    CHECK!\n");
        print("Mueve el %s",players[currentPlayer+1]);
        chFont(WCOLOR);
        printLog();
        print("\nIngresa un movimiento o \"stop\" para pausar: ");
        scan("%s %s",from,to);
        if (strcmp(from,"stop")==0)
            return;
        flag = checkInput(from,to);
        switch (flag)
        {
            case -1:
                chFont(0xD9302E);
                print("ERROR - Movimiento mal formateado!\n");
                print("Uso (movs alfa-num): mov1 mov2\n");
                chFont(WCOLOR);
                hold(3);
                break;
            case -2:
                chFont(0xD9302E);
                print("ERROR - le toma jugar al %s\n",players[currentPlayer+1]);
                chFont(WCOLOR);
                hold(3);
                break;
            case -3:
                chFont(0xD9302E);
                print("ERROR - esto no es un movimiento valido de ajedrez");
                chFont(WCOLOR);
                hold(3);
                break;
            // no hubo erroes
            default:
                movePiece(from,to);
                currentPlayer *= -1;
                checkConditions();
                break;
        }
    } 

    scClear();
    printBoard(gameBoard);
    endGame();
    return;
}

void welcomeMessage(){
    chFont(0x00FFFF);
    print("Bienvenido a \"CHESS - The Game!\"\n\n\n");
    chFont(WCOLOR);
    print("Este es un juego de ajedrez para dos jugadores con tiempo limitado.\n\n");
    chFont(0xF0FF33);
    print("REGLAS\n\n");
    chFont(WCOLOR);
    print("-- Cada jugador tiene 1 minuto de juego total\n");
    print("-- Se ingresan los movimientos con coordenadas alfanumericas con el siguiente formato: \n\n");
    print("        (ORIGEN) (DESTINO)\n");
    print("Por ejemplo: \"A7 A5\" mueve la pieza de A7 a A5, si es valido el movimiento\n\n");
    print("-- Siempre comienza a jugar el jugador blanco\n\n\n");
    print("-- Durante una partida se puede pausar usando el comando especial \"stop\"");
    chFont(0xF0FF33);
    print("COMANDOS\n\n");
    chFont(WCOLOR);
    print("-- Los comandos van escritos sin usar \"!\". Puedes usar \n");
    chFont(0x8844FF);
    print("newgame");
    chFont(WCOLOR);
    print(" para comenzar un juego nuevo\n");
    chFont(0x8844FF);
    print("continue");
    chFont(WCOLOR);
    print(" para continuar uno ya comenzado\n");
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
        print(">>>");
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

void printLog(){
    chFont(0xAAAAAA);
    print("\n------------------------------------LOG-----------------------------------------------\n");
    for (int i=0;i<logSize;i+=4){
        if (i%8==0){
            chFont(WCOLOR);
        }
        else{
            chFont(BCOLOR);
        }
        
        print("%s ",log+i);
    }
    chFont(0xAAAAAA);
    print("\n--------------------------------------------------------------------------------------\n");
    chFont(WCOLOR);
}