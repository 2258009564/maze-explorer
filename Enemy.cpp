#include "Enemy.h"
#include <cstdlib>
#include <queue>
#include <utility>
#include <vector>

Enemy::Enemy(int startX, int startY, int moveSpeed)
    : x(startX), y(startY), speed(moveSpeed), moveCounter(0), frozen(false), frozenTurns(0)
{
}

bool Enemy::canMoveThisTurn()
{
    if (frozen)
        return false;

    moveCounter++;
    if (moveCounter >= speed)
    {
        moveCounter = 0;
        return true;
    }
    return false;
}

void Enemy::resetMoveCounter()
{
    moveCounter = 0;
}

void Enemy::freeze(int turns)
{
    frozen = true;
    frozenTurns = turns;
}

void Enemy::updateFrozenState()
{
    if (frozen)
    {
        frozenTurns--;
        if (frozenTurns <= 0)
        {
            frozen = false;
        }
    }
}

// 使用简化的BFS寻找朝向玩家的最佳移动方向
void Enemy::move(const std::vector<std::vector<char>> &maze, int playerX, int playerY)
{
    // 如果被冻结，无法移动
    if (frozen)
        return;

    // 使用简单的BFS寻路算法找到朝向玩家的最佳移动
    std::vector<std::vector<bool>> visited(maze.size(), std::vector<bool>(maze[0].size(), false));
    std::vector<std::vector<std::pair<int, int>>> parent(maze.size(), std::vector<std::pair<int, int>>(maze[0].size(), {-1, -1}));

    std::queue<std::pair<int, int>> q;
    q.push({x, y});
    visited[x][y] = true;

    int dr[] = {-1, 1, 0, 0}; // 上下左右
    int dc[] = {0, 0, -1, 1};
    bool foundPath = false;

    // BFS寻路
    while (!q.empty() && !foundPath)
    {
        auto [currX, currY] = q.front();
        q.pop();

        // 如果到达玩家位置
        if (currX == playerX && currY == playerY)
        {
            foundPath = true;
            break;
        }

        // 探索四个方向
        for (int i = 0; i < 4; i++)
        {
            int newX = currX + dr[i];
            int newY = currY + dc[i];

            // 检查是否可以移动到该位置
            if (newX >= 0 && newX < maze.size() && newY >= 0 && newY < maze[0].size() &&
                !visited[newX][newY] && maze[newX][newY] != '#' && maze[newX][newY] != '!')
            {
                visited[newX][newY] = true;
                parent[newX][newY] = {currX, currY};
                q.push({newX, newY});
            }
        }
    }

    // 如果找到路径，沿路径回溯找到下一步移动
    if (foundPath)
    {
        int nextX = playerX;
        int nextY = playerY;

        // 回溯找到敌人旁边的第一步
        while (parent[nextX][nextY].first != x || parent[nextX][nextY].second != y)
        {
            int tempX = nextX;
            int tempY = nextY;
            nextX = parent[tempX][tempY].first;
            nextY = parent[tempX][tempY].second;

            // 如果回溯到起点附近，这就是敌人的下一步
            if (parent[nextX][nextY].first == x && parent[nextX][nextY].second == y)
            {
                break;
            }
        }

        // 执行移动
        x = nextX;
        y = nextY;
    }
    // 如果没找到路径，使用直接靠近的方法
    else
    {
        // 计算玩家和敌人间的距离
        int dx = playerX - x;
        int dy = playerY - y;

        // 尝试向玩家方向移动
        if (abs(dx) >= abs(dy))
        {
            int newX = x + (dx > 0 ? 1 : (dx < 0 ? -1 : 0));
            if (newX >= 0 && newX < maze.size() && maze[newX][y] != '#' && maze[newX][y] != '!')
            {
                x = newX;
                return;
            }
        }

        if (dy != 0)
        {
            int newY = y + (dy > 0 ? 1 : -1);
            if (newY >= 0 && newY < maze[0].size() && maze[x][newY] != '#' && maze[x][newY] != '!')
            {
                y = newY;
            }
        }
    }
}
