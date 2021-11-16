#include "Fcell.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <time.h>

#define notDisplayMode 1
#define cmdDisplayMode 2

int roomSizex;              //  壁含む教室のサイズx
int roomSizey;              //  壁含む教室のサイズy
int studentCount;           //  配置数
int deskCountx;             //  机x
int deskCounty;             //  机y
int maxdcx;                 //  机xの最大値
int maxdcy;                 //  机yの最大値
int displayMode;            //  displayモード
int allTestCount;           //  試行回数
std::string hedFileName;    //  出力ファイル名

int timeCount;      //  世代数
int existCell;      //  滞在人数 

int main(int argc, char** argv){   //   0,1直接移動
    std::cout << "Type roomSizex (14) (3 <= rsx <= " << maxSizeX << ")" << std::endl;
    std::cin >> roomSizex;
    while(roomSizex > maxSizeX || roomSizex < 3){
        if(roomSizex > maxSizeX){
            std::cout << "\033[31m" << "error: too large! Type roomSizex again (3 <= rsx <= " << maxSizeX << ")" << "\033[m" << std::endl;
        }
        if(roomSizex < 3){
            std::cout << "\033[31m" << "error: too low! Type roomSizex again (3 <= rsx <= " << maxSizeX << ")" << "\033[m" << std::endl;
        }
        std::cin >> roomSizex;
    }
    std::cout << "Type roomSizey (18) (3 <= rsy <= " << maxSizeY << ")" << std::endl;
    std::cin >> roomSizey;
    while(roomSizey > maxSizeY || roomSizey < 3){
        if(roomSizey > maxSizeY){
            std::cout << "\033[31m" << "error: too large! Type roomSizey again (3 <= rsy <= " << maxSizeY << ")" << "\033[m" << std::endl;
        }
        if(roomSizey < 3){
            std::cout << "\033[31m" << "error: too low! Type roomSizey again (3 <= rsy <= " << maxSizeY << ")" << "\033[m" << std::endl;
        }
        std::cin >> roomSizey;
    }
    roomSize(roomSizex, roomSizey);    //   壁含む教室のサイズを他関数に引き渡し
    
    std::cout << "Type studentCount (sc <= " << (roomSizex - 2) * (roomSizey - 2) << ")" << std::endl;
    std::cin >> studentCount;
    while(studentCount > (roomSizex - 2) * (roomSizey - 2)){
        std::cout << "\033[31m" << "error: too large! Type studentCount again (rsy <= " << (roomSizex - 2) * (roomSizey - 2) << ")" << "\033[m" << std::endl;
        std::cin >> studentCount;
    }

    maxdcx = maxDeskCountx();   //  机xの最大値
    maxdcy = maxDeskCounty();   //  机yの最大値
    std::cout << "Type deskCountx (dcx <= " << maxdcx << ")" << std::endl;
    std::cin >> deskCountx;
    while(deskCountx > maxdcx){
        std::cout << "\033[31m" << "error: too large! Type deskCountx again (dcx <= " << maxdcx << ")" << "\033[m" << std::endl;
        std::cin >> deskCountx;
    }
    std::cout << "Type deskCounty (dcy <= " << maxdcy << ")" << std::endl;
    std::cin >> deskCounty;
    while(deskCounty > maxdcy){
        std::cout << "\033[31m" << "error: too large! Type deskCounty again (dcy <= " << maxdcy << ")" << "\033[m" << std::endl;
        std::cin >> deskCounty;
    }
    
    std::cout << "Type printFileName" << std::endl;
    std::cin >> hedFileName;
    while(fileExists(hedFileName)){
        std::cout << "\033[31m" << "error: alreadey exists! Type printFileName again" << "\033[m" << std::endl;
        std::cin >> hedFileName;
    }

    std::cout << "Type display mode (only txt: " << notDisplayMode << " cmd: " << cmdDisplayMode << ")" << std::endl;
    std::cin >> displayMode;

    std::cout << "Type allTestCount" << std::endl;
    std::cin >> allTestCount;

        /*  実行パート  */
    srand((unsigned int)time(NULL));
    for(int testCount = 1; testCount <= allTestCount; testCount++){
        std::cout << std::endl << "test_" << testCount << " start! >>" << std::endl;

        timeCount = 0;  //  世代数
        firstCell_2(studentCount, deskCountx, deskCounty);  //  初期配置設定  引数は(配置数, 机x{x <= (X - 2) / 2}, 机y{y <= (Y - 2) / 2})
        
        existCell = remain();    //  調査
        printCell(hedFileName, testCount, timeCount, existCell);     //  記録
        if(displayMode == cmdDisplayMode){
            coutCell(timeCount, existCell);
            Sleep(500);
        }
        
        while(existCell > 0){
            timeCount++;  //  世代数
            nextCell_2();    //   配置更新   
            
            existCell = remain();    //  調査
            printCell(hedFileName, testCount, timeCount, existCell);   //  記録
            if(displayMode == cmdDisplayMode){
                coutCell(timeCount, existCell);
                Sleep(500);
            }
        }
        std::cout << "test_" << testCount << " has done!" << std::endl;
    } 
    std::cout << "all tests have done!";
    system("pause");
}