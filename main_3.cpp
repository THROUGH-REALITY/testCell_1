#include "Fcell.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

int roomSizex;              //  壁含む教室のサイズx
int roomSizey;              //  壁含む教室のサイズy
int studentCount;           //  配置数
int deskCountx;             //  机x
int deskCounty;             //  机y
int maxdcx;                 //  机xの最大値
int maxdcy;                 //  机yの最大値
int allTestCount;           //  試行回数
std::string hedFileName;    //  出力ファイル名

int timeCount;      //  世代数
int existCell;      //  滞在人数 

int main(int argc, char** argv){   //   0,1直接移動
    std::cout << "Type roomSizex (14) (rsx <= " << maxSizeX << ")" << std::endl;
    std::cin >> roomSizex;
    while(roomSizex > maxSizeX){
        std::cout << "\x1b[31m" << "error: too large! Type roomSizex again (rsx <= " << maxSizeX << ")" << std::endl;
        std::cin >> roomSizex;
    }
    std::cout << "\x1b[39m" << "Type roomSizey (18) (rsx <= " << maxSizeY << ")" << std::endl;
    std::cin >> roomSizey;
    while(roomSizey > maxSizeY){
        std::cout << "\x1b[31m" << "error: too large! Type roomSizey again (rsy <= " << maxSizeY << ")" << std::endl;
        std::cin >> roomSizey;
    }
    roomSize(roomSizex, roomSizey);    //   壁含む教室のサイズを他関数に引き渡し
    
    std::cout << "\x1b[39m" << "Type studentCount (sc <= " << (roomSizex - 2) * (roomSizey - 2) << ")" << std::endl;
    std::cin >> studentCount;
    while(studentCount > (roomSizex - 2) * (roomSizey - 2)){
        std::cout << "\x1b[31m" << "error: too large! Type studentCount again (rsy <= " << (roomSizex - 2) * (roomSizey - 2) << ")" << std::endl;
        std::cin >> studentCount;
    }

    maxdcx = maxDeskCountx();   //  机xの最大値
    maxdcy = maxDeskCounty();   //  机yの最大値
    std::cout << "\x1b[39m" << "Type deskCountx (dcx <= " << maxdcx << ")" << std::endl;
    std::cin >> deskCountx;
    while(deskCountx > maxdcx){
        std::cout << "\x1b[31m" << "error: too large! Type deskCountx again (dcx <= " << maxdcx << ")" << std::endl;
        std::cin >> deskCountx;
    }
    std::cout << "\x1b[39m" << "Type deskCounty (dcy <= " << maxdcy << ")" << std::endl;
    std::cin >> deskCounty;
    while(deskCounty > maxdcy){
        std::cout << "\x1b[31m" << "error: too large! Type deskCounty again (dcy <= " << maxdcy << ")" << std::endl;
        std::cin >> deskCounty;
    }
    
    std::cout << "\x1b[39m" << "Type printFileName" << std::endl;
    std::cin >> hedFileName;
    while(fileExists(hedFileName)){
        std::cout << "\x1b[31m" << "error: alreadey exists! Type printFileName again" << std::endl;
        std::cin >> hedFileName;
    }
    std::cout << "\x1b[39m" << "Type allTestCount" << std::endl;
    std::cin >> allTestCount;

    for(int testCount = 1; testCount <= allTestCount; testCount++){
        std::cout << std::endl << "test_" << testCount << " start! >>" << std::endl;

        timeCount = 0;  //  世代数
        firstCell_2(studentCount, deskCountx, deskCounty);  //  初期配置設定  引数は(配置数, 机x{x <= (X - 2) / 2}, 机y{y <= (Y - 2) / 2})
        
        existCell = remain();    //  調査
        printCell(hedFileName, testCount, timeCount, existCell);     //  記録
        std::cout << "time: " << timeCount << ", existCell: " << existCell << std::endl;
        
        while(existCell > 0){
            timeCount++;  //  世代数
            nextCell_2();    //   配置更新   
            
            existCell = remain();    //  調査
            printCell(hedFileName, testCount, timeCount, existCell);   //  記録
            std::cout << "time: " << timeCount << ", existCell: " << existCell << std::endl;
        }
        std::cout << "test_" << testCount << " has done!" << std::endl;
    } 
    std::cout << "all tests have done!";
    system("pause");
}