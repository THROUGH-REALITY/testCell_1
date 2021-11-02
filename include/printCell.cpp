#include "printCell.hpp"
#include "firstCell.hpp"
#include <fstream>

extern int cell[X][Y];

void printCell(int fileCount, int timeCount, int remain){ 
/*    int a = fileCount / 1000;
    int b = fileCount % 1000 / 100;
    int c = fileCount % 100 / 10;
    int d = fileCount % 10;
    char fileCountStr[] = {'0' + a, '0' + b, '0' + c, '0' + d, '\0'};*/

    char* fileCountStr;
    sprintf(fileCountStr,"%d",fileCount);   //  これでいけるんですかね？？？

    std::ofstream writing_file;
    std::string filename = "result_" + std::string(fileCountStr) + ".txt";
    writing_file.open(filename, std::ios::app);
    writing_file << "<" << timeCount << ">" << std::endl;
    for(int x =0; x < X; x++){
        for(int y = 0; y < Y; y++){
            writing_file << cell[x][y] << " ";
        }
        writing_file << std::endl;
    }
    writing_file << '/' << remain << std::endl << std::endl;
}