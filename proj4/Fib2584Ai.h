#ifndef __FIB2584AI_H__
#define __FIB2584AI_H__

#include <cstdlib>
#include <ctime>
#include <string>
#include "Fib2584/Typedefs.h"

using namespace std;
class Fib2584Ai
{
public:
	Fib2584Ai();
	// initialize ai
	void initialize(int argc, char* argv[]);
	// generate one move
	MoveDirection generateMove(int board[4][4]);
	// You need to implement this for project 4
	int generateEvilMove(int board[4][4]);
	// do some action when game over
	void gameOver(int board[4][4], int iScore);
	string getBoardKey(int board[4][4]);
	int generateRandomMove(int board[4][4]);
	int generateRandomTile(int board[4][4]);
	int randomPlay(int board[4][4]);
	int seriousPlay(int board[4][4]);
	/**********************************
	You can implement any additional functions
	or define any variables you may need.
	**********************************/

};

#endif