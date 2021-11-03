#include "include/firstCell.hpp" // X,Y,cell[X][Y]
#include "include/nextCell.hpp"
#include "include/remaining.hpp"
#include "include/printCell.hpp"
#include <iostream>

int studentCount;   //  配置数
int deskCountX;     //  机x
int deskCountY;     //  机y
int allTestCount;   //  試行回数
int timeCount;      //  世代数
int existCell;      //  滞在人数 

int main(int argc, char** argv){   //   0,1直接移動
    std::cout << "Type studentCount" << std::endl;
    std::cin >> studentCount;
    std::cout << std::endl << "Type deskCountX (dcx <= " << (X - 2) / 2 << ")" << std::endl;
    std::cin >> deskCountX;
    std::cout << std::endl << "Type deskCountY (dcy <= " << (Y - 2) / 2 << ")" << std::endl;
    std::cin >> deskCountY;
    std::cout << std::endl << "Type allTestCount" << std::endl;
    std::cin >> allTestCount;

    for(int testCount = 1; testCount <= allTestCount; testCount++){
        std::cout << std::endl << "test_" << testCount << " start! >>" << std::endl;

        timeCount = 0;  //  世代数
        firstCell_1(studentCount, deskCountX, deskCountY);  //  初期配置設定  引数は(配置数, 机x{x <= (X - 2) / 2}, 机y{y <= (Y - 2) / 2})
        
        existCell = remaining_2();    //  調査
        printCell(testCount, timeCount, existCell);     //  記録
        std::cout << "time == " << timeCount << ", existCell == " << existCell << std::endl;
        
        while(existCell > 0){
            timeCount++;  //  世代数
            nextCell_2();    //   配置更新   
            
            existCell = remaining_2();    //  調査
            printCell(testCount, timeCount, existCell);   //  記録
            std::cout << "time == " << timeCount << ", existCell == " << existCell << std::endl;
        }
        std::cout << "test_" << testCount << " has done!" << std::endl;
    } 
    std::cout << "all tests have done!";
    return 0;
}