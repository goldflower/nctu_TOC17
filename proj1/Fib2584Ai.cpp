#include "Fib2584Ai.h"
#include "Fib2584/GameBoard.h"
#include "Fib2584/MoveDirection.h"
#include "Fib2584/Statistic.h"
#include <algorithm>
#include <functional>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>


const vector<int> fib = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309};

Fib2584Ai::Fib2584Ai()
{
}

void Fib2584Ai::initialize(int argc, char* argv[])
{

	srand(time(NULL));
	return;
}

float getRowScore(int a, int b, int c, int d)
{
    //cout << "getRowScore" << endl;
    //cout << a << "," << b <<"," << c <<","<< d << endl;
    float score = 0;
    float s = 0;
    if (a + b > a && a + b > b && std::find(fib.begin(), fib.end(), a+b) != fib.end())
    {
        s = a + b;
        score += s;
        if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
        {
            s = c+d;
            score += s;
        }
    }

    else if (b + c > b && b + c > c && std::find(fib.begin(), fib.end(), b+c) != fib.end())
    {
        s = b+c;
        if (d>b && b>c && b>a)
        {
            score += s/1.2;
        }
        else
        {
            score += s;
        }
        
    }

    else if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
    {
        s = c+d;
        if (d>c && d>b && d>a)
        {
            score += s/1.2;
        }
        else
        {
            score += s;
        }
        
    }

    else if (b == 0 && a + c > a && a + c > c && std::find(fib.begin(), fib.end(), a+c) != fib.end())
    {
        s = a+c;
        score += s;
    }

    else if (b==0 && c==0 && a + d > a && a + d > d && std::find(fib.begin(), fib.end(), a+d) != fib.end())
    {
        s = a+d;
        score += s/1.3;

    }

    else if (c==0 && b+d > b && b+d>d  && std::find(fib.begin(), fib.end(), b+d) != fib.end())
    {
        s = b+d;
        score += s/1.1;

    }
    //cout << "return score " << score << endl;
    //cout << score << endl;
    return score;
}

float moveScore(int board[4][4], int d)
{

    float score = 0;
    if (d == 3)
    {
        for (int i = 0; i < 4; i++)
        {
            int a = board[i][0], b = board[i][1], c = board[i][2], d = board[i][3];
            score += getRowScore(a,b,c,d)/11-10;
        }
    }
    else if (d == 0)
    {
        for (int i = 0; i < 4; i++)
        {
            int a = board[0][i], b=board[1][i], c=board[2][i], d=board[3][i];
            score += getRowScore(a,b,c,d);
        }
    }
    else if (d == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            int d = board[i][0], c = board[i][1], b = board[i][2], a = board[i][3];
            score += getRowScore(a,b,c,d);
        }
    }
    else if (d == 2)
    {
        for (int i = 0; i < 4; i++)
        {
            int d = board[0][i], c=board[1][i], b=board[2][i], a=board[3][i];
            score += getRowScore(a,b,c,d);
        }
    }
    //cout << "moveScore return " << score << endl;
    return score;
}


MoveDirection Fib2584Ai::generateMove(int board[4][4])
{
    MoveDirection returnMove;
    //bool flag = canMove(board);
    /*
    int random = rand()%10000;
    if (random > 500)
    {
        returnMove = static_cast<MoveDirection>(rand()%2);
    }
    else if (random > 5)
    {
        returnMove = static_cast<MoveDirection>(rand()%2+1);
    }
    else
    {
        returnMove = static_cast<MoveDirection>(3);
    }
    return returnMove;
    */

    /*
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << board[i][j] << "  ";
        }
        cout << endl;
    }
    */
    
    // Greedy strategy
    float max = 0;
    int move = 0;
    for (int i = 0; i < 4; i++)
    {
        //cout << "try move to " << i << endl;
        if (moveScore(board, i) > max)
        {
            max = moveScore(board, i);
            returnMove = static_cast<MoveDirection>(i);
        }
    }
    /*
    if (max == 0)
    {
        cout << "random move" << endl;
        int d = rand()%4;
        returnMove = static_cast<MoveDirection>(d);
        move = d;
    }
    */


    if (max <= 0)
    {
        int random = rand()%20000;
        if (random > 10000)
        {
            returnMove = static_cast<MoveDirection>(rand()%2);
        }
        else if (random > 0)
        {
            returnMove = static_cast<MoveDirection>(2);
        }
        
        else
        {
            returnMove = static_cast<MoveDirection>(3);
        }
    }

    //cout << "Move to " << move << " moveScore: " << max << endl;
    //cout << "decide move to " << move << endl;
    return returnMove;
}


void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	return;
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
