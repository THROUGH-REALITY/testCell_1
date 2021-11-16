#include "Fcell.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>
#include <cstdlib>

// int cell[X][Y];    //   グローバル変数cellの定義

static int cell[maxSizeX][maxSizeY];
static int sizex;
static int sizey;

void roomSize(int argx, int argy){
    sizex = argx;
    sizey = argy;
}

int maxDeskCountx(){
    return (sizex - 2) / 2;
}

int maxDeskCounty(){
    return (sizey - 2) / 2;
}


void firstCell_1(int firstCellCount, int deskCountx, int deskCounty){   //  0,1 壁0,1
    for(int x =0; x < sizex; x++){
        cell[x][0] = 1;
    }   //  上端
    cell[0][1] = 0;    //  出口
    for(int y = 2; y < sizey; y++){
        cell[0][y] = 1;
    }   //  左右端
    for(int x = 1; x < sizex; x++){
        for(int y = 1; y < sizey; y++){
            cell[x][y] = 0;
        }
    }   //  初期化

    if(deskCountx * deskCounty != 0){
        int deskGapx = (sizex - 2) / (deskCountx);
        int deskGapy = (sizey - 2) / (deskCounty);
        for(int dx = 1; dx <= deskCountx; dx++){
            for(int dy = 1; dy <= deskCounty; dy++){
                cell[deskGapx * dx][deskGapy * dy] = 2;
            }
        }   //  机(障害物)配置
    }

    for(int i = 0; i < firstCellCount; i++){
        int ramx = 1 + rand() % (sizex - 2);
        int ramy = 1 + rand() % (sizey - 2);
        if(cell[ramx][ramy] == 0){
            cell[ramx][ramy] = 1;
        }else{
            i -= 1;
        }
    }   //  [1 <= ramx <= sizex-1],[1 <= ramy <= sizey-1]の範囲でランダム選択 >> cellがまだ0なら1を代入,代入済みならやり直し
}

void firstCell_2(int firstCellCount, int deskCountx, int deskCounty){   //  0,1 壁2
    for(int x =0; x < sizex; x++){
        cell[x][0] = 2;
        cell[x][sizey - 1] = 2;
    }   //  上下端
    cell[0][1] = 0;    //  出口
    cell[(unsigned int)(sizex - 1)][1] = 2;
    for(int y = 2; y < sizey; y++){
        cell[0][y] = 2;
        cell[sizex - 1][y] = 2;
    }   //  左右端
    for(int x = 1; x < sizex - 1; x++){
        for(int y = 1; y < sizey -1; y++){
            cell[x][y] = 0;
        }
    }   //  初期化

    if(deskCountx * deskCounty != 0){
        int deskGapx = (sizex - 2) / (deskCountx);
        int deskGapy = (sizey - 2) / (deskCounty);
        for(int dx = 1; dx <= deskCountx; dx++){
            for(int dy = 1; dy <= deskCounty; dy++){
                cell[deskGapx * dx][deskGapy * dy] = 2;
            }
        }   //  机(障害物)配置
    }

    for(int i = 0; i < firstCellCount; i++){
        int ramx = 1 + rand() % (sizex - 2);
        int ramy = 1 + rand() % (sizey - 2);
        if(cell[ramx][ramy] == 0){
            cell[ramx][ramy] = 1;
        }else{
            i -= 1;
        }
    }   //  [1 <= ramx <= sizex-1],[1 <= ramy <= sizey-1]の範囲でランダム選択 >> cellがまだ0なら1を代入,代入済みならやり直し
}


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
    int tempCell[maxSizeX][maxSizeY];
    for(int sx = 1; sx < sizex - 1; sx++){
        for(int sy = 1; sy < sizey - 1; sy++){
            tempCell[sx][sy] = nextRule(cell[sx][sy - 1], cell[sx - 1][sy], cell[sx][sy], cell[sx + 1][sy], cell[sx][sy + 1]);
        }   //  上,左,中,右,下のセルに対してnextRuleを適用
    }
    for(int sx = 1;sx < sizex - 1;sx++){
        for(int sy = 1; sy < sizey - 1; sy++){
            cell[sx][sy] = tempCell[sx][sy];
        }
    }   //  世代更新
}

void nextCell_2(){  //  0,1直接移動
    cell[0][1] = 0;   //   出口は初期化
    for(int sx = 1;sx < sizex - 1;sx++){
        for(int sy = 1; sy < sizey - 1; sy++){
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


int remain(){  //  障害物あり(0,1のcellの合計)
    int rem = 0;
    for(int x = 1; x < sizex - 1; x++){
        for(int y = 1; y < sizey - 1; y++){
            if(cell[x][y] <= 1){
                rem += cell[x][y];
            }
        }
    }
    return rem;
}


bool fileExists(std::string hedFileName){
    std::string fileName = hedFileName + "_" + std::to_string(1) + ".txt";
    bool isExists = std::filesystem::exists(fileName);
    return isExists;
}

void printCell(std::string hedFileName, int fileCount, int timeCount, int remain){
    std::ofstream writing_file;
    std::ofstream writing_file2;
    std::ofstream writing_file3;
    std::string fileName = hedFileName + "_" + std::to_string(fileCount) + ".txt";
    std::string rfileName = hedFileName + "_allresult.txt";
    std::string rfileName2 = hedFileName + "_allresult_xlsx.txt";

    writing_file.open(fileName, std::ios::app);
    writing_file << "<" << timeCount << ">" << std::endl;
    for(int y = 0; y < sizey; y++){
        for(int x =0; x < sizex; x++){     
            writing_file << cell[x][y] << " ";
        }
        writing_file << std::endl;
    }
    writing_file << '/' << remain << std::endl << std::endl;

    if(fileCount == 0){        
        writing_file3.open(rfileName2, std::ios::app);
        writing_file3 << "test,time:" << std::endl;
    }

    if(timeCount == 0){
        writing_file2.open(rfileName, std::ios::app);
        writing_file2 << "<" << fileCount << ">" << std::endl;
        for(int y = 0; y < sizey; y++){
            for(int x = 0; x < sizex; x++){
                writing_file2 << cell[x][y] << " ";
            }
            writing_file2 << std::endl;
        }
    }

    if(remain == 0){
        writing_file2.open(rfileName, std::ios::app);
        writing_file2 << "t == " << timeCount << std::endl << std::endl;
        
        writing_file3.open(rfileName2, std::ios::app);
        writing_file3 << fileCount << ',' << timeCount << std::endl;
    }
}


void coutCell(int timeCount, int existCell){
    std::cout << "<" << timeCount << ">" << std::endl;
    for(int y = 0; y < sizey; y++){
        for(int x =0; x < sizex; x++){     
            if(cell[x][y] == 0){
                std::cout << "\033[m" << cell[x][y] << " ";
            }
            if(cell[x][y] == 1){
                std::cout << "\033[43m" << cell[x][y] << "\033[m" << " ";
            }
            if(cell[x][y] == 2){
                std::cout << "\033[44m" << cell[x][y] << "\033[m" << " ";
            }        
        }
        std::cout << "\033[m" << std::endl;
    }
    std::cout << '/' << existCell << std::endl << std::endl;
}