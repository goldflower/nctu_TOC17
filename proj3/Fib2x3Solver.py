#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import copy
prob_1 = 0.75
prob_2 = 0.25
fib = [0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610]

def evaluteExpectedScore(arrayBoard):
    for i in range(4):
        if arrayBoard == move(arrayBoard, i):
            continue
        

def findBestMove(arrayBoard):
    return 0

def move(arrayBoard, direction):
    """
    input: 
        arrayBoard 2*3 list
        direction int 0~3
    return:
        tuple
        (2*3 result list, int score)
    """
    board = copy.deepcopy(arrayBoard)
    t = [[0,0,0,],[0,0,0]]
    score = 0
    # up
    if direction == 0:
        for i in range(3):
            add = arrayBoard[0][i] + arrayBoard[1][i]
            if add > arrayBoard[0][i] and \
                    add > arrayBoard[1][i] and \
                    add in fib:
                #board[0][i] = add
                t[0][i] = add
                score += add
                #board[1][i] = 0
                t[1][i] = 0
            elif arrayBoard[0][i] == 0:
                #board[0][i] = arrayBoard[1][i]
                t[0][i] = arrayBoard[1][i]
                #board[1][i] = 0
                t[1][i] = 0
            else:
                t[0][i] = arrayBoard[0][i]
                t[1][i] = arrayBoard[1][i]
        return (t, score)

    # down
    elif direction == 2:
        for i in range(3):
            add = arrayBoard[0][i] + arrayBoard[1][i]
            if add > arrayBoard[0][i] and \
                    add > arrayBoard[1][i] and \
                    add in fib:
                #board[1][i] = add
                t[1][i] = add
                score += add
                #board[0][i] = 0
                t[0][i] = 0
            elif arrayBoard[1][i] == 0:
                #board[1][i] = arrayBoard[0][i]
                t[1][i] = arrayBoard[0][i]
                #board[0][i] = 0
                t[0][i] = 0
            else:
                t[0][i] = arrayBoard[0][i]
                t[1][i] = arrayBoard[1][i]
        return (t, score)
    # left
    elif direction == 3:
        for i in range(2):
            add1 = arrayBoard[i][0] + arrayBoard[i][1]
            add2 = arrayBoard[i][1] + arrayBoard[i][2]
            add3 = arrayBoard[i][0] + arrayBoard[i][2]
            flag1 = add1 in fib and \
                    add1 > arrayBoard[i][0] and \
                    add1 > arrayBoard[i][1]
            flag2 = arrayBoard[i][0] == 0
            flag3 = add2 in fib and \
                    add2 > arrayBoard[i][1] and \
                    add2 > arrayBoard[i][2]
            flag4 = arrayBoard[i][1] == 0
            flag5 = add3 in fib and \
                    add3 > arrayBoard[i][0] and \
                    add3 > arrayBoard[i][2]
            if flag1:
                board[i][0] = add1
                score += add1
                board[i][1] = arrayBoard[i][2]
                board[i][2] = 0
            elif flag2:
                if flag3:
                    board[i][0] = add2
                    score += add2
                    board[i][1] = 0
                    board[i][2] = 0
                elif flag4:
                    board[i][0] = arrayBoard[i][2]
                    board[i][1] = 0
                    board[i][2] = 0
                elif not flag4:
                    board[i][0] = arrayBoard[i][1]
                    board[i][1] = arrayBoard[i][2]
                    board[i][2] = 0
                else:
                    exit(0)
            elif flag3:
                board[i][0] = arrayBoard[i][0]
                board[i][1] = add2
                score += add2
                board[i][2] = 0
            elif flag4:
                if flag5:
                    board[i][0] = add3
                    score += add3
                    board[i][1] = 0
                    board[i][2] = 0
                elif not flag5:
                    board[i][0] = arrayBoard[i][0]
                    board[i][1] = arrayBoard[i][2]
                    board[i][2] = 0
                else:
                    exit(0)
            elif not flag4:
                continue
            else:
                exit(0)
                
                
                
    # right
    elif direction == 1:
        for i in range(2):
            add1 = arrayBoard[i][2] + arrayBoard[i][1]
            add2 = arrayBoard[i][1] + arrayBoard[i][0]
            add3 = arrayBoard[i][0] + arrayBoard[i][2]
            flag1 = add1 in fib and \
                    add1 > arrayBoard[i][2] and \
                    add1 > arrayBoard[i][1]
            flag2 = arrayBoard[i][2] == 0
            flag3 = add2 in fib and \
                    add2 > arrayBoard[i][1] and \
                    add2 > arrayBoard[i][0]
            flag4 = arrayBoard[i][1] == 0
            flag5 = add3 in fib and \
                    add3 > arrayBoard[i][0] and \
                    add3 > arrayBoard[i][2]
            if flag1:
                board[i][2] = add1
                score += add1
                board[i][1] = arrayBoard[i][0]
                board[i][0] = 0
            elif flag2:
                if flag3:
                    board[i][2] = add2
                    score += add2
                    board[i][1] = 0
                    board[i][0] = 0
                elif flag4:
                    board[i][2] = arrayBoard[i][0]
                    board[i][1] = 0
                    board[i][0] = 0
                elif not flag4:
                    board[i][2] = arrayBoard[i][1]
                    board[i][1] = arrayBoard[i][0]
                    board[i][0] = 0
                else:
                    exit(0)
            elif flag3:
                board[i][2] = arrayBoard[i][2]
                board[i][1] = add2
                score += add2
                board[i][0] = 0
            elif flag4:
                if flag5:
                    board[i][2] = add3
                    score += add3
                    board[i][1] = 0
                    board[i][0] = 0
                elif not flag5:
                    board[i][2] = arrayBoard[i][2]
                    board[i][1] = arrayBoard[i][0]
                    board[i][0] = 0
                else:
                    exit(0)
            elif not flag4:
                continue
            else:
                exit(0)
    return (board, score)
    
def movable(arrayBoard):
    # 檢查上下
    add1 = arrayBoard[0][0] + arrayBoard[1][0]
    add2 = arrayBoard[0][1] + arrayBoard[1][1]
    add3 = arrayBoard[0][2] + arrayBoard[1][2]
    flag_UD = (add1 in fib and add1 > arrayBoard[0][0] and add1 > arrayBoard[1][0]) or \
              (add2 in fib and add2 > arrayBoard[0][1] and add2 > arrayBoard[1][1]) or \
              (add3 in fib and add3 > arrayBoard[0][2] and add3 > arrayBoard[1][2])
    if flag_UD:
        return True
        
    for i in range(2):
        # 檢查左右
        add1 = arrayBoard[i][0] + arrayBoard[i][1]
        add2 = arrayBoard[i][1] + arrayBoard[i][2]
        add3 = arrayBoard[i][0] + arrayBoard[i][2]
        flag_LR = (add1 in fib and add1 > arrayBoard[i][0] and add1 > arrayBoard[i][1]) or \
                  (add2 in fib and add2 > arrayBoard[i][1] and add2 > arrayBoard[i][2]) or \
                  (add3 in fib and add3 > arrayBoard[i][0] and add3 > arrayBoard[i][2] and arrayBoard[i][1] == 0)
        if flag_LR:
            return True
        
            
        for j in range(3):
            # 有0必定可移動
            if arrayBoard[i][j] == 0:
                return True
            
    return False
                
def illegal(arrayBoard):
    return 0