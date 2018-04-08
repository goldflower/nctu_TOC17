#include "Fib2584Ai.h"
#include "move.h"
#include "MCT.h"
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
//#include "TD.cpp"


using namespace std;
static int generateNumber = 0;
map<int, int> fibOrder;

long y = 22*22*22*22;
int x = 4;
const vector<int> fib = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309};
static vector<vector<float>> weights(y, vector<float>(x));

//const vector<int> fib = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309};
float MCT::c = 20;
int MCT::totalCount = 0;


void setWeights(string filename, vector<vector<float>> &weights)
{
    cout << "Setting weights from file " << filename << "..." << endl;
    ifstream in(filename);
    int rowNumber = 0;
    string str;
    //float x,y,z,t,s;
    //float x,y,z,t;
    float a,b,c,d;
    while(getline(in >> a >> b >> c >> d, str))
    {
        weights[rowNumber][0] = a;
        weights[rowNumber][1] = b;
        weights[rowNumber][2] = c;
        weights[rowNumber][3] = d;
        //weights[rowNumber][4] = s;
        rowNumber += 1;
    }
    cout << "Done!!" << endl;
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

    // 中間的田
    // key = 0;
    // key += fibOrder[state[1][1]]*pow(22,0);
    // key += fibOrder[state[1][2]]*pow(22,1);
    // key += fibOrder[state[2][2]]*pow(22,2);
    // key += fibOrder[state[2][1]]*pow(22,3);
    // value += weights[key][4];
    
    return value;
}


// weights結構：所有tuple組合(rows) * 4tuple (columns)
//static vector<vector<float>> weights(y, vector<float>(x));
bool movable(int current_board[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        int afterState[4][4] = {0};
        switch(i)
        {
            case 0:
                up(afterState, current_board);
                break;
            case 1:
                right(afterState, current_board);
                break;
            case 2:
                down(afterState, current_board);
                break;
            case 3:
                left(afterState, current_board);
                break;
        }
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                if (afterState[j][k] != current_board[j][k])
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int move(int afterState[4][4], int current_board[4][4], int direction)
{
    int r = -1;
    switch(direction)
    {
        case 0:
            r = up(afterState, current_board);
            break;
        case 1:
            r = right(afterState, current_board);
            break;
        case 2:
            r = down(afterState, current_board);
            break;
        case 3:
            r = left(afterState, current_board);
            break;
    }
    return r;
}



Fib2584Ai::Fib2584Ai()
{
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	srand(time(NULL));
    for (int i = 0; i < 25; i++)
    {
        fibOrder[fib[i]] = i;
    }
    setWeights("weights.txt", weights);
	return;
}


int generateIntMove(int board[4][4])
{
    int a = 0;
    float max = -INFINITY;
    float afterStateScore;
    int afterState[4][4];
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
                max = value;
                a = i;
            }   
        }
    }
    
    return a;
}
MoveDirection Fib2584Ai::generateMove( int board[4][4] )
{

    MoveDirection a = static_cast<MoveDirection>(3);
    float max = -INFINITY;
    float afterStateScore;
    int afterState[4][4];
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
                max = value;
                a = static_cast<MoveDirection>(i);
            }   
        }
    }
    
    return a;
}

int Fib2584Ai::generateRandomMove( int board[4][4] )
{
    int afterState[4][4] = {0};
    while(true)
    {   
        for (int i = 0; i < 4; i++)
        {
            // initialize after state to 0
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                    afterState[j][k] = 0;
            }
        }
        int r = rand()%4;
        computeAfterState(afterState, board, r);
        if (!same_board(afterState, board))
        {
            return r;
        }
    }
}

int Fib2584Ai::generateRandomTile(int board[4][4])
{
    while(true)
    {
        int r = rand()%16;
        if (board[r/4][r%4] == 0)
        {
            return r;
        }
    }
}

void showBoard(int board[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool sameBoard(int board[4][4], int otherboard[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if (board[i][j] != otherboard[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

int Fib2584Ai::seriousPlay(int board[4][4])
{
    int current_board[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            current_board[i][j] = board[i][j];
        }
    }
    //cout << "1" << endl;
    int afterState[4][4];
    int total_score = 0;
    int move_score = 0;
    int next_tile = generateNumber;
    while(true)
    {
        //showBoard(current_board);
        if (!movable(current_board))
        {
            //cout << "cant move" << endl;
            break;
        }
        //cout << "set after state" << endl;
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                afterState[i][j] = 0;
            }
        }
        //cout << "move" << endl;
        move_score = move(afterState, current_board, generateIntMove(current_board));
        //cout << "get score" << endl;
        //cout << "2" << endl;
        //cout << endl;

        // 不相同,則把分數加上去後加入新的tile
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                current_board[i][j] = afterState[i][j];
            }
        }
        total_score += move_score;
        int position = generateRandomTile(current_board);
        if (next_tile == 3)
        {
            current_board[position/4][position%4] = 3;
        }
        else
        {
            current_board[position/4][position%4] = 1;
        }
        next_tile = (next_tile + 1) % 4;
    }

    return total_score;
}

// 隨機玩一場並return最後分數
int Fib2584Ai::randomPlay(int board[4][4])
{
    int move;
    int current_board[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            current_board[i][j] = board[i][j];
        }
    }
    int afterState[4][4];
    int total_score = 0;
    int move_score;
    int moved[4] = {0};
    int next_tile = generateNumber;
    bool terminated = false;
    while(!terminated)
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                afterState[i][j] = 0;
            }
        }
        move = rand()%4;
        switch(move)
        {
            case 0:
                move_score = up(afterState, current_board);
                moved[0] = 1;
                break;
            case 1:
                move_score = right(afterState, current_board);
                moved[1] = 1;
                break;
            case 2:
                move_score = down(afterState, current_board);
                moved[2] = 1;
                break;
            case 3:
                move_score = left(afterState, current_board);
                moved[3] = 1;
                break;
        }
        bool same = true;
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                if (current_board[j][k] != afterState[j][k])
                {
                    same = false;
                    break;
                }
            }
        }
        // 檢查盤面是否相同,相同有兩種可能
        // 1.還有沒試過的其他步
        // 2.四步都走過了,表示terminate
        if (same)
        {
            terminated = true;
            for(int i = 0; i < 4; i++)
            {
                if(moved[i] == 0)
                {
                    terminated = false;
                    break;
                }
            }
            continue;
        }
        // 不相同,則把分數加上去後加入新的tile
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                current_board[i][j] = afterState[i][j];
            }
        }
        total_score += move_score;
        int position = generateRandomTile(current_board);
        if (next_tile == 3)
        {
            current_board[position/4][position%4] = 3;
        }
        else
        {
            current_board[position/4][position%4] = 1;
        }
        //showBoard(current_board);
        next_tile = (next_tile + 1) % 4;
        for (int i = 0; i < 4; i++)
            moved[i] = 0;

    }

    return total_score;
}

string Fib2584Ai::getBoardKey(int board[4][4])
{
    string key = ""; // 盤面的編號
    int count = 0;
    int empty[16] = {0};
    // 1.記錄可以下的位置
    // 2.計算目前的key
    for (int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
            {
                empty[count] = 4*i+j;
                count += 1;
            }
            if (4*i+j == 15)
                key += to_string(board[i][j]);
            else
                key += to_string(board[i][j]) + " ";
        }
    }
    return key;
}

int Fib2584Ai::generateEvilMove(int board[4][4])
{   
    // 每個node的分數:
    // Q_MCTS: sum(score_i)/current_games + const*sqrt(log(total_games)/current_games)
    // current state: board[4][4]
    MCT *root = new MCT(0, -1);
    int score;
    //cout << "init" << endl;
    for (int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
            {
                if (generateNumber == 3)
                {
                    board[i][j] = 3;
                }
                else
                {
                    board[i][j] = 1;
                }
                //score = randomPlay(board);
                score = randomPlay(board);
                MCT::totalCount++;
                board[i][j] = 0;
                MCT *node = new MCT(score, 4*i+j);
                MCT::update(node, score, 0);
                root->childs.push_back(node);
            }
        }
    }
    //cout << "init done" << endl;
    // 第一種iteration設定
    //int iterations = ((root->childs.size()%8)+1)*900;
    // 第二種iteration設定
    int iterations;
    if (root->childs.size() == 1)
    {
        iterations = 1;
    }
    if (root->childs.size() < 5)
    {
        iterations = 10000;
    }
    else if(root->childs.size() < 9)
    {
        iterations = root->childs.size()*2000;
        //iterations = 8000;
    }
    else if(root->childs.size() < 14)
    {
        iterations = 8000;
    }
    else
    {
        iterations = (17-root->childs.size())*1000;
        //iterations = root->childs.size()*1000;
    }
    // 找Q最大的
    float max = -INFINITY;
    MCT *playThis;
    for(int i = 0; i < iterations; i++)
    {
        //cout << "round " << i << endl;
        playThis = MCT::findMaxQ(root->childs);
        //cout << "play " << playThis->position << endl;
        // update
        if (generateNumber == 3)
        {
            board[(playThis->position)/4][(playThis->position)%4] = 3;
        }
        else
        {
            board[(playThis->position)/4][(playThis->position)%4] = 1;
        }
        int score = randomPlay(board);
        //int score = seriousPlay(board);
        //cout << score << endl;
        board[(playThis->position)/4][(playThis->position)%4] = 0;
        MCT::totalCount++;
        for(int j = 0; j < root->childs.size(); j++)
        {
            if(root->childs.at(j)->position == playThis->position)
            {
                MCT::update(root->childs.at(j), score, 1);
            }
            else
            {
                MCT::update(root->childs.at(j), 0, 0);
            }
        }
    }

    max = -INFINITY;
    int returnPos = 0;
    for(int j = 0; j < root->childs.size(); j++)
    {   
        //cout << root->childs.at(j)->position << ":" << root->childs.at(j)->Q << "| ";
        if (root->childs.at(j)->selfCount > max)
        {
            returnPos = root->childs.at(j)->position;
            max = root->childs.at(j)->selfCount;
        }
    }

    generateNumber = (generateNumber+1)%4;
    return returnPos;
    //return 玩最多

    //cout << root->childs.size();
    // simple heuristic
    /*
    float lowest = INFINITY;
    int lowestMove = 0;
    float score = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
            {
                if (generateNumber == 3)
                {
                    board[i][j] = 3;
                    score = evaluateState(board);
                    board[i][j] = 0;
                }
                else
                {
                    board[i][j] = 1;
                    score = evaluateState(board);
                    board[i][j] = 0;
                }
                if (score < lowest)
                {
                    lowest = score;
                    lowestMove = 4*i+j;
                }
            }
        }
    }
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
            {
                return 4*i+j;
            }
        }
    }
    */
    
    
    //return lowestMove;
    return generateRandomTile(board);
}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	return;
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
