#define WHITE 1
#define BLACK -1
enum wpieces {WPAWN=1,WBISHOP=2,WKNIGHT=3,WROOK=4,WQUEEN=5,WKING=6};
enum bpieces {BPAWN=-1,BBISHOP=-2,BKNIGHT=-3,BROOK=-4,BQUEEN=-5,BKING=-6};

#define SIZE 8

char board[SIZE][SIZE] ={
    {BROOK,BKNIGHT,BBISHOP,BQUEEN,BKING,BBISHOP,BKNIGHT,BROOK}, //0
    {BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,BPAWN},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {WPAWN,WPAWN,WPAWN,WPAWN,WPAWN,WPAWN,WPAWN,WPAWN},
    {WROOK,WKNIGHT,WBISHOP,WQUEEN,WKING,WBISHOP,WKNIGHT,WROOK}  //7
};


int move(int fromX, int fromY, int toX, int toY){
    board[toY][toX] = board[fromY][fromX];
    board[fromY][fromX] = 0;
}

int checkMove(int fromX, int fromY, int toX, int toY)
{

    int piece = board[fromY][fromX];
    int side = piece / abs(piece);

    int flag = checkBounds(toX,toY);
    if (!flag)
        return flag;

    switch (piece)
    {
        case (WPAWN):
        case (BPAWN):
                checkPawn(side,fromX,fromY,toX,toY);
            return flag;
            break;

        case(WROOK):
        case(BROOK):
            return checkRook(side,fromX,fromY,toX,toY);
            break;
        case(WKNIGHT):
        case(BKNIGHT):
            return checkKnight(side,fromX,fromY,toX,toY);
            break;
        case(WBISHOP):
        case(BBISHOP):
            return checkBishop(side,fromX,fromY,toX,toY);
            break;
        case(WQUEEN):
        case(BQUEEN):
            return checkQueen(side,fromX,fromY,toX,toY);
            break;
        case(WKING):
        case(BKING):
            return checkKing(side,fromX,fromY,toX,toY);
            break;
    }
}
int checkBounds(int x,int y){
    if(x<0 || x>SIZE-1 || y<0 || y>SIZE-1)
        return -1;
    return 0;
}

int checkPawn(int side, int fromX, int fromY, int toX, int toY)
{

    int absDistY = side*(toY - fromY);
    int absDistX = abs(toX-fromX);
    //Chequeos de movimiento vertical
    if (side * (absDistY) <= 0 || absDistY > 2
        || (side == BLACK && fromY != 1 && absDistY == 2) || (side == WHITE && fromY != 6 && absDistY == 2))
        return 0;

    //Chequeos de movimiento horizontal
    if (absDistX>1)
        return 0;
    if (absDistX==0)
        return board[toY][toX] == 0;
    return board[toY][toX]*side < 0;
}

int checkRook(int side, int fromX, int fromY, int toX, int toY ){
    if (fromX!=toX){
        //si X cambia, y no puede hacerlo
        if (fromY!=toY)
            return 0;

        //Se mueve hacia la derecha?
        if(fromX < toX){
            //No puede haber piezas de fromX+1 a toX-1
            for (int x= fromX+1; x<=toX;x++)
                if (board[toY][x]!=0)
                    return 0;
            return side*board[toY][toX]  <= 0;
        }
        else for(int x = fromX - 1; x >=toX ; x--){
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
            for (int y= fromY+1; y<=toY;y++)
                if (board[y][toX]!=0)
                    return 0;
            return side*board[toY][toX] <= 0;
        }
        else {
             for (int y= fromY-1; y>=toY;y--)
                if (board[y][toX]!=0)
                    return 0;
            return side*board[toY][toX] <= 0;
        }
    }
}

int checkKnight(int side, int fromX, int fromY, int toX, int toY ){
    int absDisX = abs(fromX - toX);
    int absDisY = abs(fromY - toY);
    //Chequeo 2 casilleros vertical y 1 horizontal o 2 horizontal y 1 vertical
    if((absDisX == 1 && absDisY == 2) || (absDisX == 2 && absDisY == 1)) {
        return side*board[toY][toX] <= 0;
     }
    return 0;
}

int checkBishop(int side, int fromX, int fromY, int toX, int toY ){
    int absDisX = abs(fromX - toX);
    int absDisY = abs(fromY - toY);
    if(absDisX == 0 || absDisY == 0) { return 0;}
    //Tengo 4 casos, hacia esquina inf izq, inf der, sup izq, sup der
    //Caso 1; hacia sup der
    if(fromX < toX && fromY < toY){
        for(int i  =  fromX + 1; i <= toX; i++){
            if(board[i][i] != 0) { return 0; }
        }
        return side*board[toY][toX] <= 0;
    }
    //Caso 2 : hacia inf izq
    if(fromX > toX && fromY > toY){
        for(int i  =  fromX -1 ; i >= toX; i--){
            if(board[i][i] != 0) { return 0; }
        }
        return side*board[toY][toX] <= 0;
    }
    //Caso3 : hacia sup izq
    if(fromX > toX && fromY < toY){
        for(int i  =  fromX -1 ; i >= toX; i--){
            if(board[i][toY - i] != 0) { return 0; }
        }
        return side*board[toY][toX] <= 0;
    }
    //Caso 4 : hacia inf der
    if(fromX < toX && fromY > toY){
        for(int i  =  fromX + 1 ; i <= toX; i++){
            if(board[i][toY - i] != 0) { return 0; }
        }
        return side*board[toY][toX] <= 0;
    }
}

int checkKing(int side, int fromX, int fromY, int toX, int toY){
    int absDisX = abs(fromX - toX);
    int absDisY = abs(fromY - toY);
    if(absDisX <= 1  && absDisY <=1 && !(absDisX ==0 && absDisX==0)) { return side*board[toY][toX] <= 0;}
    return 0;
}

int checkQueen(int side, int fromX, int fromY, int toX, int toY){
    int absDisX = abs(fromX - toX);
    int absDisY = abs(fromY - toY);
    //El movimiento es recto?
    if(absDisX == 0 || absDisY == 0){
        return checkRook(side,fromX,fromY,toX,toY);
    }
    //Caso contrario es diagonal
    return checkBishop(side,fromX,fromY,toX,toY);
}


