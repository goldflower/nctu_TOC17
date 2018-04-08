#ifndef __MCT_H__
#define __MCT_H__

#include <cmath>
#include <cassert>
#include <limits>
#include <stack>
#include <iostream>
#include <vector>

using namespace std;
class MCT{
public:
    vector<MCT*> childs;
    int selfCount;
    int position;
    int selfScore;
    float Q;
    static int totalCount;
    static float c;
    static void update(MCT* node, int score=0, int count=0) {
        node->selfScore += score;
        node->selfCount += count;
        node->Q = - (node->selfScore)/(node->selfCount) + c*sqrt(totalCount / node->selfCount);
    }
    static MCT *findMaxQ(vector<MCT*> childs)
    {
        float max = -INFINITY;
        MCT *node;
        for(int j = 0; j < childs.size(); j++)
        {
            if (childs.at(j)->Q > max)
            {
                max = childs.at(j)->Q;
                node = childs.at(j);
            }
        }
        return node;
    }
    MCT (int score, int pos) : selfScore(score), position(pos), selfCount(1){}
};


#endif