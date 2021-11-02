#include <stdlib.h>
#include <time.h>
#define X 14
#define Y 18
int cell[X][Y];

void nextCell_test(){  //  直接移動
    int* tempCell = &cell[0][0];    //  tempCellとcellを同期
    int tempCell_2[X][Y];   //  次の世代の仮cell
    for(int sx = 1;sx < X - 1;sx++){
        for(int sy = 1; sy < Y - 1; sy++){
            tempCell_2[sx][sy] = 0;   //  初期化
            if(cell[sx][sy] != 0){
                if(cell[sx][sy - 1] == 0){
                    tempCell_2[sx][sy - 1] = cell[sx][sy];
                }else if(cell[sx - 1][sy] == 0){
                    tempCell_2[sx - 1][sy] = cell[sx][sy];
                }else{
                    tempCell_2[sx][sy] = cell[sx][sy];
                }   
            }   //  上優先で移動or待機
        }
    }
    tempCell = &tempCell_2[0][0];   //  世代更新 (cell[][]にtempCell_2[][]を代入) これでいけるのか？？？
}


int main(){
    const char* somep = "asd";
    char aaa = *somep;
}   //  わからん