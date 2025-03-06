#pragma once

#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>
#include <memory>
#include "CommonDefs.h"
#include "Enemy.h"
#include "Skill.h"

class GameController
{
private:
    std::vector<std::vector<char>> maze;
    int rows, cols;
    int playerX, playerY;
    int endX, endY;
    GameState state;

    // 敌人相关
    std::vector<Enemy> enemies;
    int enemySpeed; // 敌人移动速度(1-5)
    int enemyCount; // 敌人数量
    int maxEnemies; // 最大敌人数量

    // 技能相关
    std::vector<std::unique_ptr<Skill>> skills;
    int selectedSkillIndex; // 当前选中的技能索引

    // 游戏计数器
    int turnCounter;

public:
    // 构造函数
    GameController();

    // 初始化游戏
    bool initialize();

    // 获取迷宫尺寸输入
    bool getMazeSize();

    // 设置敌人参数
    bool setupEnemies();

    // 生成迷宫
    bool generateAndValidateMaze();

    // 初始化敌人
    void spawnEnemies();

    // 初始化技能
    void initializeSkills();

    // 运行游戏主循环
    void run();

    // 处理用户输入
    bool handleInput();

    // 更新敌人
    void updateEnemies();

    // 更新技能冷却时间
    void updateSkills();

    // 检查游戏状态
    void checkGameState();

    // 显示技能信息
    void displaySkillInfo();

    // 寻找安全位置(用于敌人生成和传送技能)
    std::pair<int, int> findSafeLocation();

    // 技能执行方法 - 供Skill类调用
    bool teleportPlayerToSafeLocation();
    bool breakWallsAroundPlayer();
    bool freezeAllEnemies(int turns);

    // 当前游戏状态
    GameState getState() const { return state; }

    // 获取迷宫 - 供技能类调用
    const std::vector<std::vector<char>> &getMaze() const { return maze; }

    // 修改迷宫 - 供技能类调用
    void setMazeCell(int x, int y, char value);

    // 友元类，用于访问私有成员
    friend class TeleportSkill;
    friend class WallBreakerSkill;
    friend class FreezeEnemiesSkill;
};
