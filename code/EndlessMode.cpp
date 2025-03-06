#include "EndlessMode.h"
#include "Leaderboard.h"
#include "UIManager.h"
#include <conio.h>
#include <windows.h>

using namespace std;

// 无尽模式构造函数
EndlessMode::EndlessMode()
    : currentLevel(1), score(0), quitEndlessMode(false)
{
}

// 预设100个关卡的参数
// 每个关卡包含3个参数：迷宫大小、敌人数量、敌人速度(1最快-5最慢)
struct LevelParams
{
    int mazeSize;   // 迷宫大小（方形迷宫边长）
    int enemyCount; // 敌人数量
    int enemySpeed; // 敌人速度
};

// 100个关卡的预设参数
const LevelParams PRESET_LEVELS[100] = {
    // 关卡1-10：简单入门
    {5, 1, 5},
    {5, 1, 5},
    {6, 1, 5},
    {6, 1, 4},
    {7, 1, 4},
    {7, 1, 4},
    {8, 1, 3},
    {8, 1, 3},
    {9, 2, 3},
    {9, 2, 3},

    // 关卡11-20：初级挑战
    {10, 2, 3},
    {10, 2, 3},
    {11, 2, 3},
    {11, 2, 2},
    {12, 2, 2},
    {12, 3, 2},
    {13, 3, 2},
    {13, 3, 2},
    {14, 3, 2},
    {14, 3, 2},

    // 关卡21-30：中级挑战
    {14, 3, 2},
    {14, 4, 2},
    {15, 4, 2},
    {15, 4, 1},
    {15, 4, 1},
    {15, 5, 1},
    {16, 5, 1},
    {16, 5, 1},
    {16, 5, 1},
    {16, 6, 1},

    // 关卡31-40：高级挑战
    {16, 6, 1},
    {17, 6, 1},
    {17, 6, 1},
    {17, 7, 1},
    {17, 7, 1},
    {17, 7, 1},
    {18, 7, 1},
    {18, 7, 1},
    {18, 8, 1},
    {18, 8, 1},

    // 关卡41-50：专家级
    {18, 8, 1},
    {18, 8, 1},
    {19, 8, 1},
    {19, 8, 1},
    {19, 9, 1},
    {19, 9, 1},
    {19, 9, 1},
    {19, 9, 1},
    {20, 9, 1},
    {20, 9, 1},

    // 关卡51-60：大师级
    {20, 9, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},

    // 关卡61-100：无尽地狱（全部最高难度）
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1},
    {20, 10, 1}};

// 获取关卡参数 (确保不会数组越界)
const LevelParams &GetLevelParams(int level)
{
    // 关卡从1开始，数组索引从0开始
    int index = level - 1;

    // 确保索引在有效范围内
    if (index < 0)
        index = 0;
    if (index >= 100)
        index = 99;

    return PRESET_LEVELS[index];
}

// 根据当前级别设置难度参数，使用预设参数避免任何用户输入
void EndlessMode::SetupLevelDifficulty(GameController &game)
{
    // 获取当前关卡的预设参数
    const LevelParams &params = GetLevelParams(currentLevel);

    // 保存原始输入输出流缓冲区
    std::streambuf *origCin = std::cin.rdbuf();
    std::streambuf *origCout = std::cout.rdbuf();

    // 创建字符串流来代替标准输入和输出
    std::stringstream mockInput;
    std::stringstream mockOutput; // 用于捕获并丢弃输出提示

    // 向模拟输入流写入预设参数
    mockInput << params.mazeSize << " " << params.mazeSize * 1.5 << std::endl; // 迷宫大小 
    mockInput << params.enemyCount << std::endl;                         // 敌人数量
    mockInput << params.enemySpeed << std::endl;                         // 敌人速度

    // 重定向标准输入输出
    std::cin.rdbuf(mockInput.rdbuf());
    std::cout.rdbuf(mockOutput.rdbuf());

    // 调用游戏初始化方法，会自动从我们的模拟输入中读取参数
    game.initialize();

    // 还原标准输入输出
    std::cin.rdbuf(origCin);
    std::cout.rdbuf(origCout);
}

// 运行无尽模式
void EndlessMode::Run()
{
    // 设置窗口标题
    SetConsoleTitle(L"MazeExplorer -无尽模式");
    
    if (!GetPlayerName())
    {
        return; // 用户取消了输入
    }

    while (!quitEndlessMode)
    {
        // 显示当前级别信息
        ShowLevelInfo();

        // 创建游戏控制器并自动设置难度
        GameController game;

        // 设置难度并自动初始化游戏 - 不再需要玩家输入任何参数
        SetupLevelDifficulty(game);

        // 运行游戏
        game.run();

        // 获取游戏结果
        GameState result = game.getState();

        if (result == GameState::WIN)
        {
            // 胜利，进入下一级
            score += currentLevel * 100; // 根据级别计算得分
            currentLevel++;

            // 显示过关信息
            system("cls");
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "\n\n恭喜通过第 " << (currentLevel - 1) << " 关！\n";
            cout << "当前得分: " << score << "\n";
            cout << "即将进入第 " << currentLevel << " 关...\n";
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cout << "\n按任意键继续，或按 'Q' 退出无尽模式...";

            char key = _getch();
            if (key == 'q' || key == 'Q')
            {
                quitEndlessMode = true;
            }
        }
        else
        {
            // 失败或退出 - 游戏结束
            quitEndlessMode = true;
        }
    }

    // 显示最终得分并保存
    ShowFinalScore();

    // 正常返回主界面
}

// 获取玩家姓名
bool EndlessMode::GetPlayerName()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "\n\n                       无尽模式 - 玩家登记\n\n";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "  请输入您的名字 (最多14个字符)：";

    playerName = "";
    char ch;

    while (true)
    {
        ch = _getch();

        if (ch == 13) // Enter
        {
            if (!playerName.empty())
                break;
        }
        else if (ch == 27) // ESC
        {
            return false; // 用户取消
        }
        else if (ch == 8) // Backspace
        {
            if (!playerName.empty())
            {
                playerName.pop_back();
                cout << "\b \b";
            }
        }
        else if (ch >= 32 && ch <= 126) // 可打印字符
        {
            if (playerName.length() < 14)
            {
                playerName.push_back(ch);
                cout << ch;
            }
        }
    }

    return true;
}

// 显示当前级别信息
void EndlessMode::ShowLevelInfo()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 获取当前关卡参数以显示
    const LevelParams &params = GetLevelParams(currentLevel);

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "\n\n                       无尽模式 - 第 " << currentLevel << " 关\n\n";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "  玩家: " << playerName << "\n";
    cout << "  当前得分: " << score << "\n\n";

    // 根据关卡显示难度
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "  难度: ";

    // 根据关卡级别显示难度等级和具体参数
    if (currentLevel <= 10)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "简单入门";
    }
    else if (currentLevel <= 20)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "初级挑战";
    }
    else if (currentLevel <= 30)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "中级挑战";
    }
    else if (currentLevel <= 40)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "高级挑战";
    }
    else if (currentLevel <= 50)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "专家级";
    }
    else if (currentLevel <= 60)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "大师级";
    }
    else
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "无尽地狱";
    }

    // 显示当前关卡设置
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << " (迷宫大小: " << params.mazeSize << "×" << params.mazeSize;
    cout << ", 敌人: " << params.enemyCount << "个, 速度: " << params.enemySpeed << "/5)";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "\n\n  通关奖励: " << (currentLevel * 100) << "分";

    // 显示里程碑奖励
    if (currentLevel % 5 == 0)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << " + 额外里程碑奖励" << (300 * (currentLevel / 5)) << "分";
    }

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "\n\n  按任意键开始挑战...";

    _getch();
}

// 显示最终得分和保存
void EndlessMode::ShowFinalScore()
{
    // 只有玩家至少通过一关才记录分数
    if (score > 0)
    {
        system("cls");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "\n\n                     无尽模式 - 游戏结束\n\n";

        cout << "  玩家: " << playerName << "\n";
        cout << "  最终得分: " << score << "\n";
        cout << "  通过关卡: " << (currentLevel - 1) << "\n\n";

        // 确保在游戏退出前保存分数
        bool saved = false;

        // 尝试多次保存分数
        for (int attempts = 0; attempts < 3 && !saved; attempts++)
        {
            saved = SaveScore(playerName, score);
            if (!saved)
            {
                // 如果保存失败，等待一小段时间再重试
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "  尝试保存分数... (" << (attempts + 1) << "/3)\n";
                Sleep(500); // 等待500毫秒
            }
        }

        if (saved)
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "  您的分数已成功保存到排行榜！\n";
        }
        else
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << "  分数保存失败，排行榜可能无法访问。\n";
            cout << "  请确保程序有权限写入文件系统。\n";
        }

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << "\n  按任意键返回主菜单...";

        _getch();
    }
}