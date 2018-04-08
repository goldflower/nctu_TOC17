#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from Fib2x3Solver import *
import sys
# you may use any arguments you need (perhaps to load an external table?)

fib = [0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610]
arrayBoard = [[0, 0, 0], [0, 0, 0]]



# fib的對應表
fib_dic = dict()
count = 0
for i in fib:
    fib_dic[i] = count
    count += 1

# board的對應表
f = open('score_table.txt')
lines = f.readlines()
f.close()

boardDict = dict()
for line in lines:
    l = line.split()
    #print(l[0], l[1], l[2])
    boardDict[int(l[0])] = (float(l[1]), int(l[2]))
print("Initialization finished")


# input problems
while True:
    exists = True
    key = 0
    for i in range(2):
        for j in range(3):
            try:
                s = input()
                if int(s) == float(s):
                    try:
                        key += fib_dic[int(s)]*(15**(3*i+j))
                    except KeyError:
                        exists = False
                else:
                    print('Bye')
                    sys.exit(0)
            except TypeError:
                print('Bye')
                sys.exit(0)
    print(key)
    expectedScore = -1
    if not exists:
        bestMove = None
    else:
        expectedScore = boardDict[key][0]
        bestMove = boardDict[key][1]
    bestMoveDirection = ""
    if bestMove == 0:
        bestMoveDirection = "Up"
    elif bestMove == 1:
        bestMoveDirection = "Right"
    elif bestMove == 2:
        bestMoveDirection = "Down"
    elif bestMove == 3:
        bestMoveDirection = "Left"
    elif bestMove == -1:
        bestMoveDirection = "Cannot move"
    else:
        bestMoveDirection = "Invalid move number"
    #print("Problem {}:".format(counter))
    if exists:
        print("Best move: ", bestMoveDirection)
        print("Expected score: ", round(expectedScore, 10))
    else:
        print("Expected score: ", round(expectedScore, 10))
