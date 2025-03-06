#include "PathFinder.h"

using namespace std;

// 计算两点间的最短路径长度
int calculateShortestPath(const vector<vector<char>> &maze, int startX, int startY, int endX, int endY)
{
    int rows = maze.size();
    int cols = maze[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<int>> distance(rows, vector<int>(cols, -1));

    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;
    distance[startX][startY] = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        if (x == endX && y == endY)
            return distance[x][y];

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dr[i];
            int ny = y + dc[i];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols &&
                !visited[nx][ny] && (maze[nx][ny] == ' ' || maze[nx][ny] == '@'))
            {
                visited[nx][ny] = true;
                distance[nx][ny] = distance[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return -1; // 路径不存在
}

// 使用DFS检查从起点到终点是否有可达路径
bool checkPathExists(const vector<vector<char>> &maze, int startX, int startY, int endX, int endY)
{
    int rows = maze.size();
    int cols = maze[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    // DFS使用栈进行遍历
    stack<pair<int, int>> s;
    s.push({startX, startY});
    visited[startX][startY] = true;

    // 四个方向：上、右、下、左
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    while (!s.empty())
    {
        auto [x, y] = s.top();
        s.pop();

        // 如果到达终点
        if (x == endX && y == endY)
        {
            return true;
        }

        // 探索四个方向
        for (int i = 0; i < 4; i++)
        {
            int newX = x + dr[i];
            int newY = y + dc[i];

            // 检查边界和是否可通行
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
                !visited[newX][newY] && (maze[newX][newY] == ' ' || maze[newX][newY] == '@'))
            {
                visited[newX][newY] = true;
                s.push({newX, newY});
            }
        }
    }

    return false;
}
