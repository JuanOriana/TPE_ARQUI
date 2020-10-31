
enum wpieces {WPAWN=1,WBISHOP,WKNIGHT,WROOK,WQUEEN,WKING};
enum bpieces {BPAWN=11,BBISHOP,BKNIGHT,BROOK,BQUEEN,BKING};


char board[8][8] ={
    {BROOK,BKNIGHT,BBISHOP,BQUEEN,BKING,BBISHOP,BKNIGHT,BROOK},
    {BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,BPAWN,BPAWN},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {WPAWN,WPAWN,WPAWN,WPAWN,WPAWN,WPAWN,WPAWN,WPAWN,WPAWN},
    {WROOK,WKNIGHT,WBISHOP,WQUEEN,WKING,WBISHOP,WKNIGHT,WROOK}
};


int move(int piece, int from_x, int from_y, int to_x, int to_y){
    board[from_x][from_x] = 0;
    board[to_x][to_y] = piece;
}

int checkMove(int piece, int from_x, int from_y, int to_x, int to_y){
    switch (piece%10)
    {
    case 1:
    {
        if(1) { return -1;}

        else if(to_x == 2 + from_x){
            if(from_x == 1 && from_y==to_y && board[to_x][to_y]==0) {
                move(piece,from_x,from_y,to_x,to_y);
            }
            else return -1;
        }
        else {
            if (to_y == from_y && board[to_x][to_y]==0) {move(piece,from_x,fr_y,)}
        }
        
    }