#include <game.h>
#include <board.h>
#include <timeUtils.h>
#include <mainLib.h>

static int board[8][8] = {0};

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





// readMove(){ //A1 A2
//     char fromX = getChar()// A --> 0
//     char fromY = getCHar()// 1 --> 7
//     getChar();
//     char toX = getChar()// A --> 0
//     char toY = getCHar()// 1 --> 7

//     move(c1 - 'A', '8' - fromY)
// }