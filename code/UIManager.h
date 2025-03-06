#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
#include "Enemy.h"

// 颜色控制函数
void setConsoleColor(int textColor);

// 显示迷宫，同时覆盖显示玩家位置和敌人位置
void displayMaze(const std::vector<std::vector<char>> &maze, int playerX, int playerY,
                 const std::vector<Enemy> &enemies = std::vector<Enemy>());

// 显示主菜单
void ShowMenu();

// 显示游戏失败（触碰陷阱）时的艺术字
void ShowGameOverArt();

// 显示游戏胜利（到达终点）时的艺术字
void ShowVictoryArt();


