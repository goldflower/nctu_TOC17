#ifndef __MOVE_H__
#define __MOVE_H__

int left(int returnBoard[4][4], int board[4][4]);
int right(int returnBoard[4][4], int board[4][4]);
int up(int returnBoard[4][4], int board[4][4]);
int down(int returnBoard[4][4], int board[4][4]);
bool same_board(int board[4][4], int otherBoard[4][4]);
int computeAfterState(int returnBoard[4][4], int board[4][4], int d);
#endif