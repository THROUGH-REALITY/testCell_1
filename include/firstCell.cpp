#include "firstCell.hpp"
#include <stdlib.h>
#include <time.h>

int cell[X][Y];    //   グローバル変数cellの定義

void firstCell_1(int firstCellCount, int deskCountx, int deskCounty){   //  0,1 壁0,1
    for(int x =0; x < X; x++){
        cell[x][0] = 1;
    }   //  上端
    cell[0][1] = 0;    //  出口
    for(int y = 2; y < Y; y++){
        cell[0][y] = 1;
    }   //  左右端
    for(int x = 1; x < X; x++){
        for(int y = 1; y < Y; y++){
            cell[x][y] = 0;
        }
    }   //  初期化

    if(deskCountx * deskCounty != 0){
        int deskGapx = (X - 2) / (deskCountx);
        int deskGapy = (Y - 2) / (deskCounty);
        for(int dx = 1; dx <= deskCountx; dx++){
            for(int dy = 1; dy <= deskCounty; dy++){
                cell[deskGapx * dx][deskGapy * dy] = 2;
            }
        }   //  机(障害物)配置
    }

    srand((unsigned int)time(NULL));
    for(int i = 0; i < firstCellCount; i++){
        int ramx = 1 + rand() % (X - 2);
        int ramy = 1 + rand() % (Y - 2);
        if(cell[ramx][ramy] == 0){
            cell[ramx][ramy] = 1;
        }else{
            i -= 1;
        }
    }   //  [1 <= ramx <= X-1],[1 <= ramy <= Y-1]の範囲でランダム選択 >> cellがまだ0なら1を代入,代入済みならやり直し
}

void firstCell_2(int firstCellCount, int deskCountx, int deskCounty){   //  0,1 壁2
    for(int x =0; x < X; x++){
        cell[x][0] = 2;
        cell[x][Y - 1] = 2;
    }   //  上下端
    cell[0][1] = 0;    //  出口
    cell[X - 1][1] = 2;
    for(int y = 2; y < Y; y++){
        cell[0][y] = 2;
        cell[X - 1][y] = 2;
    }   //  左右端
    for(int x = 1; x < X - 1; x++){
        for(int y = 1; y < Y -1; y++){
            cell[x][y] = 0;
        }
    }   //  初期化

    if(deskCountx * deskCounty != 0){
        int deskGapx = (X - 2) / (deskCountx);
        int deskGapy = (Y - 2) / (deskCounty);
        for(int dx = 1; dx <= deskCountx; dx++){
            for(int dy = 1; dy <= deskCounty; dy++){
                cell[deskGapx * dx][deskGapy * dy] = 2;
            }
        }   //  机(障害物)配置
    }

    srand((unsigned int)time(NULL));
    for(int i = 0; i < firstCellCount; i++){
        int ramx = 1 + rand() % (X - 2);
        int ramy = 1 + rand() % (Y - 2);
        if(cell[ramx][ramy] == 0){
            cell[ramx][ramy] = 1;
        }else{
            i -= 1;
        }
    }   //  [1 <= ramx <= X-1],[1 <= ramy <= Y-1]の範囲でランダム選択 >> cellがまだ0なら1を代入,代入済みならやり直し
}