#include "printCell.hpp"
#include "firstCell.hpp"
#include <fstream>
#include <string>

void printCell(int fileCount, int timeCount, int remain){
    std::ofstream writing_file;
    std::string filename = "result_" + std::to_string(fileCount) + ".txt";
    writing_file.open(filename, std::ios::app);
    writing_file << "<" << timeCount << ">" << std::endl;
    for(int y = 0; y < Y; y++){
        for(int x =0; x < X; x++){     
            writing_file << cell[x][y] << " ";
        }
        writing_file << std::endl;
    }
    writing_file << '/' << remain << std::endl << std::endl;
}