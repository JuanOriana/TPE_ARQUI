#include <game.h>
#include <board.h>
#include <timeUtils.h>
#include <mainLib.h>

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
    int fY = fromY - '0';
    int tY = toY - '0';
    if (checkMove(gameBoard, fX, fY, tX, tY))
    {
        gameBoard[toY][toX] = gameBoard[fromY][fromX];
        gameBoard[fromY][fromX] = 0;
        return 1;
    }
    return 0;
}

void initializeGame(){
    initializeBoard(gameBoard);
    printBoard(gameBoard);
    hold(3);
    scClear();
    movePiece('A','7','A','5');
    printBoard(gameBoard);
}
