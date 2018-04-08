#include <iostream>
#include <cstdlib>
#include "Fib2584/GameBoard.h"
#include "Fib2584/MoveDirection.h"
#include "Fib2584/Statistic.h"
#include "Fib2584Ai.h"
#include <map>
#include <cmath>
#include <functional>
#include <vector>
#include <ctime>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>


using namespace std;

map<int, int> fibOrder;

float LearningRate = 0.00001;

const vector<int> fib = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309};

long y = 22*22*22*22;
int x = 4;

// weights結構：所有tuple組合(rows) * 4tuple (columns)
vector<vector<float>> weights(y, vector<float>(x));


Fib2584Ai::Fib2584Ai()
{
}

void setWeights(string filename, vector<vector<float>> &weights)
{
    cout << "Setting weights from file " << filename << "..." << endl;
    ifstream in(filename);
    int rowNumber = 0;
    string s;
    float x,y,z,t;
    while(getline(in >> x >> y >> z >> t, s))
    {
        weights[rowNumber][0] = x;
        weights[rowNumber][1] = y;
        weights[rowNumber][2] = z;
        weights[rowNumber][3] = t;
        rowNumber += 1;
    }
    cout << "Done!!" << endl;
}


void Fib2584Ai::initialize(int argc, char* argv[])
{
    // initialize the map from fibonacci to 0~25
    for (int i = 0; i < 25; i++)
    {
        fibOrder[fib[i]] = i;
    }
    setWeights("weights.txt", weights);
	srand(time(NULL));
	return;
}


float evaluateState(int state[4][4])
{
    float value = 0;
    int key;
    // row的分數
    // row0, row3
    key = 0;
    key += fibOrder[state[0][0]]*pow(22,0);
    key += fibOrder[state[0][1]]*pow(22,1);
    key += fibOrder[state[0][2]]*pow(22,2);
    key += fibOrder[state[0][3]]*pow(22,3);
    value += weights[key][0];
    
    key = 0;
    key += fibOrder[state[3][0]]*pow(22,0);
    key += fibOrder[state[3][1]]*pow(22,1);
    key += fibOrder[state[3][2]]*pow(22,2);
    key += fibOrder[state[3][3]]*pow(22,3);
    value += weights[key][0];
    
    // row1, row2
    key = 0;
    key += fibOrder[state[1][0]]*pow(22,0);
    key += fibOrder[state[1][1]]*pow(22,1);
    key += fibOrder[state[1][2]]*pow(22,2);
    key += fibOrder[state[1][3]]*pow(22,3);
    value += weights[key][1];
    
    key = 0;
    key += fibOrder[state[2][0]]*pow(22,0);
    key += fibOrder[state[2][1]]*pow(22,1);
    key += fibOrder[state[2][2]]*pow(22,2);
    key += fibOrder[state[2][3]]*pow(22,3);
    value += weights[key][1];
    
    
    // 田的分數
    // 四個角落的田
    key = 0;
    key += fibOrder[state[0][0]]*pow(22,0);
    key += fibOrder[state[0][1]]*pow(22,1);
    key += fibOrder[state[1][1]]*pow(22,2);
    key += fibOrder[state[1][0]]*pow(22,3);
    value += weights[key][2];
    
    key = 0;
    key += fibOrder[state[0][2]]*pow(22,0);
    key += fibOrder[state[0][3]]*pow(22,1);
    key += fibOrder[state[1][3]]*pow(22,2);
    key += fibOrder[state[1][2]]*pow(22,3);
    value += weights[key][2];
    
    key = 0;
    key += fibOrder[state[2][0]]*pow(22,0);
    key += fibOrder[state[2][1]]*pow(22,1);
    key += fibOrder[state[3][1]]*pow(22,2);
    key += fibOrder[state[3][0]]*pow(22,3);
    value += weights[key][2];
    
    key = 0;
    key += fibOrder[state[2][2]]*pow(22,0);
    key += fibOrder[state[2][3]]*pow(22,1);
    key += fibOrder[state[3][3]]*pow(22,2);
    key += fibOrder[state[3][2]]*pow(22,3);
    value += weights[key][2];
    
    
    // 十字的田
    key = 0;
    key += fibOrder[state[0][1]]*pow(22,0);
    key += fibOrder[state[0][2]]*pow(22,1);
    key += fibOrder[state[1][2]]*pow(22,2);
    key += fibOrder[state[1][1]]*pow(22,3);
    value += weights[key][3];
    
    key = 0;
    key += fibOrder[state[1][0]]*pow(22,0);
    key += fibOrder[state[1][1]]*pow(22,1);
    key += fibOrder[state[2][1]]*pow(22,2);
    key += fibOrder[state[2][0]]*pow(22,3);
    value += weights[key][3];
    
    key = 0;
    key += fibOrder[state[1][2]]*pow(22,0);
    key += fibOrder[state[1][3]]*pow(22,1);
    key += fibOrder[state[2][3]]*pow(22,2);
    key += fibOrder[state[2][2]]*pow(22,3);
    value += weights[key][3];
    
    key = 0;
    key += fibOrder[state[2][1]]*pow(22,0);
    key += fibOrder[state[2][2]]*pow(22,1);
    key += fibOrder[state[3][2]]*pow(22,2);
    key += fibOrder[state[3][1]]*pow(22,3);
    value += weights[key][3];
    
    return value/12;

}


int left(int returnBoard[4][4], int board[4][4])
{
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        int a = board[i][0];
        int b = board[i][1];
        int c = board[i][2];
        int d = board[i][3];

        // 1. a, b可加為新的fib
        if (a + b > a && a + b > b && std::find(fib.begin(), fib.end(), a+b) != fib.end())
        {
            // c,d可加為新的fib
            if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
            {
                returnBoard[i][0] = a+b;
                returnBoard[i][1] = c+d;
                score +=a+b+c+d;
            }
            else if (c == 0)
            {
                returnBoard[i][0] = a+b;
                returnBoard[i][1] = d;
                score += a+b;
            }
            else if (c != 0)
            {
                returnBoard[i][0] = a+b;
                returnBoard[i][1] = c;
                returnBoard[i][2] = d;
                score += a+b;
            }
        }

        // 2. ab,不可加為新的fib
        else
        {
            // 2.1. bc可加為新的fib
            if (b + c > b && b + c > c && std::find(fib.begin(), fib.end(), b+c) != fib.end())
            {
                if (a == 0)
                {
                    returnBoard[i][0] = b+c;
                    returnBoard[i][1] = d;
                    score += b+c;
                }
                else
                {
                    returnBoard[i][0] = a;
                    returnBoard[i][1] = b+c;
                    returnBoard[i][2] = d;
                    score += b+c;
                }
            }

            // 2.2 bc不可加為新的fib
            // 2.2.1 b為0
            else if (b == 0)
            {
                // ac可加
                if (a + c > a && a + c > c && std::find(fib.begin(), fib.end(), a+c) != fib.end())
                {
                    returnBoard[i][0] = a+c;
                    returnBoard[i][1] = d;
                    score += a+c;
                }
                else
                {
                    if (a == 0)
                    {
                        if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
                        {
                            returnBoard[i][0] = c+d;
                            score += c+d;
                        }
                        else
                        {
                            if (c==0)
                            {
                                returnBoard[i][0] = d;
                            }
                            else
                            {
                                returnBoard[i][0] = c;
                                returnBoard[i][1] = d;
                            }
                        }
                    }
                    else
                    {
                        if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
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
                        
                    }
                }
            }

            // 2.2.2 b不為0
            else
            {
                // cd ok
                if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    if (a == 0)
                    {
                        returnBoard[i][0] = b;
                        returnBoard[i][1] = c+d;
                        score += c+d;
                    }
                    else
                    {
                        returnBoard[i][0] = a;
                        returnBoard[i][1] = b;
                        returnBoard[i][2] = c+d;
                        score += c+d;
                    }
                }
                // cd not ok
                else
                {
                    if (a == 0)
                    {
                        if (c == 0)
                        {
                            returnBoard[i][0] = b;
                            returnBoard[i][1] = d;
                        }
                        else
                        {
                            returnBoard[i][0] = b;
                            returnBoard[i][1] = c;
                            returnBoard[i][2] = d;
                        }
                        
                    }
                    else
                    {
                        if (c == 0)
                        {
                            returnBoard[i][0] = a;
                            returnBoard[i][1] = b;
                            returnBoard[i][2] = d;
                        }
                        else
                        {
                            returnBoard[i][0] = a;
                            returnBoard[i][1] = b;
                            returnBoard[i][2] = c;
                            returnBoard[i][3] = d;
                        }
                        
                    }
                }
            }
        }
    }
    return score;
}
int right(int returnBoard[4][4], int board[4][4])
{

    //cout << "2. condition " << endl;
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        int a = board[i][3];
        int b = board[i][2];
        int c = board[i][1];
        int d = board[i][0];

        // 1. a, b可加為新的fib
        if (a + b > a && a + b > b && std::find(fib.begin(), fib.end(), a+b) != fib.end())
        {

            // c,d可加為新的fib
            if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
            {
                //cout << "r1.1 " << endl;
                returnBoard[i][3] = a+b;
                returnBoard[i][2] = c+d;
                score +=a+b+c+d;
            }
            // cd不可加,c=0
            else if (c == 0)
            {
                //cout << "r1.2 " << endl;
                returnBoard[i][2] = d;
                returnBoard[i][3] = a+b;
                
                score += a+b;
            }
            else if (c != 0)
            {
                //cout << "r1.3 " << endl;
                returnBoard[i][1] = d;
                returnBoard[i][2] = c;
                returnBoard[i][3] = a+b;
                
                
                score += a+b;
            }
        }

        // 2. ab,不可加為新的fib
        else
        {
            // 2.1. bc可加為新的fib
            if (b + c > b && b + c > c && std::find(fib.begin(), fib.end(), b+c) != fib.end())
            {
                if (a == 0)
                {
                  //  cout << "r2.1 " << endl;
                    returnBoard[i][2] = d;
                    returnBoard[i][3] = b+c;
                    
                    score += b+c;
                }
                else
                {
                    //cout << "r2.2 " << endl;
                    returnBoard[i][1] = d;
                    returnBoard[i][2] = b+c;
                    returnBoard[i][3] = a;
                    
                    
                    score += b+c;
                }
            }

            // 2.2 bc不可加為新的fib
            // 2.2.1 b為0
            else if (b == 0)
            {
                // ac可加
                if (a + c > a && a + c > c && std::find(fib.begin(), fib.end(), a+c) != fib.end())
                {
                    //cout << "r2.3 " << endl;
                    returnBoard[i][2] = d;
                    returnBoard[i][3] = a+c;
                    
                    score += a+c;
                }
                else
                {
                    if (a == 0)
                    {
                        if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
                        {
                            //cout << "r2.4 " << endl;
                            returnBoard[i][3] = c+d;
                            score += c+d;
                        }
                        else
                        {
                            if (c==0)
                            {
                      //          cout << "r2.5 " << endl;
                                returnBoard[i][3] = d;
                            }
                            else
                            {
                        //        cout << "r2.6 " << endl;
                                returnBoard[i][3] = c;
                                
                            }
                        }
                    }
                    else
                    {
                        if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
                        {
                          //  cout << "r2.7 " << endl;
                            returnBoard[i][2] = c+d;
                            returnBoard[i][3] = a;
                            
                            score += c+d;
                        }
                        else
                        {
                            //cout << "r2.8 " << endl;
                            returnBoard[i][1] = d;
                            returnBoard[i][2] = c;
                            returnBoard[i][3] = a;
                            
                            
                        }
                        
                    }
                }
            }

            // 2.2.2 b不為0
            else
            {
                // cd ok
                if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    if (a == 0)
                    {
                        //cout << "r2.9 " << endl;
                        returnBoard[i][3] = b;
                        returnBoard[i][2] = c+d;
                        score += c+d;
                    }
                    else
                    {
                        //cout << "r2.10 " << endl;
                        returnBoard[i][3] = a;
                        returnBoard[i][2] = b;
                        returnBoard[i][1] = c+d;
                        score += c+d;
                    }
                }
                // cd not ok
                else
                {
                    if (a == 0)
                    {
                        if (c == 0)
                        {
                            //cout << "r2.11 " << endl;
                            returnBoard[i][3] = b;
                            returnBoard[i][2] = d;
                        }
                        else
                        {
                            //cout << "r2.12 " << endl;
                            returnBoard[i][3] = b;
                            returnBoard[i][2] = c;
                            returnBoard[i][1] = d;
                        }
                        
                    }
                    else
                    {
                        if (c == 0)
                        {
                           // cout << "r2.13 " << endl;
                            returnBoard[i][3] = a;
                            returnBoard[i][2] = b;
                            returnBoard[i][1] = d;
                        }
                        else
                        {
                            //cout << "r2.14 " << endl;
                            returnBoard[i][3] = a;
                            returnBoard[i][2] = b;
                            returnBoard[i][1] = c;
                            returnBoard[i][0] = d;
                        }
                        
                    }
                }

            }
        }
    }
    return score;
}
int up(int returnBoard[4][4], int board[4][4])
{
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        int a = board[0][i];
        int b = board[1][i];
        int c = board[2][i];
        int d = board[3][i];

        // 1. a, b可加為新的fib
        if (a + b > a && a + b > b && std::find(fib.begin(), fib.end(), a+b) != fib.end())
        {
            // c,d可加為新的fib
            if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
            {
                returnBoard[0][i] = a+b;
                returnBoard[1][i] = c+d;
                score += a+b+c+d;
            }
            else if (c == 0)
            {
                returnBoard[0][i] = a+b;
                returnBoard[1][i] = d;
                score += a+b;
            }
            else if (c != 0)
            {
                returnBoard[0][i] = a+b;
                returnBoard[1][i] = c;
                returnBoard[2][i] = d;
                score += a+b;
            }
        }

        // 2. ab,不可加為新的fib
        else
        {
            // 2.1. bc可加為新的fib
            if (b + c > b && b + c > c && std::find(fib.begin(), fib.end(), b+c) != fib.end())
            {
                if (a == 0)
                {
                    returnBoard[0][i] = b+c;
                    returnBoard[1][i] = d;
                    score += b+c;
                }
                else
                {
                    returnBoard[i][0] = a;
                    returnBoard[i][1] = b+c;
                    returnBoard[i][2] = d;
                    score += b+c;
                }
            }

            // 2.2 bc不可加為新的fib
            // 2.2.1 b為0
            else if (b == 0)
            {
                // ac可加
                if (a + c > a && a + c > c && std::find(fib.begin(), fib.end(), a+c) != fib.end())
                {
                    returnBoard[0][i] = a+c;
                    returnBoard[1][i] = d;
                    score += a+c;
                }
                else
                {
                    if (a == 0)
                    {
                        if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
                        {
                            returnBoard[0][i] = c+d;
                            score += c+d;
                        }
                        else
                        {
                            if (c==0)
                            {
                                returnBoard[0][i] = d;
                            }
                            else
                            {
                                returnBoard[0][i] = c;
                                returnBoard[1][i] = d;
                            }
                        }
                    }
                    else
                    {
                        if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
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
                        
                    }
                }
            }

            // 2.2.2 b不為0
            else
            {
                // cd ok
                if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    if (a == 0)
                    {
                        returnBoard[0][i] = b;
                        returnBoard[1][i] = c+d;
                        score += c+d;
                    }
                    else
                    {
                        returnBoard[0][i] = a;
                        returnBoard[1][i] = b;
                        returnBoard[2][i] = c+d;
                        score += c+d;
                    }
                }
                // cd not ok
                else
                {
                    if (a == 0)
                    {
                        returnBoard[0][i] = b;
                        returnBoard[1][i] = c;
                        returnBoard[2][i] = d;
                    }
                    else
                    {
                        returnBoard[0][i] = a;
                        returnBoard[1][i] = b;
                        returnBoard[2][i] = c;
                        returnBoard[3][i] = d;
                    }
                }
            }
        }
    }
    return score;
}
int down(int returnBoard[4][4], int board[4][4])
{
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        int a = board[3][i];
        int b = board[2][i];
        int c = board[1][i];
        int d = board[0][i];

        // 1. a, b可加為新的fib
        if (a + b > a && a + b > b && std::find(fib.begin(), fib.end(), a+b) != fib.end())
        {
            // c,d可加為新的fib
            if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
            {
                returnBoard[3][i] = a+b;
                returnBoard[2][i] = c+d;
                score += a+b+c+d;
            }
            else if (c == 0)
            {
                returnBoard[3][i] = a+b;
                returnBoard[2][i] = d;
                score += a+b;
            }
            else if (c != 0)
            {
                returnBoard[3][i] = a+b;
                returnBoard[2][i] = c;
                returnBoard[1][i] = d;
                score += a+b;
            }
        }

        // 2. ab,不可加為新的fib
        else
        {
            // 2.1. bc可加為新的fib
            if (b + c > b && b + c > c && std::find(fib.begin(), fib.end(), b+c) != fib.end())
            {
                if (a == 0)
                {
                    returnBoard[3][i] = b+c;
                    returnBoard[2][i] = d;
                    score += b+c;
                }
                else
                {
                    returnBoard[3][i] = a;
                    returnBoard[2][i] = b+c;
                    returnBoard[1][i] = d;
                    score += b+c;
                }
            }

            // 2.2 bc不可加為新的fib
            // 2.2.1 b為0
            else if (b == 0)
            {
                // ac可加
                if (a + c > a && a + c > c && std::find(fib.begin(), fib.end(), a+c) != fib.end())
                {
                    returnBoard[3][i] = a+c;
                    returnBoard[2][i] = d;
                    score += a+c;
                }
                else
                {
                    if (a == 0)
                    {
                        if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
                        {
                            returnBoard[3][i] = c+d;
                            score += c+d;
                        }
                        else
                        {
                            if (c==0)
                            {
                                returnBoard[3][i] = d;
                            }
                            else
                            {
                                returnBoard[3][i] = c;
                                returnBoard[2][i] = d;
                            }
                        }
                    }
                    else
                    {
                        if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
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
                        
                    }
                }
            }

            // 2.2.2 b不為0
            else
            {
                // cd ok
                if (c + d > c && c + d > d && std::find(fib.begin(), fib.end(), c+d) != fib.end())
                {
                    if (a == 0)
                    {
                        returnBoard[3][i] = b;
                        returnBoard[2][i] = c+d;
                        score += c+d;
                    }
                    else
                    {
                        returnBoard[3][i] = a;
                        returnBoard[2][i] = b;
                        returnBoard[1][i] = c+d;
                        score += c+d;
                    }
                }
                // cd not ok
                else
                {
                    if (a == 0)
                    {
                        returnBoard[3][i] = b;
                        returnBoard[2][i] = c;
                        returnBoard[1][i] = d;
                    }
                    else
                    {
                        returnBoard[3][i] = a;
                        returnBoard[2][i] = b;
                        returnBoard[1][i] = c;
                        returnBoard[0][i] = d;
                    }
                }
            }
        }
    }
    return score;
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

MoveDirection Fib2584Ai::generateMove(int board[4][4])
{
    MoveDirection a = static_cast<MoveDirection>(rand()%4);
    float max = -INFINITY;
    float afterStateScore;
    int afterState[4][4];
    //int bestState[4][4];
    float value = 0;
    int r;
    for (int i = 0; i < 4; i++)
    {
        // initialize after state to 0
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
                afterState[j][k] = 0;
        }
        r = computeAfterState(afterState, board, i);
        afterStateScore = evaluateState(afterState);
        value = r + afterStateScore;
        //value = afterStateScore;

        

        if (value > max)
        {    

            bool same = true;
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    if (board[j][k] != afterState[j][k])
                    {
                        same = false;
                        break;
                    }
                }

            }

            if (same)
            {
                continue;
            }
            else
            {
                //rbest = r;
                max = value;
                a = static_cast<MoveDirection>(i);
            }
            
        }
            

    }
    
    // cout << "best move: " << a;
    // cout << " reward: " << rbest;
    // cout << " value: " << value << endl;
    
    return a;
}


void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	return;
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
