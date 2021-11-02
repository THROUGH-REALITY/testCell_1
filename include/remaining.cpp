#include "firstCell.hpp"
#include "remaining.hpp"

extern int cel[X][Y];

int remaining_1(){  //  0,1のみ(cellの合計)
    int rem = 0;
    for(int x = 1; x < X - 1; x++){
        for(int y = 1; y < Y - 1; y++){
            rem += cell[x][y];
        }
    }
    return rem;
}

int remaining_2(){  //  誰か居たら1加算
    int rem = 0;
    for(int x = 1; x < X - 1; x++){
        for(int y = 1; y < Y - 1; y++){
            if(cell[x][y] != 0){
                rem += 1;
            }
        }
    }
    return rem;
}