#include <game.h>
#include <board.h>
#include <timeUtils.h>
#include <mainLib.h>
#include <libc.h>
#include <stdlib.h>

#define LONG_CASTLING 3
#define SHORT_CASTLING 2
#define EN_PASS 4
#define LOG_MAX 1024
#define MOV_SIZE 4

int activeGame=0;
int playerWTime = 10*60;
int playerBTime = 10*60;
int boardRotation = 0;
int pieceCaptured = 0;
int isCastling = 0;
int isEnPass = 0;
// 1 blanco, -1 negro
int currentPlayer = 1;
int surrounded=0;
char* players[] = {"negro","","blanco"};
char log[LOG_MAX] = {0};
int logSize=0;
char initials[] = {'P','B','N','R','Q','K'};
int autoRotation = 0;

//Resulta mas conveniente por chequeos de jaques ir llevando posicion de los reyes (GUARDADO EN X,Y)
int wKingPos[2] = {4,7};
int bKingPos[2] = {4,0};
int checked =0;
int winner=0; // -1 gana negro / 0 esta en juego / 1 gana blanco / >1 tablas

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

    pieceCaptured = gameBoard[tY][tX] != 0;

    //Cargo inicial pieza
    if (logSize < LOG_MAX - MOV_SIZE)
    {
        if(isCastling){
            if(isCastling == SHORT_CASTLING){
            log[logSize++]='O';
            log[logSize++]='-';
            log[logSize++]='O';
            }
            //No es la notacion correcta pero hay que cambiar el log para que imprima de a 5?
            else {
                log[logSize++]='O';
                log[logSize++]='O';
                log[logSize++]='O';
            }
            log[logSize++]=0;
        }
        else {
        log[logSize++] = initials[abs(gameBoard[fY][fX]) - 1];
        //Cargo mov
        //if(pieceCaptured) { log[logSize++] = 'x';} SE ROMPE EL LOG
        log[logSize++] = to[0];
        log[logSize++] = '8' - tY;
        log[logSize++] = 0;
        }
    }

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
    //Promotion de peones
    if (gameBoard[fY][fX]==WPAWN && tY==7)
        gameBoard[fY][fX]=WQUEEN;
    if (gameBoard[fY][fX] == BPAWN &&tY == 0)
        gameBoard[fY][fX] = BQUEEN;

    if(isEnPass){
        isEnPass= 0;
        enPassant(fX,fY,tX,tY);
    }
    else if(isCastling){
        isCastling = 0;
        castling(fX,fY,tX,tY);
    }
    else{
        gameBoard[tY][tX] = gameBoard[fY][fX];
        gameBoard[fY][fX] = 0;
    }
}
void timeMainLoop()
{
    if (currentPlayer == WHITE){
        playerWTime -= 1;
        if (playerWTime < 0 || playerBTime - playerWTime > 60)
        {
            winner = BLACK;
            writer(0,"\n",3);  //Tengo que "echar" al jugador del scanf escribiendo en entrada estandar
            return;
        }
    }
    else {
        playerBTime -= 1;
        if (playerBTime<0 || playerWTime- playerBTime > 60){
            winner=WHITE;
            writer(0, "\n", 3);
            return;
        }
    }


    int wSecs = playerWTime % 60;
    int bSecs = playerBTime % 60;
    int wMins = playerWTime / 60;
    int bMins = playerBTime / 60;
    char timeW[6] = {0};
    char timeB[6] = {0};
    timeW[2] = timeB[2] = ':';
    timeW[4] = wSecs % 10+'0';
    timeW[3] = wSecs / 10 + '0';
    timeW[1] = wMins % 10 + '0';
    timeW[0] = wMins / 10 + '0';
    timeB[4] = bSecs % 10 + '0';
    timeB[3] = bSecs / 10 + '0';
    timeB[1] = bMins % 10 + '0';
    timeB[0] = bMins / 10 + '0';
    writeAtPos(1, "\b\b\b\b\b", 10, 620, 100);
    writeAtPos(1, "\b\b\b\b\b", 10, 800, 100);
    writeAtPos(1, " Blanco      ---        Negro ", 35, 610, 80);
    writeAtPos(1, timeW, 10, 620, 100);
    writeAtPos(1, timeB, 10, 800, 100);
}

void initializeGame(){
    wKingPos[0]=4;wKingPos[1]=7;bKingPos[0]=4;bKingPos[1]=0;
    activeGame=1;
    playerWTime=playerBTime=2*60;
    currentPlayer=1;
    surrounded=winner=checked=0;
    autoRotation=1;
    logSize=0;
    initializeBoard(gameBoard);
}

int wellFormatedIn(char* input){
    if (input[0] == 0 || input[1] == 0 || input[2] != 0)
        return 0;
    return 1;
}

int checkInput(char* from, char* to){

    //Mal formato?
    if (!wellFormatedIn(from)|| !wellFormatedIn(to))
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
    char* prevMov = logSize> 0 ? log + logSize - 4 : log;
    int flag = checkMove(gameBoard, fX, fY, tX, tY,prevMov);

    if (!flag)
        return -3;
    if(flag == LONG_CASTLING || flag == SHORT_CASTLING){ isCastling = flag;}
    if(flag == EN_PASS) { isEnPass = 1;}

    return 1;
}
void endGame(){
    timer(TIMER_STOP, 0, 0);
    chFont(0xDD5599);
    if (winner<=1){
        if (surrounded&&checked){
            print("\n                                                    ---- CHECK MATE ------\n");
        }
        print(" \n\n\n\n                                  El ganador fue el %s!!!\n\n",players[winner+1]);
    }
    else{
        print("\n                                                          TABLAS!\n");
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

int lastMoveRepeated(){
    if (logSize<3)
        return 0;
    int reps = 1;
    char* lastMove = log+ logSize-MOV_SIZE;
    for (int i =0; i<logSize-MOV_SIZE; i+=MOV_SIZE){
        if (strcmp(lastMove,log+i)==0)
            reps++;
        if (reps>=3)
            return 1;
    }
    return 0;
}

void checkConditions(){
    checked=surrounded=0;
    int * kingPos = currentPlayer==WHITE?wKingPos:bKingPos;
    checked= isAttacked(gameBoard,kingPos[0],kingPos[1],currentPlayer*-1);
    if (lastMoveRepeated()){
        winner=2;
        return;
    }
    // surrounded= isSurrounded(gameBoard,kingPos[0],kingPos[1],currentPlayer*-1);
    // // if (surrounded){
    //     if (checked)
    //         winner= currentPlayer*-1;
    //     //STALEMATE NO NECESARIAMENTE CUMPLE ESTA CONDICION
    //     // else
    //     //     winner=2;
    // }
    return;
}

void play(){
    //IMPLEMENTAR;
    char from[10];
    char to[10];
    int flag=0;
    timer(TIMER_START, 1, timeMainLoop);
    while(!winner){
        from[1]=to[0]=to[1]=0;
        scClear();
        chFont(0xF800DD);
        writeAtPos(1, "Rotacion automatica ", 30, 640, 300);
        writeAtPos(1, "\b\b\b\b\b\b\b\b\b", 10, 800, 300);
        if (autoRotation)
        {
            writeAtPos(1, "ACTIVADA", 10, 800, 300);
            boardRotation = currentPlayer==WHITE?0:180;
        }
        else{
            writeAtPos(1, "DESACTIVADA", 12, 800, 300);
            writeAtPos(1, "Usar rotate auto para reactivarla ", 40, 640, 320);
        }
        printBoard(gameBoard,boardRotation);
        chFont(WCOLOR);
        printLog();
        chFont(0xDD22DD);
        if (checked)
            print("\n\n    CHECK!\n");
        print("Mueve el %s", players[currentPlayer + 1]);
        chFont(WCOLOR);
        print("\nIngresa un movimiento, \"stop\" para pausar o \"rotate\" para rotar el tablero 90 grados: \n>>> ");
        scan("%s %s",from,to);
        if (winner) //EXISTE LA POSIBILIDAD QUE EL JUGADOR HAYA PERDIDO ESPERANDO UNA JUGADA
            break;
        if (strcmp(from, "stop") == 0){
            timer(TIMER_STOP, 0, 0);
            return;
        }
        else if(strcmp(from,"rotate")==0){
            if (strcmp(to,"auto")==0){
                autoRotation=1;
                boardRotation=currentPlayer+1;
            }
            else if(to[0]==0){
                autoRotation=0;
                rotateBoard();
            }
            scClear();
            printBoard(gameBoard,boardRotation);
            continue;

        }
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
    printBoard(gameBoard,boardRotation);
    endGame();
    return;
}

void welcomeMessage(){
    print("\n\n-----------------------------------------------------------------------------------------------------\n");
    chFont(0xF0FF33);
    print("                        Bienvenido a \"CHESS - The Game!\"\n\n\n");
    chFont(WCOLOR);
    print(" Este es un juego de ajedrez para dos jugadores con tiempo limitado.\n\n");
    chFont(0x00FFFF);
    print("////REGLAS\n\n");
    chFont(WCOLOR);
    print("-- Cada jugador tiene 10 minutos de juego total\n");
    print("-- Acabarse esos 10 minutos o tener una diferencia de mas de 1 minuto con el oponente\n");
    print("   implica perder al partida\n\n");
    print("-- Se ingresan los movimientos con coordenadas alfanumericas con el siguiente formato: \n");
    chFont(0xFCFF83);
    print("            (ORIGEN) (DESTINO)\n");
    chFont(WCOLOR);
    print(" Por ejemplo: \"A7 A5\" mueve la pieza de A7 a A5, si es valido el movimiento\n\n");
    print("-- Durante una partida se puede pausar usando el comando especial \"stop\"\n\n");
    print("-- Durante la partida se puede rotar la pantalla con el comando \"rotate\"\n\n");
    print("-- Siempre comienza a jugar el jugador blanco\n\n");
    print("-- La repeticion de una misma posicion 3 veces implica TABLAS\n\n");
    print("-- La rotacion automatica esta ACTIVADA por defecto\n");
    print("   rota una vez para desactivarla\n\n\n");
    chFont(0x00FFFF);
    print("////COMANDOS\n\n");
    chFont(WCOLOR);
    print("-- Los comandos van escritos sin usar \"!\". Puedes usar: \n\n");
    chFont(0x8899FF);
    print("  newgame");
    chFont(WCOLOR);
    print(" para comenzar un juego nuevo\n");
    chFont(0x8899FF);
    print("  continue");
    chFont(WCOLOR);
    print(" para continuar uno ya comenzado\n");
    chFont(0xDD4422);
    print("  exit");
    chFont(WCOLOR);
    print(" para salir de la aplicacion.\n\n");
    chFont(0xF0FF33);
    print("                      Gracias por jugar!!!\n\n");
    chFont(WCOLOR);
    print("-----------------------------------------------------------------------------------------------------");
    return;
}


void chess(){
    scClear();
    welcomeMessage();
    char command[120] = {0};
    while(1){
        print("\nCHESS - The Game\n");
        command[0] = 0;
        print(">>> ");
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
        else{
            chFont(0xF0FF33);
            print("\nNo entendi tu comando! proba con uno de estos: newgame - continue - exit\n");
            chFont(WCOLOR);
        }
    }
    return;
}

void printLog(){
    chFont(0xAAAAAA);
    print("\n------------------------------------LOG-----------------------------------------------\n");
    for (int i=0;i<logSize;i+=MOV_SIZE){
        if (i%(MOV_SIZE*2)==0){
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

void rotateBoard(){
    boardRotation= (boardRotation + 90)%360;
}

void castling(int fX, int fY, int tX,int tY){
    //Enroque corto
    if(tX == 7){
        gameBoard[fY][fX+1] = gameBoard[tY][tX]; //Muevo la torre
        gameBoard[tY][tX] = EMPTY;
        gameBoard[tY][tX -1] = gameBoard[fY][fX];//muevo el rey
    }
    else{ //enroque largo
        gameBoard[fY][fX-1] = gameBoard[tY][tX]; 
        gameBoard[tY][tX] = EMPTY;
        gameBoard[tY][tX + 2] = gameBoard[fY][fX];
    }
    gameBoard[fY][fX] = EMPTY;

}

void enPassant(int fX, int fY, int tX,int tY){
    
    //Como el peon contrario
    gameBoard[fY][tX] = EMPTY;
    //Muevo mi peon
    gameBoard[tY][tX] = gameBoard[fY][fX];
    gameBoard[fY][fX] = EMPTY;
}


