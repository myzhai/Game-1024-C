//
//  logic_1024_c.c
//  Game-1024
//
//  Created by zhaimengyang on 8/25/16.
//  Copyright © 2016 zhaimengyang. All rights reserved.
//

#include "logic_1024_c.h"

int getThisScore(int (*p)[Y]){
    int thisScore = 1;
    int temp = **p;
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            if (*(*(p+i)+j) >= temp)
                temp = *(*(p+i)+j);
        }
    }
    for (int i = 0; i < temp; i++) {
        thisScore *= 2;
    }
    return thisScore;
}

void writeLogFile(int thisScore, int *p){
    FILE *fp = fopen("./log", "r+");
    if (fp != NULL) {
        if (p[0] <= thisScore)
            p[0] = thisScore;
        p[1] = thisScore;
        fwrite(p, sizeof(int), 2, fp);
    }
    fp = fopen("./log", "a");
    fwrite(&thisScore, sizeof(int), 1, fp);
    fclose(fp);
}

void start(int *p){
    int temp;
    int index;
    int tag[X*Y];
    
    for (int i = 0; i < X*Y; i++) {
        tag[i] = i;
    }
    for (int i = 0; i < Start; i++) {
        temp = tag[index = arc4random_uniform(X*Y)];
        tag[index] = tag[X*Y - (i + 1)];
        tag[X*Y - (i + 1)] = temp;
    }
    
    for (int i = X*Y - Start; i < X*Y; i++) {
        *(p + tag[i]) = arc4random_uniform(2) + 1;
    }
}

int isDied(int (*p)[Y]){
    for (int i = 0; i < X-1; i++) {
        for (int j = 0; j < Y-1; j++) {
            if (((*(*(p+i)+j)) == (*(*(p+i)+(j+1)))) || ((*(*(p+i)+j)) == (*(*(p+(i+1))+j))))
                return 1;
        }
    }
    return 0;
}

int provNums(int *p){
    int i1, i2, temp;
    int index = 0;
    int count = 0;
    int tag[X*Y] = {0};
    
    for (int i = 0; i < X*Y; i++) {
        if (*(p + i) == 0) {
            count++;
            tag[index++] = i;
        }
    }
    
    if (count >= 2) {
        i1 = tag[temp = arc4random_uniform(count)];
        for (int k = 0; k < count - temp - 1; k++) {
            tag[temp] = tag[temp+1];
            temp++;
        }
        i2 = tag[temp = arc4random_uniform(count-1)];
        
        *(p + i1) = arc4random_uniform(2) + 1;
        *(p + i2) = arc4random_uniform(2) + 1;
        return 0;
    }
    else if(count == 1){
        *(p + tag[0]) = arc4random_uniform(2) + 1;
        return 0;
    }
    else return 1;
}

void printMap(int (*p)[Y]){
    int temp = 0;
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            temp = *(*(p+i) + j);
            switch (temp) {
                case 1:
                    printf("   2\t");
                    break;
                case 2:
                    printf("   4\t");
                    break;
                case 3:
                    printf("   8\t");
                    break;
                case 4:
                    printf("  16\t");
                    break;
                case 5:
                    printf("  32\t");
                    break;
                case 6:
                    printf("  64\t");
                    break;
                case 7:
                    printf(" 128\t");
                    break;
                case 8:
                    printf(" 256\t");
                    break;
                case 9:
                    printf(" 512\t");
                    break;
                case 10:
                    printf("1024\t");
                    break;
                case 11:
                    printf("2048\t");
                    break;
                case 12:
                    printf("4096\t");
                    break;
                case 13:
                    printf("8192\t");
                    break;
                    
                default:printf("  **\t");
                    break;
            }
        }
        printf("\n");
    }
    printf("------------------------------\n");
}

void calcUp(int (*p)[Y]){
    for (int t = 0, i = X-1; t < X-1; t++) {
        for (int tem_i = i; tem_i > 0; tem_i--) {
            for (int j = 0; j < Y; j++) {
                if (*(*(p+tem_i-1) + j) == 0) {
                    *(*(p+tem_i-1) + j) = *(*(p+tem_i) + j);
                    *(*(p+tem_i) + j) = 0;
                } else if (*(*(p+tem_i-1) + j) == *(*(p+tem_i) + j)) {
                    *(*(p+tem_i-1) + j) += 1;
                    *(*(p+tem_i) + j) = 0;
                }
            }
        }
        i--;
    }
    
    for (int i = X-1; i > 0; i--) {
        for (int j = 0; j < Y; j++) {
            if (*(*(p+i-1) + j) == 0) {
                *(*(p+i-1) + j) = *(*(p+i) + j);
                *(*(p+i) + j) = 0;
            }
        }
    }
}

void calcDown(int (*p)[Y]){
    for (int t = 0, i = 0; t < X-1; t++) {
        for (int tem_i = i; tem_i < X-1; tem_i++) {
            for (int j = 0; j < Y; j++) {
                if (*(*(p+tem_i+1) + j) == 0) {
                    *(*(p+tem_i+1) + j) = *(*(p+tem_i) + j);
                    *(*(p+tem_i) + j) = 0;
                } else if (*(*(p+tem_i+1) + j) == *(*(p+tem_i) + j)) {
                    *(*(p+tem_i+1) + j) += 1;
                    *(*(p+tem_i) + j) = 0;
                }
            }
        }
        i++;
    }
    
    for (int i = 0; i < X-1; i++) {
        for (int j = 0; j < Y; j++) {
            if (*(*(p+i+1) + j) == 0) {
                *(*(p+i+1) + j) = *(*(p+i) + j);
                *(*(p+i) + j) = 0;
            }
        }
    }
}

void calcLeft(int (*p)[Y]){
    for (int t = 0, j = Y-1; t < Y-1; t++) {
        for (int i = 0; i < X; i++) {
            for (int tem_j = j; tem_j > 0; tem_j--) {
                if (*(*(p+i) + (tem_j-1)) == 0) {
                    *(*(p+i) + (tem_j-1)) = *(*(p+i) + tem_j);
                    *(*(p+i) + tem_j) = 0;
                } else if (*(*(p+i) + (tem_j-1)) == *(*(p+i) + tem_j)) {
                    *(*(p+i) + (tem_j-1)) += 1;
                    *(*(p+i) + tem_j) = 0;
                }
            }
        }
        j--;
    }
    
    for (int i = 0; i < X; i++) {
        for (int j = Y-1; j > 0; j--) {
            if (*(*(p+i) + (j-1)) == 0) {
                *(*(p+i) + (j-1)) = *(*(p+i) + j);
                *(*(p+i) + j) = 0;
            }
        }
    }
}

void calcRight(int (*p)[Y]){
    for (int t = 0, j = 0; t < Y-1; t++) {
        for (int i = 0; i < X; i++) {
            for (int tem_j = j; tem_j < Y-1; tem_j++) {
                if (*(*(p+i) + (tem_j+1)) == 0) {
                    *(*(p+i) + (tem_j+1)) = *(*(p+i) + tem_j);
                    *(*(p+i) + tem_j) = 0;
                } else if (*(*(p+i) + (tem_j+1)) == *(*(p+i) + tem_j)) {
                    *(*(p+i) + (tem_j+1)) += 1;
                    *(*(p+i) + tem_j) = 0;
                }
            }
        }
        j++;
    }
    
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y-1; j++) {
            if (*(*(p+i) + (j+1)) == 0) {
                *(*(p+i) + (j+1)) = *(*(p+i) + j);
                *(*(p+i) + j) = 0;
            }
        }
    }
}

int inPut(int (*p)[Y]){
    char dire = ' ';
    scanf("%c",&dire);
    switch ((int)dire) {
        case (int)'w':
        case (int)'W':calcUp(p);
            while (getchar() != '\n');
            break;
            
        case (int)'a':
        case (int)'A':calcLeft(p);
            while (getchar() != '\n');
            break;
            
        case (int)'s':
        case (int)'S':calcDown(p);
            while (getchar() != '\n');
            break;
            
        case (int)'d':
        case (int)'D':calcRight(p);
            while (getchar() != '\n');
            break;
            
        case (int)'q':
        case (int)'Q':return 1;
            
        default:
            while (getchar() != '\n');
            break;
    }
    return 0;
}
