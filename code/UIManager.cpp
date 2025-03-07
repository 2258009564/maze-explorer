#include "UIManager.h"
#include <Windows.h>
using namespace std;

// 颜色控制函数
void setConsoleColor(int textColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor);
}

// 显示迷宫，同时覆盖显示玩家位置（用高亮的 '^' 表示）和敌人位置（用 'E' 表示）
void displayMaze(const vector<vector<char>> &maze, int playerX, int playerY, const vector<Enemy> &enemies)
{
    int mazeRows = maze.size();
    int mazeCols = maze[0].size();

    // 获取控制台句柄
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 保存原始颜色属性
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD originalAttrs = consoleInfo.wAttributes;

    for (int i = 0; i < mazeRows; i++)
    {
        for (int j = 0; j < mazeCols; j++)
        {
            // 检查是否有敌人在此位置
            bool isEnemy = false;
            bool isFrozenEnemy = false;
            for (const auto &enemy : enemies)
            {
                if (enemy.getX() == i && enemy.getY() == j)
                {
                    isEnemy = true;
                    isFrozenEnemy = enemy.isFrozen();
                    break;
                }
            }

            if (i == playerX && j == playerY)
            {
                // 设置玩家位置为亮绿色
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "我";
            }
            else if (isEnemy)
            {
                if (isFrozenEnemy)
                {
                    // 冻结的敌人显示为亮蓝色
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                }
                else
                {
                    // 普通敌人显示为亮紫色
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                }
                cout << "鬼";
            }
            else if (maze[i][j] == '@')
            {
                // 设置终点为亮红色
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "家";
            }
            else if (maze[i][j] == '!')
            {
                // 设置陷阱为亮黄色
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "危";
            }
            else if (maze[i][j] == ' ')
            {
                // 设置通道为白色
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << "  ";
            }
            else
            {
                // 墙壁保持默认颜色
                SetConsoleTextAttribute(hConsole, originalAttrs);
                // cout << maze[i][j];
                cout << "墙";
            }

            // 每输出一个字符后恢复原始颜色
            SetConsoleTextAttribute(hConsole, originalAttrs);
        }
        cout << endl;
    }
}

void ShowMenu()
{
    // 设置控制台输出编码为 UTF-8，确保中文能正确显示
    SetConsoleOutputCP(CP_UTF8);

    // 设置窗口标题
    SetConsoleTitle(L"MazeExplorer -经典模式");

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

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "\n          欢迎来到 Maze Explorer！\n\n";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "  在这片迷宫中，你将用智慧和勇气\n";
    cout << "  挑战未知的道路，避开致命陷阱";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "（鬼/危）";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "，\n  寻找通向胜利的出口";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "（家）\n";

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    cout << "       按任意键开始冒险...\n"
         << endl;

    // 恢复默认颜色
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    system("pause");
}

// 显示游戏失败（触碰陷阱）时的艺术字
void ShowGameOverArt()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

    cout << R"(
   ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ 
  ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗
  ██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝
  ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║██║   ██║██╔══╝  ██╔══██╗
  ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝╚██████╔╝███████╗██║  ██║
   ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═╝  ╚═╝
)" << endl;
    cout << "==================【你永远迷失在了迷宫中。游戏结束】==================" << endl
         << endl;

    // 恢复默认颜色
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// 显示游戏胜利（到达终点）时的艺术字
void ShowVictoryArt()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    cout << R"(
██╗   ██╗██╗ ██████╗████████╗ ██████╗ ██████╗ ██╗   ██╗██╗
██║   ██║██║██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗╚██╗ ██╔╝██║
██║   ██║██║██║        ██║   ██║   ██║██████╔╝ ╚████╔╝ ██║
╚██╗ ██╔╝██║██║        ██║   ██║   ██║██╔══██╗  ╚██╔╝  ╚═╝
 ╚████╔╝ ██║╚██████╗   ██║   ╚██████╔╝██║  ██║   ██║   ██╗
  ╚═══╝  ╚═╝ ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝   ╚═╝   ╚═╝                                                           
)" << endl;
    cout << "==================【恭喜你成功到达终点！】==================" << endl
         << endl;

    // 恢复默认颜色
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

