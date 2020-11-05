#include <mainLib.h>
#include <board.h>
#include <libc.h>

void printPiece(int board[SIZE][SIZE],int i, int j);

int pawn[12] = {0xFFFF, 0x8001, 0x8001, 0xB001, 0xB871, 0xBFF1, 0xBFF1, 0xB871, 0xB001, 0x8001, 0x8001, 0xFFFF};
int rook[12] = {0xFFFF, 0x8001, 0xA071, 0xB8F1, 0xBFE1, 0xBFF1, 0xBFF1, 0xBFE1, 0xB8F1, 0xA071, 0x8001, 0xFFFF};
int bishop[12] = {0xFFFF, 0x8001, 0xE001, 0xF0C1, 0xFFF1, 0xFFFD, 0xFFCD, 0xFFD1, 0xF0C1, 0xE001, 0x8001, 0xFFFF};
int king[12] = {0xFFFF, 0x8001, 0xE001, 0xF091, 0xFFD1, 0xFFFD, 0xFFFD, 0xFFD1, 0xF091, 0xE001, 0x8001, 0xFFFF};
int queen[12] = {0xFFFF, 0x8001, 0xE031, 0xF0E1, 0xFFD9, 0xDDFF, 0xFFBB, 0xFFBB, 0xF0E1, 0xE031, 0x8001, 0xFFFF};
int knight[12] = {0xFFFF, 0x8001, 0xE1E1, 0x7CF1, 0xFBF9, 0xFFB9, 0xFFFB, 0xFFFB, 0xFFFB, 0xF8F9, 0x8001, 0xFFFF};
int empty[12] = {0xFFFF, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0xFFFF};

int checkPawn(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY);
int checkRook(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY);
int checkKnight(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY);
int checkBishop(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY);
int checkKing(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY);
int checkQueen(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY);

int initialBoard[SIZE][SIZE] = {
    {BROOK, BKNIGHT, BBISHOP, BQUEEN, BKING, BBISHOP, BKNIGHT, BROOK}, //0
    {BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN},
    {WROOK, WKNIGHT, WBISHOP, WQUEEN, WKING, WBISHOP, WKNIGHT, WROOK} //7
};

void initializeBoard(int board[SIZE][SIZE])
{

    for(int row = 0 ; row < SIZE ; row++){
        for(int col = 0 ; col < SIZE ; col++){
        board[row][col] = initialBoard[row][col];
        }
    }
}

int checkMove(int board[SIZE][SIZE], int fromX, int fromY, int toX, int toY)
{
    int flag = checkBounds(fromX, fromY) * checkBounds(toX,toY);
    if (!flag)
        return flag;

    int piece = board[fromY][fromX];
    if (piece==0)
        return 0;
    int side = piece / abs(piece);

    switch (piece)
    {
        case (WPAWN):
        case (BPAWN):
            return checkPawn(board,side,fromX,fromY,toX,toY);
            break;

        case(WROOK):
        case(BROOK):
            return checkRook(board,side,fromX,fromY,toX,toY);
            break;
        case(WKNIGHT):
        case(BKNIGHT):
            return checkKnight(board,side,fromX,fromY,toX,toY);
            break;
        case(WBISHOP):
        case(BBISHOP):
            return checkBishop(board,side,fromX,fromY,toX,toY);
            break;
        case(WQUEEN):
        case(BQUEEN):
            return checkQueen(board,side,fromX,fromY,toX,toY);
            break;
        case(WKING):
        case(BKING):
            return checkKing(board,side,fromX,fromY,toX,toY);
            break;
    }
    return 0;
}
int checkBounds(int x,int y){
    if(x<0 || x>SIZE-1 || y<0 || y>SIZE-1)
        return 0;
    return 1;
}

int checkPawn(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY)
{

    int absDistY = side*(fromY-toY);
    int absDistX = abs(toX-fromX);
    //Chequeos de movimiento vertical
    if (absDistY <= 0 || absDistY > 2
        || (side == BLACK && fromY != 1 && absDistY == 2) || (side == WHITE && fromY != 6 && absDistY == 2))
        return 0;

    //Chequeos de movimiento horizontal
    if (absDistX>1)
        return 0;
    if (absDistX==0)
        return board[toY][toX] == 0;
    return board[toY][toX]*side < 0;
}

int checkRook(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY)
{
    if (fromX!=toX){
        //si X cambia, y no puede hacerlo
        if (fromY!=toY)
            return 0;

        //Se mueve hacia la derecha?
        if(fromX < toX){
            //No puede haber piezas de fromX+1 a toX-1
            for (int x= fromX+1; x<toX;x++)
                if (board[toY][x]!=0)
                    return 0;
            return side*board[toY][toX]  <= 0;
        }
        else for(int x = fromX - 1; x >toX ; x--){
                if (board[toY][x]!=0)
                    return 0;
            return side*board[toY][toX]  <= 0;
        }
    }
    else
    {
        if (fromX != toX)
            return 0;

        //Idem en Y
        if(fromY < toX){
            for (int y= fromY+1; y<toY;y++)
                if (board[y][toX]!=0)
                    return 0;
            return side*board[toY][toX] <= 0;
        }
        else {
             for (int y= fromY-1; y>toY;y--)
                if (board[y][toX]!=0)
                    return 0;
            return side*board[toY][toX] <= 0;
        }
    }
    return -1;
}

int checkKnight(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY)
{
    int absDisX = abs(fromX - toX);
    int absDisY = abs(fromY - toY);
    //Chequeo 2 casilleros vertical y 1 horizontal o 2 horizontal y 1 vertical
    if((absDisX == 1 && absDisY == 2) || (absDisX == 2 && absDisY == 1)) {
        return side*board[toY][toX] <= 0;
     }
    return 0;
}

int checkBishop(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY)
{
    int absDisX = abs(fromX - toX);
    int absDisY = abs(fromY - toY);
    if(absDisX == 0 || absDisY == 0 || absDisX!=absDisY) { return 0;}
    //Tengo 4 casos, hacia esquina inf izq, inf der, sup izq, sup der
    //Caso 1; hacia sup der
    if(fromX < toX && fromY > toY){
        for(int i  =  fromX + 1; i < toX; i++){
            if(board[fromY - i + fromX][i] != 0) { return 0; }
        }
        return side*board[toY][toX] <= 0;
    }
    //Caso 2 : hacia inf izq
    if(fromX > toX && fromY < toY){
        for(int i  =  fromX -1 ; i > toX; i--){
            if(board[fromY - i + fromX][i] != 0) { return 0; }
        }
        return side*board[toY][toX] <= 0;
    }
    //Caso3 : hacia sup izq
    if(fromX > toX && fromY > toY){
        for(int i  =  fromX -1 ; i > toX; i--){
            if(board[fromY + i - fromX][i] != 0) { return 0; }
        }
        return side*board[toY][toX] <= 0;
    }
    //Caso 4 : hacia inf der
    if(fromX < toX && fromY < toY){
        for(int i  =  fromX + 1 ; i < toX; i++){
            if(board[fromY + i - fromX][i] != 0) { return 0; }
        }
        return side*board[toY][toX] <= 0;
    }
    return 0;
}

int checkKing(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY)
{
    int absDisX = abs(fromX - toX);
    int absDisY = abs(fromY - toY);
    if(absDisX <= 1  && absDisY <=1 && !(absDisY ==0 && absDisX==0)) { return side*board[toY][toX] <= 0;}
    return 0;
}

int checkQueen(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY)
{
    int absDisX = abs(fromX - toX);
    int absDisY = abs(fromY - toY);
    //El movimiento es recto?
    if(absDisX == 0 || absDisY == 0){
        return checkRook(board,side,fromX,fromY,toX,toY);
    }
    //Caso contrario es diagonal
    return checkBishop(board,side,fromX,fromY,toX,toY);
}
//Faltaria chequear si el rey ya se movio, quizas alguna variable booleana externa? Consultar con chicken little
int castling(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY)
{
    //Chequeo que parto de un rey y me dirijo hacia una torre
    //IF remplazable con flag de movimiento
    if((fromY != 0 || toY !=0) || (fromY!= 7 || toY !=7)
    || (fromX != 4 || toX !=7) || (fromX!= 4 || toX !=0)
    || (abs(board[fromY][toY]) != 6 )) { return 0;}

    if(side == BLACK) {
        //Enroque largo
        if(checkRook(board,side,0,0,3,0)) {
            //Primero muevo la torre, luego el rey
            // move(board,0,0,3,0); move(board,4,0,2,0);
            return 1;
        }
        //Enroque corto
        if(checkRook(board,side,7,0,5,0)) {
            // move(board,7,0,5,0); move(board,4,0,6,0);
            return 1;
        }
    }
    else {//Idem con rey blanco
        if(checkRook(board,side,0,7,3,7)) {
            // move(board,0,7,3,7); move(board,4,7,2,7);
            return 1;
        }
        //Enroque corto
        if(checkRook(board,side,7,7,5,7)) {
            // move(board,7,7,5,7); move(board,4,7,6,7);
            return 1;
        }
    }
    return 0;
}
//Devuelve si un lado tiene posibilidad de ataque sobre una celda en particular
int isAttacked(int board[SIZE][SIZE], int x, int y, int attacker)
{
    //Busco todas mis piezas en el tablero
    for (int i=0; i<SIZE;i++)
        for (int j=0; j<SIZE;j++)
            //Hay un movimiento legal de una de mis piezas?
            if (board[j][i] * attacker > 0 && checkMove(board, i, j, x, y))
                return 1;
    return 0;
}
//Devuelve si una pieza no tiene movimientos posibles a su alrededor
int isSurrounded(int board[SIZE][SIZE], int x, int y, int attacker){
    for (int i=-1;i<=1;i++){
        for (int j=-1;j<=1;j++){
            if (j==0&&i==0)
                continue;
            //Me puedo mover a un lugar que no este atacado?
            if (checkMove(board, x, y, x + i, y + j) && !isAttacked(board, x + i, y + j, attacker))
                return 0;
        }
    }
    return 1;

} 

void printBoard(int board[SIZE][SIZE], int rotation)
{
    switch (rotation)
    {
    case 0:
        for(int i = 0; i < SIZE; i++){
            print("%d",SIZE - i );
            for(int j = 0; j < SIZE ; j++){
                printPiece(board,j,i);
            }
            print("\n");
        }
        for(int i = 0 ;  i  < SIZE ; i++){
            print("  %c  ", 'A' + i);
        }
    break;

    case 90:
        for(int x = 0; x < SIZE; x++){
            print("%c",'A' + x );
            for(int y = SIZE - 1; y>=0 ; y--){
                printPiece(board,x,y);
            }
            print("\n");
        }
        for(int i = 1 ;  i  <= SIZE ; i++){
            print("  %d  ",  i);
        }
        break;
    case 180://180
         for(int y = SIZE - 1; y >= 0; y--){
            print("%d",SIZE - y );
            for(int x = SIZE -1; x>=0 ; x--){
                printPiece(board,x,y);
            }
            print("\n");
        }
        for(int i = 0 ;  i  < SIZE ; i++){
            print("  %c  ", 'H' - i);
        }
        break;
    case 270:
         for(int x = SIZE - 1; x >= 0; x--){
            print("%c",'A' + x );
            for(int y = 0; y < SIZE ; y++){
                printPiece(board,x,y);
            }
            print("\n");
        }
        for(int i = 0 ;  i  < SIZE ; i++){
            print("  %d  ", SIZE - i);
        }
        break;
    default:
        break;
    }
    print("\n");
}

void printPiece(int board[SIZE][SIZE],int x, int y)
{
    switch (abs(board[y][x]))
    {
        case PAWN:
            if(board[y][x] < 0) { chFont(BCOLOR);}
            drawFig(1,pawn);
            chFont(WCOLOR);
        break;

        case BISHOP:
            if(board[y][x] < 0) { chFont(BCOLOR);}
            drawFig(1,bishop);
            chFont(WCOLOR);
                break;

            case KNIGHT:
                if(board[y][x] < 0) { chFont(BCOLOR);}
                drawFig(1,knight);
                chFont(WCOLOR);
                break;

            case ROOK:
                if(board[y][x] < 0) { chFont(BCOLOR);}
                drawFig(1,rook);
                chFont(WCOLOR);
                break;

            case QUEEN:
                if(board[y][x] < 0) { chFont(BCOLOR);}
                drawFig(1,queen);
                chFont(WCOLOR);
                break;

            case KING:
                if(board[y][x] < 0) { chFont(BCOLOR);}
                drawFig(1,king);
                chFont(WCOLOR);
                break;

            case EMPTY:
                drawFig(1,empty);
                break;
            default: break;
    }
}
