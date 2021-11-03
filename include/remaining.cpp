#include "firstCell.hpp"
#include "remaining.hpp"

int remaining_1(){  //  0,1のみ(cellの合計)
    int rem = 0;
    for(int x = 1; x < X - 1; x++){
        for(int y = 1; y < Y - 1; y++){
            rem += cell[x][y];
        }
    }
    return rem;
}

int remaining_2(){  //  障害物あり(0,1のcellの合計)
    int rem = 0;
    for(int x = 1; x < X - 1; x++){
        for(int y = 1; y < Y - 1; y++){
            if(cell[x][y] <= 1){
                rem += cell[x][y];
            }
        }
    }
    return rem;
}