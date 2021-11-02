#include "include/firstCell.hpp" // X,Y,cell[X][Y]
#include "include/nextCell.hpp"
#include "include/remaining.hpp"
#include "include/printCell.hpp"
#include <stdio.h>

extern int cell[X][Y];

int main(){   //   0,1オートマトン
    for(int testCount = 1; testCount <= 1 /* 試行回数 */; testCount++){
        int timeCount = 0;  //  世代数
        int existCell;  //  滞在人数
        firstCell_1(40);  //  初期配置設定  引数は配置数
        
        existCell = remaining_1();    //  調査
        printCell(testCount, timeCount, existCell);     //  記録
        printf("test_%d start >>%nt == %d, cell == %d%n", testCount, timeCount, existCell);
        
        while(existCell > 0){
            timeCount += 1;  //  世代数
            nextCell_1();    //   配置更新   
            
            existCell = remaining_1();    //  調査
            printCell(testCount, timeCount, existCell);   //  記録
            printf("%nt == %d, cell == %d%n", timeCount, existCell);
        }
        printf("test_%d done!%n", testCount);
    } 
    printf("all tests have done!");
    return 0;
}