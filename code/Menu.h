#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <windows.h>

// 菜单选项枚举
enum class MenuOption
{
    START_GAME,
    ENDLESS_MODE,
    LEADERBOARD,
    CREDITS,
    GAME_TIPS,
    EXIT,
    NONE
};

// 显示主菜单并返回用户选择
MenuOption ShowMainMenu();

// 显示制作人信息
void ShowCredits();

// 显示游戏提示
void ShowGameTips();
