#include "nextCell.hpp"
#include "firstCell.hpp"

int nextRule(int a, int b, int c ,int d, int e){
    //  int row = (int)a * 10000 + (int)b * 1000 + (int)c * 100 + (int)d * 10 + (int)e;
    int next;
    if(a * b == 1){ 
        if(c == 0){
            if(d + e == 0){
                next = 0;   //  [1]{11}000
            }else{
                next = 1;   //  [3]{11}{001,010,011}
            }
        }else{
            next = 1;   //  [4]{11}{100,101,110,111}    /8
        }
    }else{
        if(c == 0){
            if(d + e == 0){
                next = 0;   //  [3]{00,01,10}{000}
            }else{
                next = 1;   //  [9]{00,01,10}{001,010,011}
            }
        }else{
            next = 0;   //  [12]{00,01,10}{100,101,110,111}    /24
        }
    } 
    return next;
}

void nextCell_1(){    //   0,1間接移動（セルオートマトン）
    int tempCell[X][Y];
    for(int sx = 1; sx < X - 1; sx++){
        for(int sy = 1; sy < Y - 1; sy++){
            tempCell[sx][sy] = nextRule(cell[sx][sy - 1], cell[sx - 1][sy], cell[sx][sy], cell[sx + 1][sy], cell[sx][sy + 1]);
        }   //  上,左,中,右,下のセルに対してnextRuleを適用
    }
    for(int sx = 1;sx < X - 1;sx++){
        for(int sy = 1; sy < Y - 1; sy++){
            cell[sx][sy] = tempCell[sx][sy];
        }
    }   //  世代更新
}

void nextCell_2(){  //  0,1直接移動
    cell[0][1] = 0;   //   出口は初期化
    for(int sx = 1;sx < X - 1;sx++){
        for(int sy = 1; sy < Y - 1; sy++){
            if(cell[sx][sy] == 1){
                cell[sx][sy] = 0;
                if(cell[sx][sy - 1] == 0){
                    cell[sx][sy - 1] = 1;
                }else if(cell[sx - 1][sy] == 0){
                    cell[sx - 1][sy] = 1;
                }else{
                    cell[sx][sy] = 1;
                }   
            }   //  上優先で優先で移動or待機
        }
    }
}