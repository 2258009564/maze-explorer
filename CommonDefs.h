#pragma once

#include <vector>
#include <string>

// 用于记录墙壁信息：墙在 maze 中的坐标和其相邻待拓展的单元格（cell）
struct Wall
{
    int wx, wy; // 迷宫中墙壁的坐标
    int cx, cy; // 与墙壁相邻的待扩展单元格（cell）在 cell grid 中的坐标
};

// 游戏状态枚举
enum class GameState
{
    RUNNING,
    WIN,
    LOSE,
    QUIT
};
