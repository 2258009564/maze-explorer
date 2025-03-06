#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "GameController.h"

// 无尽模式类
class EndlessMode
{
private:
    int currentLevel;
    int score;
    std::string playerName;
    bool quitEndlessMode;

    // 根据当前级别设置难度参数
    void SetupLevelDifficulty(GameController &game);

public:
    EndlessMode();

    // 运行无尽模式
    void Run();

    // 获取玩家姓名
    bool GetPlayerName();

    // 显示当前级别信息
    void ShowLevelInfo();

    // 显示最终得分和保存
    void ShowFinalScore();
};
