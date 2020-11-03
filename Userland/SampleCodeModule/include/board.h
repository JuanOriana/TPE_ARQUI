#ifndef BOARD_H
#define BOARD_H

#define SIZE 8

void initializeBoard(int board[SIZE][SIZE]);
int checkMove(int board[SIZE][SIZE], int fromX, int fromY, int toX, int toY);
int castling(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY);
void printBoard(int board[SIZE][SIZE]);
int checkBounds(int x, int y);

#define WHITE 1
#define BLACK -1
#define EMPTY 0
#define WCOLOR 0xFFFFFF
#define BCOLOR 0x00FF22
#define SIZE 8

enum pieces
{
    PAWN = 1,
    BISHOP = 2,
    KNIGHT = 3,
    ROOK = 4,
    QUEEN = 5,
    KING = 6
};
enum wpieces
{
    WPAWN = 1,
    WBISHOP = 2,
    WKNIGHT = 3,
    WROOK = 4,
    WQUEEN = 5,
    WKING = 6
};
enum bpieces
{
    BPAWN = -1,
    BBISHOP = -2,
    BKNIGHT = -3,
    BROOK = -4,
    BQUEEN = -5,
    BKING = -6
};

#endif