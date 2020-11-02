#include <game.h>
#include <board.h>
#include <timeUtils.h>
#include <mainLib.h>

static int board[8][8];

void movePiece(char fromX,char fromY,char toX,char toY){
    move(board,fromX -'A','8' - fromY, toX - 'A', '8'- toY);
}

void initializeGame(){
    initializeBoard(board);
    printBoard(board);
    hold(3);
    scClear();
    movePiece('A','7','A','5');
    printBoard(board);
}
