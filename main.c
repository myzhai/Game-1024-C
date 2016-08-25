//
//  main.c
//  Game-1024
//
//  Created by zhaimengyang on 15/5/14.
//  Copyright (c) 2015年 zhaimengyang. All rights reserved.
//

#include <stdio.h>
#include "logic_1024_c.h"


int main(int argc, const char * argv[]) {
    int nums[X][Y] = {0};
    char ch;
Restart:
    start((int *)nums);
    do {
    NotDied:
        printMap(nums);
        if (inPut(nums)) {
            printf("退出游戏！");
            return 0;
        }
        printf("操作后\n");
        printMap(nums);
        if (provNums((int *)nums)) {
            if (isDied(nums)) {
                printf("还没死，继续呀!\n--------------------\n");
                goto NotDied;
            }
            else
            {
                printf("GAME  OVER\n是否继续？ Y/y继续，其它键退出: --> ");
                if ((ch = getchar()) == 'y' || ch =='Y') {
                    while (getchar() != '\n');
                    for (int i = 0; i < X; i++) {
                        for (int j = 0; j < Y; j++) {
                            nums[i][j] = 0;
                        }
                    }
                    goto Restart;
                } else
                    return 0;
            }
        }
        printf("加入随机数后\n");
    } while (1);
    return 0;
}