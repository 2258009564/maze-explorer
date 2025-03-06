#pragma once

#include <vector>
#include <queue>
#include <stack>
#include <utility>

// 计算两点间的最短路径长度
int calculateShortestPath(const std::vector<std::vector<char>> &maze, int startX, int startY, int endX, int endY);

// 使用DFS检查从起点到终点是否有可达路径
bool checkPathExists(const std::vector<std::vector<char>> &maze, int startX, int startY, int endX, int endY);
