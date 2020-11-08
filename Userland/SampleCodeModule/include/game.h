#ifndef GAME_H
#define GAME_H

void initializeGame();
void chess();
void printLog();
void manualRotLeft();
void manualRotRight();
void castling(int fX, int fY, int tX, int tY);
void rotate(int rot);
#endif