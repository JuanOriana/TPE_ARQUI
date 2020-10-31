#define WHITE 1
#define BLACK -1
enum wpieces {WPAWN=1,WBISHOP=2,WKNIGHT=3,WROOK=4,WQUEEN=5,WKING=6};
enum bpieces {BPAWN=-1,BBISHOP=-2,BKNIGHT=-3,BROOK=-4,BQUEEN=-5,BKING=-6};

#define SIZE 8

char board[SIZE][SIZE] ={
    {BROOK,BKNIGHT,BBISHOP,BQUEEN,BKING,BBISHOP,BKNIGHT,BROOK}, //0
    {BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,BPAWN},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {WPAWN,WPAWN,WPAWN,WPAWN,WPAWN,WPAWN,WPAWN,WPAWN,WPAWN},
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

    switch (piece)
    {
        case (WPAWN):
        case (BPAWN):
            int flag = checkPawn(side,fromX,fromY,toX,toY);
            if (flag)
                move(fromX,fromY,toX,toY);
            return flag;
            break;

        case(WROOK):
        case(BROOK):
            return checkRook(side,fromX,fromY,toX,toY);
            break;
        case(WKNIGHT):
        case(BKNIGHT):
            break;
        case(WBISHOP):
        case(BBISHOP):
            break;
        case(WQUEEN):
        case(BQUEEN):
            break;
        case(WKING):
        case(BKING):
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
    int flag = checkBounds(toX,toY);
    if (!flag)
        return flag;
    
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
    int flag = checkBounds(toX,toY);
    if (!flag)
        return flag;

    if (fromX!=toX){
        //si X cambia, y no puede hacerlo
        if (fromY!=toY)
            return 0;
        //No puede haber piezas de fromX+1 a toX-1
        for (int x= fromX+1; x<toX;x++)
            if (board[toY][x]!=0)
                return 0;
        return side*board[toY][toX]  <= 0;
    }
    else
    {
        if (fromX != toX)
            return 0;

        //Idem en Y
        for (int y= fromY+1; y<toY;y++)
            if (board[y][toX]!=0)
                return 0;
        return side*board[toY][toX] <= 0;
    }
}
