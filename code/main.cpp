#include <cstdlib>
#include <ctime>
#include <iostream>
#include "GameController.h"
#include "UIManager.h"
#include "Menu.h"
#include "EndlessMode.h"
#include "Leaderboard.h"
#include <Windows.h>

int main()
{
    // 设置控制台输出编码为 UTF-8，确保中文能正确显示
    SetConsoleOutputCP(CP_UTF8);
    // 初始化随机种子
    srand(static_cast<unsigned int>(time(nullptr)));

    // 初始化排行榜文件
    InitializeLeaderboard();

    bool exitGame = false;

    // 游戏主循环
    while (!exitGame)
    {
        // 显示主菜单
        MenuOption option = ShowMainMenu();
        system("cls"); // 确保清屏

        switch (option)
        {
        case MenuOption::START_GAME:
        {
            // 显示经典的游戏菜单
            ShowMenu();

            // 创建并初始化游戏控制器
            GameController game;
            if (!game.initialize())
            {
                std::cout << "游戏初始化失败！" << std::endl;
                system("pause");
            }
            else
            {
                // 运行游戏主循环
                game.run();
            }

            // 确保游戏结束后清屏，以便重绘菜单
            system("cls");
        }
        break;

        case MenuOption::ENDLESS_MODE:
        {
            // 启动无尽模式
            EndlessMode endless;
            endless.Run();

            // 确保返回后清屏
            system("cls");
        }
        break;

        case MenuOption::LEADERBOARD:
            // 显示排行榜
            ShowLeaderboard();
            system("cls");
            break;

        case MenuOption::CREDITS:
            // 显示制作人信息
            ShowCredits();
            system("cls");
            break;

        case MenuOption::GAME_TIPS:
            // 显示游戏提示
            ShowGameTips();
            system("cls");
            break;

        case MenuOption::EXIT:
            // 退出游戏
            exitGame = true;
            break;

        default:
            break;
        }
    }

    return 0;
}
