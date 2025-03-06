#include "Menu.h"
#include "UIManager.h"
#include <conio.h>
#include <iomanip>

using namespace std;

// 显示主菜单并获取用户选择
MenuOption ShowMainMenu()
{
    int selectedOption = 0;
    const int optionCount = 6;
    bool menuActive = true;

    vector<string> options = {
        "开始游戏",
        "无尽模式",
        "排行榜",
        "制作人",
        "游戏提示",
        "退出游戏"};

    while (menuActive)
    {
        system("cls");

        // 显示标题艺术字
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        cout << R"(
███╗   ███╗ █████╗ ███████╗███████╗    ███████╗██╗  ██╗██████╗ ██╗      ██████╗ ██████╗ ███████╗██████╗ 
████╗ ████║██╔══██╗╚══███╔╝██╔════╝    ██╔════╝╚██╗██╔╝██╔══██╗██║     ██╔═══██╗██╔══██╗██╔════╝██╔══██╗
██╔████╔██║███████║  ███╔╝ █████╗      █████╗   ╚███╔╝ ██████╔╝██║     ██║   ██║██████╔╝█████╗  ██████╔╝
██║╚██╔╝██║██╔══██║ ███╔╝  ██╔══╝      ██╔══╝   ██╔██╗ ██╔═══╝ ██║     ██║   ██║██╔══██╗██╔══╝  ██╔══██╗
██║ ╚═╝ ██║██║  ██║███████╗███████╗    ███████╗██╔╝ ██╗██║     ███████╗╚██████╔╝██║  ██║███████╗██║  ██║
╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝    ╚══════╝╚═╝  ╚═╝╚═╝     ╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝                            
        )" << endl;

        // 以高亮显示选中的选项
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "\n\n                              主菜单\n\n";

        for (int i = 0; i < optionCount; i++)
        {
            if (i == selectedOption)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "                        > " << options[i] << " <\n";
            }
            else
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << "                          " << options[i] << "\n";
            }
        }

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cout << "\n\n           使用↑↓键或TAB键选择，Enter确认\n";

        // 获取用户输入
        int key = _getch();

        // 处理键盘输入
        if (key == 224) // 方向键前缀
        {
            key = _getch(); // 获取方向键的实际值
            switch (key)
            {
            case 72: // 上箭头
                selectedOption = (selectedOption - 1 + optionCount) % optionCount;
                break;
            case 80: // 下箭头
                selectedOption = (selectedOption + 1) % optionCount;
                break;
            }
        }
        else if (key == 9) // Tab键
        {
            selectedOption = (selectedOption + 1) % optionCount;
        }
        else if (key == 13) // 回车键
        {
            menuActive = false;
        }
        // 移除数字键选择功能
    }

    // 返回对应的枚举值
    switch (selectedOption)
    {
    case 0:
        return MenuOption::START_GAME;
    case 1:
        return MenuOption::ENDLESS_MODE;
    case 2:
        return MenuOption::LEADERBOARD;
    case 3:
        return MenuOption::CREDITS;
    case 4:
        return MenuOption::GAME_TIPS;
    case 5:
        return MenuOption::EXIT;
    default:
        return MenuOption::NONE;
    }
}

// 显示制作人信息
void ShowCredits()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << R"(
  ██████╗██████╗ ███████╗██████╗ ██╗████████╗███████╗
 ██╔════╝██╔══██╗██╔════╝██╔══██╗██║╚══██╔══╝██╔════╝
 ██║     ██████╔╝█████╗  ██║  ██║██║   ██║   ███████╗
 ██║     ██╔══██╗██╔══╝  ██║  ██║██║   ██║   ╚════██║
 ╚██████╗██║  ██║███████╗██████╔╝██║   ██║   ███████║
  ╚═════╝╚═╝  ╚═╝╚══════╝╚═════╝ ╚═╝   ╚═╝   ╚══════╝                                                                             
    )" << endl;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "\n\n                     游戏制作人：alisa22580\n\n";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "                      感谢您游玩迷宫探索者！\n";
    cout << "                   这个项目是迷宫探索游戏的实现\n\n";

    cout << "               © 2025 alisa22580 保留所有权利\n\n";

    cout << "\n\n                    按任意键返回主菜单...";

    _getch();
}

// 显示游戏提示
void ShowGameTips()
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << R"(
  ██████╗  █████╗ ███╗   ███╗███████╗    ████████╗██╗██████╗ ███████╗
 ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ╚══██╔══╝██║██╔══██╗██╔════╝
 ██║  ███╗███████║██╔████╔██║█████╗         ██║   ██║██████╔╝███████╗
 ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝         ██║   ██║██╔═══╝ ╚════██║
 ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗       ██║   ██║██║     ███████║
  ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝       ╚═╝   ╚═╝╚═╝     ╚══════╝                                         
    )" << endl
         << endl;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "                           【游戏操作】\n\n";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "  • 移动: W(上), A(左), S(下), D(右)\n";
    cout << "  • 技能选择: TAB键可以在不同技能间切换\n";
    cout << "  • 使用技能: Enter键使用当前选择的技能\n";
    cout << "  • 退出游戏: Q键\n\n";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "                           【地图元素】\n\n";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "  • 玩家: ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "我";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "- 这是你在迷宫中的位置\n";

    cout << "  • 墙壁: ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "墙";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "- 无法通过的障碍物\n";

    cout << "  • 陷阱: ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "危";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "- 踩到会导致游戏结束\n";

    cout << "  • 终点: ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "家";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "- 到达此处获得胜利\n";

    cout << "  • 敌人: ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "鬼";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "- 会追逐玩家，接触会导致游戏失败\n";

    cout << "  • 冻结敌人: ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "鬼";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "- 被冻结的敌人暂时不会移动\n\n";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "                            【技能系统】\n\n";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "  • 传送: 随机传送到一个安全位置\n";
    cout << "  • 墙破: 打破玩家周围一圈的墙壁\n";
    cout << "  • 冻结: 使所有敌人停止行动五回合\n\n";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "                           【游戏模式】\n\n";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "  • 普通模式: 完成一次迷宫挑战\n";
    cout << "  • 无尽模式: 难度逐渐增加，看你能走多远\n\n";

    cout << "\n\n                    按任意键返回主菜单...";

    _getch();
}
