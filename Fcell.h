#ifndef _FCELL_H_
#define _FCELL_H_

#include <string>

// #define X 14
// #define Y 18
// extern int cell[X][Y];  //  include先から参照していいですよ宣言

#define maxSizeX 50
#define maxSizeY 50


void roomSize(int, int);
int maxDeskCountx();
int maxDeskCounty();

void firstCell_1(int, int, int);    //  壁0,1
void firstCell_2(int, int ,int);    //  壁2

int nextRule(int, int, int, int, int);  //  オートマトンルール
void nextCell_1();  //  オートマトン移動
void nextCell_2();  //  直接移動

bool fileExists(std::string);   //  ファイル存在判定
void printCell(std::string, int, int, int);  //  結果ファイル出力

int remain();  //  0,1のセルの合計

#endif // _FCELL_H_