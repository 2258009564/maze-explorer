#pragma once

#include <vector>
#include <cmath>

class Enemy
{
private:
    int x, y;        // 敌人位置
    int speed;       // 移动速度(1-5)，1最快，5最慢
    int moveCounter; // 移动计数器
    bool frozen;     // 是否被冻结
    int frozenTurns; // 剩余冻结回合数

public:
    Enemy(int startX, int startY, int moveSpeed);

    // 尝试向玩家移动
    void move(const std::vector<std::vector<char>> &maze, int playerX, int playerY);

    // 检查此回合是否应该移动
    bool canMoveThisTurn();

    // 重置移动计数器
    void resetMoveCounter();

    // 获取位置
    int getX() const { return x; }
    int getY() const { return y; }

    // 设置位置
    void setPosition(int newX, int newY)
    {
        x = newX;
        y = newY;
    }

    // 冻结敌人
    void freeze(int turns);

    // 更新冻结状态
    void updateFrozenState();

    // 检查是否被冻结
    bool isFrozen() const { return frozen; }
};
