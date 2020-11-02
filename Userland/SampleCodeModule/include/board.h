#ifndef BOARD_H
#define BOARD_H

#define SIZE 8

void initializeBoard(int board[SIZE][SIZE]);
int move(int board[SIZE][SIZE], int fromX, int fromY, int toX, int toY);
int checkMove(int board[SIZE][SIZE],int fromX, int fromY, int toX, int toY);
int checkPawn(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY);
int checkRook(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY );
int checkKnight(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY );
int checkBishop(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY );
int checkKing(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY);
int checkQueen(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY);
int castling(int board[SIZE][SIZE], int side, int fromX, int fromY, int toX, int toY);
void printBoard(int board[8][8]);
int checkBounds(int x, int y);


#endif