#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include "CommonDefs.h"

// 生成迷宫：maze 大小为 (2*rows+1) x (2*cols+1)，随机生成起点和终点
void generateMaze(int rows, int cols, std::vector<std::vector<char>> &maze, int &startX, int &startY, int &endX, int &endY);

// 增加迷宫复杂度：随机打通一些墙壁创建环路
void addComplexity(std::vector<std::vector<char>> &maze, int rows, int cols, int complexity);

// 增强路径复杂度：创建更复杂的迷宫路径
void enhancePathComplexity(std::vector<std::vector<char>> &maze, int startX, int startY, int endX, int endY);

// 在迷宫中随机放置陷阱
void placeTraps(std::vector<std::vector<char>> &maze, int rows, int cols, double trapProbability);
