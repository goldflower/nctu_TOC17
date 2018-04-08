#include "move.h"
//#include <iostream>
#include <vector>
#include <algorithm>
//#include <cmath>
//#include <functional>
#include <string>
//#include <sstream>
using namespace std;

const vector<int> fib = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309};

int left(int returnBoard[4][4], int board[4][4])
{
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        int flag = 0;
        int a = board[i][0];
        if (a > 0)
            flag += 1;
        int b = board[i][1];
        if (b > 0)
            flag += 2;
        int c = board[i][2];
        if (c > 0)
            flag += 4;
        int d = board[i][3];
        if (d > 0)
            flag += 8;

        switch(flag)
        {
            case(0):
                break;
            case(1):
                returnBoard[i][0] = a;
                break;
            case(2):
                returnBoard[i][0] = b;
                break;
            case(3):
                if (std::find(fib.begin(), fib.end(), a+b) != fib.end())
                {
                    returnBoard[i][0] = a+b;
                    score += a+b;
                }
                else
                {
                    returnBoard[i][0] = a;
                    returnBoard[i][1] = b;
                }
                break;
            case(4):
                returnBoard[i][0] = c;
                break;
            case(5):
                if (std::find(fib.begin(), fib.end(), a+c) != fib.end())
                {
                    returnBoard[i][0] = a+c;
                    score += a+c;
                }
                else
                {
                    returnBoard[i][0] = a;
                    returnBoard[i][1] = c;
                }
                break;
            case(6):
                if (std::find(fib.begin(), fib.end(), b+c) != fib.end())
                {
                    returnBoard[i][0] = b+c;
                    score += b+c;
                }
                else
                {
                    returnBoard[i][0] = b;
                    returnBoard[i][1] = c;
                }
                break;
            case(7):
                if (std::find(fib.begin(), fib.end(), a+b) != fib.end())
                {
                    returnBoard[i][0] = a+b;
                    returnBoard[i][1] = c;
                    score += a+b;
                }
                else if (std::find(fib.begin(), fib.end(), b+c) != fib.end())
                {
                    returnBoard[i][0] = a;
                    returnBoard[i][1] = b+c;
                    score += b+c;
                }
                else
                {
                    returnBoard[i][0] = a;
                    returnBoard[i][1] = b;
                    returnBoard[i][2] = c;
                }
                break;
            case(8):
                returnBoard[i][0] = d;
                break;
            case(9):
                if (std::find(fib.begin(), fib.end(), a+d) != fib.end())
                {
                    returnBoard[i][0] = a+d;
                    score += a+d;
                }
                else
                {
                    returnBoard[i][0] = a;
                    returnBoard[i][1] = d;
                }
                break;
            case(10):
                if (std::find(fib.begin(), fib.end(), b+d) != fib.end())
                {
                    returnBoard[i][0] = b+d;
                    score += b+d;
                }
                else
                {
                    returnBoard[i][0] = b;
                    returnBoard[i][1] = d;
                }
                break;
            case(11):
                if (std::find(fib.begin(), fib.end(), a+b) != fib.end())
                {
                    returnBoard[i][0] = a+b;
                    returnBoard[i][1] = d;
                    score += a+b;
                }
                else if (std::find(fib.begin(), fib.end(), b+d) != fib.end())
                {
                    returnBoard[i][0] = a;
                    returnBoard[i][1] = b+d;
                    score += b+d;
                }
                else
                {
                    returnBoard[i][0] = a;
                    returnBoard[i][1] = b;
                    returnBoard[i][2] = d;
                }
                break;
            case(12):
                if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    returnBoard[i][0] = c+d;
                    score += c+d;
                }
                else
                {
                    returnBoard[i][0] = c;
                    returnBoard[i][1] = d;
                }
                break;
            case(13):
                if (std::find(fib.begin(), fib.end(), a+c) != fib.end())
                {
                    returnBoard[i][0] = a+c;
                    returnBoard[i][1] = d;
                    score += a+c;
                }
                else if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    returnBoard[i][0] = a;
                    returnBoard[i][1] = c+d;
                    score += c+d;
                }
                else
                {
                    returnBoard[i][0] = a;
                    returnBoard[i][1] = c;
                    returnBoard[i][2] = d;
                }
                break;
            case(14):
                if (std::find(fib.begin(), fib.end(), b+c) != fib.end())
                {
                    returnBoard[i][0] = b+c;
                    returnBoard[i][1] = d;
                    score += b+c;
                }
                else if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    returnBoard[i][0] = b;
                    returnBoard[i][1] = c+d;
                    score += c+d;
                }
                else
                {
                    returnBoard[i][0] = b;
                    returnBoard[i][1] = c;
                    returnBoard[i][2] = d;
                }
                break;
            case(15):
                if (std::find(fib.begin(), fib.end(), a+b) != fib.end())
                {
                    returnBoard[i][0] = a+b;
                    score += a+b;
                    if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                    {
                        returnBoard[i][1] = c+d;
                        score += c+d;
                    }
                    else
                    {
                        returnBoard[i][1] = c;
                        returnBoard[i][2] = d;
                    }
                }
                else if (std::find(fib.begin(), fib.end(), b+c) != fib.end())
                {
                    returnBoard[i][0] = a;
                    returnBoard[i][1] = b+c;
                    returnBoard[i][2] = d;
                    score += b+c;
                }
                else if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    returnBoard[i][0] = a;
                    returnBoard[i][1] = b;
                    returnBoard[i][2] = c+d;
                    score += c+d;
                }
                else
                {
                    returnBoard[i][0] = a;
                    returnBoard[i][1] = b;
                    returnBoard[i][2] = c;
                    returnBoard[i][3] = d;
                }
                break;
        }       
    }
    return score;
}


int right(int returnBoard[4][4], int board[4][4])
{
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        int flag = 0;
        int a = board[i][3];
        if (a > 0)
            flag += 1;
        int b = board[i][2];
        if (b > 0)
            flag += 2;
        int c = board[i][1];
        if (c > 0)
            flag += 4;
        int d = board[i][0];
        if (d > 0)
            flag += 8;

        switch(flag)
        {
            case(0):
                break;
            case(1):
                returnBoard[i][3] = a;
                break;
            case(2):
                returnBoard[i][3] = b;
                break;
            case(3):
                if (std::find(fib.begin(), fib.end(), a+b) != fib.end())
                {
                    returnBoard[i][3] = a+b;
                    score += a+b;
                }
                else
                {
                    returnBoard[i][3] = a;
                    returnBoard[i][2] = b;
                }
                break;
            case(4):
                returnBoard[i][3] = c;
                break;
            case(5):
                if (std::find(fib.begin(), fib.end(), a+c) != fib.end())
                {
                    returnBoard[i][3] = a+c;
                    score += a+c;
                }
                else
                {
                    returnBoard[i][3] = a;
                    returnBoard[i][2] = c;
                }
                break;
            case(6):
                if (std::find(fib.begin(), fib.end(), b+c) != fib.end())
                {
                    returnBoard[i][3] = b+c;
                    score += b+c;
                }
                else
                {
                    returnBoard[i][3] = b;
                    returnBoard[i][2] = c;
                }
                break;
            case(7):
                if (std::find(fib.begin(), fib.end(), a+b) != fib.end())
                {
                    returnBoard[i][3] = a+b;
                    returnBoard[i][2] = c;
                    score += a+b;
                }
                else if (std::find(fib.begin(), fib.end(), b+c) != fib.end())
                {
                    returnBoard[i][3] = a;
                    returnBoard[i][2] = b+c;
                    score += b+c;
                }
                else
                {
                    returnBoard[i][3] = a;
                    returnBoard[i][2] = b;
                    returnBoard[i][1] = c;
                }
                break;
            case(8):
                returnBoard[i][3] = d;
                break;
            case(9):
                if (std::find(fib.begin(), fib.end(), a+d) != fib.end())
                {
                    returnBoard[i][3] = a+d;
                    score += a+d;
                }
                else
                {
                    returnBoard[i][3] = a;
                    returnBoard[i][2] = d;
                }
                break;
            case(10):
                if (std::find(fib.begin(), fib.end(), b+d) != fib.end())
                {
                    returnBoard[i][3] = b+d;
                    score += b+d;
                }
                else
                {
                    returnBoard[i][3] = b;
                    returnBoard[i][2] = d;
                }
                break;
            case(11):
                if (std::find(fib.begin(), fib.end(), a+b) != fib.end())
                {
                    returnBoard[i][3] = a+b;
                    returnBoard[i][2] = d;
                    score += a+b;
                }
                else if (std::find(fib.begin(), fib.end(), b+d) != fib.end())
                {
                    returnBoard[i][3] = a;
                    returnBoard[i][2] = b+d;
                    score += b+d;
                }
                else
                {
                    returnBoard[i][3] = a;
                    returnBoard[i][2] = b;
                    returnBoard[i][1] = d;
                }
                break;
            case(12):
                if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    returnBoard[i][3] = c+d;
                    score += c+d;
                }
                else
                {
                    returnBoard[i][3] = c;
                    returnBoard[i][2] = d;
                }
                break;
            case(13):
                if (std::find(fib.begin(), fib.end(), a+c) != fib.end())
                {
                    returnBoard[i][3] = a+c;
                    returnBoard[i][2] = d;
                    score += a+c;
                }
                else if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    returnBoard[i][3] = a;
                    returnBoard[i][2] = c+d;
                    score += c+d;
                }
                else
                {
                    returnBoard[i][3] = a;
                    returnBoard[i][2] = c;
                    returnBoard[i][1] = d;
                }
                break;
            case(14):
                if (std::find(fib.begin(), fib.end(), b+c) != fib.end())
                {
                    returnBoard[i][3] = b+c;
                    returnBoard[i][2] = d;
                    score += b+c;
                }
                else if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    returnBoard[i][3] = b;
                    returnBoard[i][2] = c+d;
                    score += c+d;
                }
                else
                {
                    returnBoard[i][3] = b;
                    returnBoard[i][2] = c;
                    returnBoard[i][1] = d;
                }
                break;
            case(15):
                if (std::find(fib.begin(), fib.end(), a+b) != fib.end())
                {
                    returnBoard[i][3] = a+b;
                    score += a+b;
                    if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                    {
                        returnBoard[i][2] = c+d;
                        score += c+d;
                    }
                    else
                    {
                        returnBoard[i][2] = c;
                        returnBoard[i][1] = d;
                    }
                }
                else if (std::find(fib.begin(), fib.end(), b+c) != fib.end())
                {
                    returnBoard[i][3] = a;
                    returnBoard[i][2] = b+c;
                    returnBoard[i][1] = d;
                    score += b+c;
                }
                else if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    returnBoard[i][3] = a;
                    returnBoard[i][2] = b;
                    returnBoard[i][1] = c+d;
                    score += c+d;
                }
                else
                {
                    returnBoard[i][3] = a;
                    returnBoard[i][2] = b;
                    returnBoard[i][1] = c;
                    returnBoard[i][0] = d;
                }
                break;
        }       
    }
    return score;
}
int up(int returnBoard[4][4], int board[4][4])
{
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        int flag = 0;
        int a = board[0][i];
        if (a > 0)
            flag += 1;
        int b = board[1][i];
        if (b > 0)
            flag += 2;
        int c = board[2][i];
        if (c > 0)
            flag += 4;
        int d = board[3][i];
        if (d > 0)
            flag += 8;

        switch(flag)
        {
            case(0):
                break;
            case(1):
                returnBoard[0][i] = a;
                break;
            case(2):
                returnBoard[0][i] = b;
                break;
            case(3):
                if (std::find(fib.begin(), fib.end(), a+b) != fib.end())
                {
                    returnBoard[0][i] = a+b;
                    score += a+b;
                }
                else
                {
                    returnBoard[0][i] = a;
                    returnBoard[1][i] = b;
                }
                break;
            case(4):
                returnBoard[0][i] = c;
                break;
            case(5):
                if (std::find(fib.begin(), fib.end(), a+c) != fib.end())
                {
                    returnBoard[0][i] = a+c;
                    score += a+c;
                }
                else
                {
                    returnBoard[0][i] = a;
                    returnBoard[0][i] = c;
                }
                break;
            case(6):
                if (std::find(fib.begin(), fib.end(), b+c) != fib.end())
                {
                    returnBoard[0][i] = b+c;
                    score += b+c;
                }
                else
                {
                    returnBoard[0][i] = b;
                    returnBoard[1][i] = c;
                }
                break;
            case(7):
                if (std::find(fib.begin(), fib.end(), a+b) != fib.end())
                {
                    returnBoard[0][i] = a+b;
                    returnBoard[1][i] = c;
                    score += a+b;
                }
                else if (std::find(fib.begin(), fib.end(), b+c) != fib.end())
                {
                    returnBoard[0][i] = a;
                    returnBoard[1][i] = b+c;
                    score += b+c;
                }
                else
                {
                    returnBoard[0][i] = a;
                    returnBoard[1][i] = b;
                    returnBoard[2][i] = c;
                }
                break;
            case(8):
                returnBoard[0][i] = d;
                break;
            case(9):
                if (std::find(fib.begin(), fib.end(), a+d) != fib.end())
                {
                    returnBoard[0][i] = a+d;
                    score += a+d;
                }
                else
                {
                    returnBoard[0][i] = a;
                    returnBoard[1][i] = d;
                }
                break;
            case(10):
                if (std::find(fib.begin(), fib.end(), b+d) != fib.end())
                {
                    returnBoard[0][i] = b+d;
                    score += b+d;
                }
                else
                {
                    returnBoard[0][i] = b;
                    returnBoard[1][i] = d;
                }
                break;
            case(11):
                if (std::find(fib.begin(), fib.end(), a+b) != fib.end())
                {
                    returnBoard[0][i] = a+b;
                    returnBoard[1][i] = d;
                    score += a+b;
                }
                else if (std::find(fib.begin(), fib.end(), b+d) != fib.end())
                {
                    returnBoard[0][i] = a;
                    returnBoard[1][i] = b+d;
                    score += b+d;
                }
                else
                {
                    returnBoard[0][i] = a;
                    returnBoard[1][i] = b;
                    returnBoard[2][i] = d;
                }
                break;
            case(12):
                if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    returnBoard[0][i] = c+d;
                    score += c+d;
                }
                else
                {
                    returnBoard[0][i] = c;
                    returnBoard[1][i] = d;
                }
                break;
            case(13):
                if (std::find(fib.begin(), fib.end(), a+c) != fib.end())
                {
                    returnBoard[0][i] = a+c;
                    returnBoard[1][i] = d;
                    score += a+c;
                }
                else if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    returnBoard[0][i] = a;
                    returnBoard[1][i] = c+d;
                    score += c+d;
                }
                else
                {
                    returnBoard[0][i] = a;
                    returnBoard[1][i] = c;
                    returnBoard[2][i] = d;
                }
                break;
            case(14):
                if (std::find(fib.begin(), fib.end(), b+c) != fib.end())
                {
                    returnBoard[0][i] = b+c;
                    returnBoard[1][i] = d;
                    score += b+c;
                }
                else if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    returnBoard[0][i] = b;
                    returnBoard[1][i] = c+d;
                    score += c+d;
                }
                else
                {
                    returnBoard[0][i] = b;
                    returnBoard[1][i] = c;
                    returnBoard[2][i] = d;
                }
                break;
            case(15):
                if (std::find(fib.begin(), fib.end(), a+b) != fib.end())
                {
                    returnBoard[0][i] = a+b;
                    score += a+b;
                    if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                    {
                        returnBoard[1][i] = c+d;
                        score += c+d;
                    }
                    else
                    {
                        returnBoard[1][i] = c;
                        returnBoard[2][i] = d;
                    }
                }
                else if (std::find(fib.begin(), fib.end(), b+c) != fib.end())
                {
                    returnBoard[0][i] = a;
                    returnBoard[1][i] = b+c;
                    returnBoard[2][i] = d;
                    score += b+c;
                }
                else if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    returnBoard[0][i] = a;
                    returnBoard[1][i] = b;
                    returnBoard[2][i] = c+d;
                    score += c+d;
                }
                else
                {
                    returnBoard[0][i] = a;
                    returnBoard[1][i] = b;
                    returnBoard[2][i] = c;
                    returnBoard[3][i] = d;
                }
                break;
        }       
    }
    return score;
}

int down(int returnBoard[4][4], int board[4][4])
{
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        int flag = 0;
        int a = board[3][i];
        if (a > 0)
            flag += 1;
        int b = board[2][i];
        if (b > 0)
            flag += 2;
        int c = board[1][i];
        if (c > 0)
            flag += 4;
        int d = board[0][i];
        if (d > 0)
            flag += 8;

        switch(flag)
        {
            case(0):
                break;
            case(1):
                returnBoard[3][i] = a;
                break;
            case(2):
                returnBoard[3][i] = b;
                break;
            case(3):
                if (std::find(fib.begin(), fib.end(), a+b) != fib.end())
                {
                    returnBoard[3][i] = a+b;
                    score += a+b;
                }
                else
                {
                    returnBoard[3][i] = a;
                    returnBoard[2][i] = b;
                }
                break;
            case(4):
                returnBoard[3][i] = c;
                break;
            case(5):
                if (std::find(fib.begin(), fib.end(), a+c) != fib.end())
                {
                    returnBoard[3][i] = a+c;
                    score += a+c;
                }
                else
                {
                    returnBoard[3][i] = a;
                    returnBoard[3][i] = c;
                }
                break;
            case(6):
                if (std::find(fib.begin(), fib.end(), b+c) != fib.end())
                {
                    returnBoard[3][i] = b+c;
                    score += b+c;
                }
                else
                {
                    returnBoard[3][i] = b;
                    returnBoard[2][i] = c;
                }
                break;
            case(7):
                if (std::find(fib.begin(), fib.end(), a+b) != fib.end())
                {
                    returnBoard[3][i] = a+b;
                    returnBoard[2][i] = c;
                    score += a+b;
                }
                else if (std::find(fib.begin(), fib.end(), b+c) != fib.end())
                {
                    returnBoard[3][i] = a;
                    returnBoard[2][i] = b+c;
                    score += b+c;
                }
                else
                {
                    returnBoard[3][i] = a;
                    returnBoard[2][i] = b;
                    returnBoard[1][i] = c;
                }
                break;
            case(8):
                returnBoard[3][i] = d;
                break;
            case(9):
                if (std::find(fib.begin(), fib.end(), a+d) != fib.end())
                {
                    returnBoard[3][i] = a+d;
                    score += a+d;
                }
                else
                {
                    returnBoard[3][i] = a;
                    returnBoard[2][i] = d;
                }
                break;
            case(10):
                if (std::find(fib.begin(), fib.end(), b+d) != fib.end())
                {
                    returnBoard[3][i] = b+d;
                    score += b+d;
                }
                else
                {
                    returnBoard[3][i] = b;
                    returnBoard[2][i] = d;
                }
                break;
            case(11):
                if (std::find(fib.begin(), fib.end(), a+b) != fib.end())
                {
                    returnBoard[3][i] = a+b;
                    returnBoard[2][i] = d;
                    score += a+b;
                }
                else if (std::find(fib.begin(), fib.end(), b+d) != fib.end())
                {
                    returnBoard[3][i] = a;
                    returnBoard[2][i] = b+d;
                    score += b+d;
                }
                else
                {
                    returnBoard[3][i] = a;
                    returnBoard[2][i] = b;
                    returnBoard[1][i] = d;
                }
                break;
            case(12):
                if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    returnBoard[3][i] = c+d;
                    score += c+d;
                }
                else
                {
                    returnBoard[3][i] = c;
                    returnBoard[2][i] = d;
                }
                break;
            case(13):
                if (std::find(fib.begin(), fib.end(), a+c) != fib.end())
                {
                    returnBoard[3][i] = a+c;
                    returnBoard[2][i] = d;
                    score += a+c;
                }
                else if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    returnBoard[3][i] = a;
                    returnBoard[2][i] = c+d;
                    score += c+d;
                }
                else
                {
                    returnBoard[3][i] = a;
                    returnBoard[2][i] = c;
                    returnBoard[1][i] = d;
                }
                break;
            case(14):
                if (std::find(fib.begin(), fib.end(), b+c) != fib.end())
                {
                    returnBoard[3][i] = b+c;
                    returnBoard[2][i] = d;
                    score += b+c;
                }
                else if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    returnBoard[3][i] = b;
                    returnBoard[2][i] = c+d;
                    score += c+d;
                }
                else
                {
                    returnBoard[3][i] = b;
                    returnBoard[2][i] = c;
                    returnBoard[1][i] = d;
                }
                break;
            case(15):
                if (std::find(fib.begin(), fib.end(), a+b) != fib.end())
                {
                    returnBoard[3][i] = a+b;
                    score += a+b;
                    if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                    {
                        returnBoard[2][i] = c+d;
                        score += c+d;
                    }
                    else
                    {
                        returnBoard[2][i] = c;
                        returnBoard[1][i] = d;
                    }
                }
                else if (std::find(fib.begin(), fib.end(), b+c) != fib.end())
                {
                    returnBoard[3][i] = a;
                    returnBoard[2][i] = b+c;
                    returnBoard[1][i] = d;
                    score += b+c;
                }
                else if (std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    returnBoard[3][i] = a;
                    returnBoard[2][i] = b;
                    returnBoard[1][i] = c+d;
                    score += c+d;
                }
                else
                {
                    returnBoard[3][i] = a;
                    returnBoard[2][i] = b;
                    returnBoard[1][i] = c;
                    returnBoard[0][i] = d;
                }
                break;
        }       
    }
    return score;
}

bool same_board(int board[4][4], int otherBoard[4][4])
{
    for (int i = 0; i < 16; i++)
    {
        if (board[i] != otherBoard[i])
            return false;
    }
    return true;
}

int computeAfterState(int returnBoard[4][4], int board[4][4], int d)
{
    int score = 0;
    // left
    if (d == 3)
        score = left(returnBoard, board);
    else if (d == 1)
        score = right(returnBoard, board);
    else if (d == 0)
        score = up(returnBoard, board);
    else if (d == 2)
        score = down(returnBoard, board);
    return score;
}