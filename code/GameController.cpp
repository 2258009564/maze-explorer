#include "GameController.h"
#include "MazeGenerator.h"
#include "PathFinder.h"
#include "UIManager.h"
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

// 构造函数
GameController::GameController()
    : rows(0), cols(0), playerX(0), playerY(0), endX(0), endY(0), state(GameState::RUNNING),
      enemySpeed(3), enemyCount(0), maxEnemies(0), selectedSkillIndex(0), turnCounter(0)
{
}

// 初始化游戏
bool GameController::initialize()
{
    if (!getMazeSize())
    {
        return false;
    }

    if (!setupEnemies())
    {
        return false;
    }

    if (!generateAndValidateMaze())
    {
        return false;
    }

    // 初始化技能
    initializeSkills();

    // 生成敌人
    spawnEnemies();

    return true;
}

// 获取迷宫尺寸输入
bool GameController::getMazeSize()
{
    bool validInput = false;

    // 循环直到获取有效输入
    while (!validInput)
    {
        cout << "请输入迷宫的行数和列数 迷宫将按照 (2 * rows + 1) x (2 * cols + 1) 的形式生成: ";
        cin >> rows >> cols;

        if (rows < 5 || cols < 5) // 增加最小尺寸限制，确保有足够空间
        {
            cout << "迷宫尺寸过小，请至少输入5 * 5 ！\n";
            // 清空输入缓冲区
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else
        {
            validInput = true;
        }
    }

    return true;
}

// 设置敌人参数
bool GameController::setupEnemies()
{
    // 根据迷宫大小计算最大敌人数量
    maxEnemies = sqrt(rows * cols) / 2;
    maxEnemies = max(maxEnemies, 1);

    bool validInput = false;

    cout << "请输入敌人数量 (1-" << maxEnemies << "): ";
    while (!validInput)
    {
        cin >> enemyCount;

        if (cin.fail() || enemyCount < 1 || enemyCount > maxEnemies)
        {
            cout << "无效输入，请输入1到" << maxEnemies << "之间的数字: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else
        {
            validInput = true;
        }
    }

    validInput = false;
    cout << "请输入敌人速度 (1-5，1最快，5最慢): ";
    while (!validInput)
    {
        cin >> enemySpeed;

        if (cin.fail() || enemySpeed < 1 || enemySpeed > 5)
        {
            cout << "无效输入，请输入1到5之间的数字: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else
        {
            validInput = true;
        }
    }

    return true;
}

// 生成迷宫并验证有效性
bool GameController::generateAndValidateMaze()
{
    int pathLength;

    // 循环生成迷宫，直到确保起点到终点可达
    do
    {
        generateMaze(rows, cols, maze, playerX, playerY, endX, endY);

        // 放置陷阱，10% 概率
        placeTraps(maze, rows, cols, 0.1);

        // 检查路径可达性
        pathLength = calculateShortestPath(maze, playerX, playerY, endX, endY);

        // 如果路径不可达，则重新生成
        if (pathLength == -1)
        {
            cout << "正在重新生成可达的迷宫..." << endl;
            this_thread::sleep_for(chrono::milliseconds(50));
        }
        // 确保路径有足够的复杂度 - 至少是迷宫尺寸的两倍
        else if (pathLength < (rows + cols))
        {
            cout << "正在增加迷宫复杂度..." << endl;
            this_thread::sleep_for(chrono::milliseconds(50));
            pathLength = -1; // 强制重新生成
        }
    } while (pathLength == -1);

    return true;
}

// 初始化技能
void GameController::initializeSkills()
{
    skills.push_back(make_unique<TeleportSkill>());
    skills.push_back(make_unique<WallBreakerSkill>());
    skills.push_back(make_unique<FreezeEnemiesSkill>());
}

// 生成敌人
void GameController::spawnEnemies()
{
    enemies.clear();

    for (int i = 0; i < enemyCount; i++)
    {
        // 找一个安全的位置放置敌人
        auto [enemyX, enemyY] = findSafeLocation();

        // 确保敌人不会太靠近玩家起点
        while (abs(enemyX - playerX) + abs(enemyY - playerY) < 10)
        {
            auto [newX, newY] = findSafeLocation();
            enemyX = newX;
            enemyY = newY;
        }

        enemies.emplace_back(enemyX, enemyY, enemySpeed);
    }
}

// 寻找安全位置
pair<int, int> GameController::findSafeLocation()
{
    int x, y;

    // 寻找一个非墙、非陷阱、非终点的位置
    do
    {
        x = 1 + rand() % (maze.size() - 2);
        y = 1 + rand() % (maze[0].size() - 2);
    } while (maze[x][y] != ' ' || (x == playerX && y == playerY));

    return {x, y};
}

// 运行游戏主循环
void GameController::run()
{
    // 设置窗口标题
    SetConsoleTitle(L"MazeExplorer -游戏进行中！");

    // 初始显示一次迷宫和技能信息
    system("cls");
    displayMaze(maze, playerX, playerY, enemies);
    displaySkillInfo();
    cout << "使用WASD移动，TAB/↑↓键切换技能，Enter键释放技能，Q退出\n";

    // 游戏主循环
    while (state == GameState::RUNNING)
    {
        // 处理用户输入（敌人移动已在handleInput中处理）
        if (handleInput())
        {
            // 刷新显示
            system("cls");
            displayMaze(maze, playerX, playerY, enemies);
            displaySkillInfo();
            cout << "使用WASD移动，TAB/↑↓键切换技能，Enter键释放技能，Q退出\n";
        }
        else
        {
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    }

    // 游戏结束显示
    switch (state)
    {
    case GameState::WIN:
        ShowVictoryArt();
        break;
    case GameState::LOSE:
        ShowGameOverArt();
        break;
    default:
        break;
    }

    cout << "按任意键返回主菜单..." << endl;
    _getch();

    // 注意：这里不再需要额外的退出逻辑，因为函数正常返回后会回到调用它的main函数中的游戏循环
}

// 处理用户输入
bool GameController::handleInput()
{
    if (!_kbhit())
        return false;

    int input = _getch();

    // 处理移动
    int newX = playerX, newY = playerY;
    bool playerMoved = false; // 标记玩家是否进行了移动操作

    if (input == 'q' || input == 'Q')
    {
        state = GameState::QUIT;
        return true;
    }
    else if (input == 'w' || input == 'W')
    {
        newX--;
        playerMoved = true;
    }
    else if (input == 's' || input == 'S')
    {
        newX++;
        playerMoved = true;
    }
    else if (input == 'a' || input == 'A')
    {
        newY--;
        playerMoved = true;
    }
    else if (input == 'd' || input == 'D')
    {
        newY++;
        playerMoved = true;
    }
    else if (input == '\t')
    {
        // 切换选择的技能
        selectedSkillIndex = (selectedSkillIndex + 1) % skills.size();
        return true; // 更新显示但不移动敌人
    }
    else if (input == 0 || input == 224) // 方向键可能是0或224前缀
    {
        int arrowKey = _getch(); // 获取具体方向键

        if (arrowKey == 72) // 上箭头
        {
            // 向上选择技能（考虑循环）
            selectedSkillIndex = (selectedSkillIndex + skills.size() - 1) % skills.size();
            return true; // 更新显示但不移动敌人
        }
        else if (arrowKey == 80) // 下箭头
        {
            // 向下选择技能
            selectedSkillIndex = (selectedSkillIndex + 1) % skills.size();
            return true; // 更新显示但不移动敌人
        }
        // 左右箭头可能用于其他功能，这里不做处理
    }
    else if (input == '\r' || input == '\n') // 检测Enter键
    {
        // 使用当前选中的技能
        if (selectedSkillIndex >= 0 && selectedSkillIndex < skills.size())
        {
            bool used = skills[selectedSkillIndex]->use(this);
            return used; // 如果技能使用成功，更新显示但不移动敌人
        }
        return false;
    }
    else
    {
        return false; // 无效输入，不更新游戏状态
    }

    // 如果是玩家移动操作，需要进行边界和碰撞检查
    if (playerMoved)
    {
        // 检查移动边界
        if (newX < 0 || newX >= maze.size() || newY < 0 || newY >= maze[0].size())
        {
            return false;
        }

        // 检查是否撞墙
        if (maze[newX][newY] == '#')
        {
            return false;
        }

        // 检查陷阱
        if (maze[newX][newY] == '!')
        {
            playerX = newX;
            playerY = newY;
            state = GameState::LOSE;
            return true;
        }

        // 检查终点
        if (maze[newX][newY] == '@')
        {
            playerX = newX;
            playerY = newY;
            state = GameState::WIN;
            return true;
        }

        // 执行移动
        playerX = newX;
        playerY = newY;

        // 玩家移动回合结束，敌人应该移动
        turnCounter++; // 只在玩家实际移动时增加回合计数

        // 更新敌人位置
        updateEnemies();

        // 更新技能冷却
        updateSkills();

        // 检查游戏状态（是否被敌人抓到）
        checkGameState();

        return true;
    }

    return false;
}

// 更新敌人
void GameController::updateEnemies()
{
    for (auto &enemy : enemies)
    {
        enemy.updateFrozenState(); // 更新冻结状态

        if (enemy.canMoveThisTurn())
        {
            // 记录之前的位置
            int prevX = enemy.getX();
            int prevY = enemy.getY();

            // 移动敌人
            enemy.move(maze, playerX, playerY);

            // 检查是否与玩家相撞
            if (enemy.getX() == playerX && enemy.getY() == playerY)
            {
                state = GameState::LOSE;
                return;
            }

            // 检查敌人间碰撞，如果碰撞则恢复位置
            for (auto &otherEnemy : enemies)
            {
                if (&enemy != &otherEnemy &&
                    enemy.getX() == otherEnemy.getX() &&
                    enemy.getY() == otherEnemy.getY())
                {
                    enemy.setPosition(prevX, prevY);
                    break;
                }
            }
        }
    }
}

// 更新技能冷却
void GameController::updateSkills()
{
    for (auto &skill : skills)
    {
        skill->updateCooldown();
    }
}

// 检查游戏状态
void GameController::checkGameState()
{
    // 检查是否被敌人抓到
    for (const auto &enemy : enemies)
    {
        if (enemy.getX() == playerX && enemy.getY() == playerY)
        {
            state = GameState::LOSE;
            return;
        }
    }
}

// 显示技能信息
void GameController::displaySkillInfo()
{
    cout << "\n技能列表:\n";
    for (size_t i = 0; i < skills.size(); i++)
    {
        cout << (i == selectedSkillIndex ? ">" : " ")
             << "[" << (i + 1) << "] "
             << skills[i]->getName() << " - "
             << skills[i]->getDescription();

        if (skills[i]->isAvailable())
        {
            cout << " (可用)";
        }
        else
        {
            cout << " (冷却中: " << skills[i]->getCurrentCooldown() << "回合)";
        }
        cout << endl;
    }
}

// 技能：传送到安全位置
bool GameController::teleportPlayerToSafeLocation()
{
    auto [newX, newY] = findSafeLocation();
    playerX = newX;
    playerY = newY;

    cout << "你使用了传送技能，被传送到一个安全的位置！\n";
    system("pause");
    return true;
}

// 技能：打破周围的墙壁
bool GameController::breakWallsAroundPlayer()
{
    bool brokeAnyWall = false;

    // 扫描玩家周围3x3区域
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            int nx = playerX + dx;
            int ny = playerY + dy;

            // 确保在边界内
            if (nx > 0 && nx < maze.size() - 1 && ny > 0 && ny < maze[0].size() - 1)
            {
                // 如果是墙壁，打破它
                if (maze[nx][ny] == '#')
                {
                    maze[nx][ny] = ' ';
                    brokeAnyWall = true;
                }
            }
        }
    }

    if (brokeAnyWall)
    {
        cout << "你使用了破墙技能，周围的墙壁碎裂了！\n";
        system("pause");
    }
    else
    {
        cout << "周围没有墙壁可以打破！\n";
        system("pause");
        return false; // 没有使用成功
    }

    return true;
}

// 技能：冻结所有敌人
bool GameController::freezeAllEnemies(int turns)
{
    if (enemies.empty())
    {
        cout << "没有敌人可以冻结！\n";
        system("pause");
        return false;
    }

    for (auto &enemy : enemies)
    {
        enemy.freeze(turns);
    }

    cout << "你使用了冻结技能，所有敌人被冻结了" << turns << "回合！\n";
    system("pause");
    return true;
}

// 设置迷宫单元格的值
void GameController::setMazeCell(int x, int y, char value)
{
    if (x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size())
    {
        maze[x][y] = value;
    }
}
