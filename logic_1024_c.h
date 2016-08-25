//
//  logic_1024_c.h
//  Game-1024
//
//  Created by zhaimengyang on 8/25/16.
//  Copyright © 2016 zhaimengyang. All rights reserved.
//

#ifndef logic_1024_c_h
#define logic_1024_c_h

#include <stdio.h>
#include <stdlib.h>
#define X 4
#define Y 4
#define Start 6
#define Prov 2

void start(int *p);

int isDied(int (*p)[Y]);

int provNums(int *p);

void printMap(int (*p)[Y]);

int inPut(int (*p)[Y]);

#endif /* logic_1024_c_h */
