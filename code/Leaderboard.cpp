#include "Leaderboard.h"
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <direct.h>

using namespace std;

// 获取排行榜文件路径 - 使用可执行文件所在目录
string GetLeaderboardFilePath()
{
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);

    // 获取目录路径（去掉文件名部分）
    string path(exePath);
    size_t lastSlash = path.find_last_of("\\/");
    if (lastSlash != string::npos)
    {
        path = path.substr(0, lastSlash + 1);
    }

    return path + "leaderboard.dat";
}

// 初始化排行榜文件 - 如果文件不存在则创建
void InitializeLeaderboard()
{
    string filepath = GetLeaderboardFilePath();

    // 检查文件是否存在
    ifstream fileCheck(filepath);
    if (!fileCheck)
    {
        // 文件不存在，创建一个空文件
        ofstream newFile(filepath, ios::binary);
        if (!newFile)
        {
            cerr << "无法创建排行榜文件！路径：" << filepath << endl;
        }
        else
        {
            cout << "排行榜文件已创建：" << filepath << endl;
            newFile.close();
        }
    }
    else
    {
        fileCheck.close();
    }
}

// 获取当前日期时间字符串
string GetCurrentDateTimeString()
{
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    tm local_time;
    localtime_s(&local_time, &now_time);

    stringstream ss;
    ss << put_time(&local_time, "%Y-%m-%d %H:%M");
    return ss.str();
}

// 检查排行榜文件是否可写
bool IsLeaderboardWritable()
{
    string filepath = GetLeaderboardFilePath();

    // 尝试打开文件进行写入
    ofstream testFile(filepath, ios::binary | ios::app);
    if (!testFile.is_open())
    {
        return false;
    }
    testFile.close();
    return true;
}

// 保存分数到排行榜
bool SaveScore(const string &playerName, int score)
{
    // 确保排行榜文件存在
    InitializeLeaderboard();

    // 检查排行榜文件是否可写
    if (!IsLeaderboardWritable())
    {
        cerr << "排行榜文件无法写入！" << endl;
        return false;
    }

    string filepath = GetLeaderboardFilePath();
    vector<ScoreRecord> records;
    bool playerExists = false;

    // 读取现有记录
    ifstream inFile(filepath, ios::binary);
    if (inFile.is_open())
    {
        ScoreRecord record;
        while (inFile.read(reinterpret_cast<char *>(&record), sizeof(ScoreRecord)))
        {
            // 检查是否已有该玩家的记录
            if (strcmp(record.playerName, playerName.c_str()) == 0)
            {
                // 如果新分数更高，则更新记录
                if (score > record.score)
                {
                    record.score = score;
                    string dateStr = GetCurrentDateTimeString();
                    strncpy_s(record.date, sizeof(record.date), dateStr.c_str(), _TRUNCATE);
                }
                playerExists = true;
                records.push_back(record);
            }
            else
            {
                records.push_back(record);
            }
        }
        inFile.close();
    }

    // 如果玩家不存在，添加新记录
    if (!playerExists)
    {
        ScoreRecord newRecord;
        // 安全地复制玩家名称，确保不超过缓冲区
        strncpy_s(newRecord.playerName, sizeof(newRecord.playerName), playerName.c_str(), _TRUNCATE);
        newRecord.score = score;

        // 获取并保存当前日期时间
        string dateStr = GetCurrentDateTimeString();
        strncpy_s(newRecord.date, sizeof(newRecord.date), dateStr.c_str(), _TRUNCATE);

        records.push_back(newRecord);
    }

    // 按分数降序排序
    sort(records.begin(), records.end(), [](const ScoreRecord &a, const ScoreRecord &b)
         { return a.score > b.score; });

    // 只保留前10名
    if (records.size() > 10)
    {
        records.resize(10);
    }

    // 保存回文件
    ofstream outFile(filepath, ios::binary | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "无法创建排行榜文件！" << endl;
        return false;
    }

    for (const auto &record : records)
    {
        outFile.write(reinterpret_cast<const char *>(&record), sizeof(ScoreRecord));
    }

    outFile.close();
    return true;
}

// 显示排行榜
void ShowLeaderboard()
{
    // 确保排行榜文件存在
    InitializeLeaderboard();

    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << R"(
 ██╗     ███████╗ █████╗ ██████╗ ███████╗██████╗ ██████╗  ██████╗  █████╗ ██████╗ ██████╗ 
 ██║     ██╔════╝██╔══██╗██╔══██╗██╔════╝██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██╔══██╗██╔══██╗
 ██║     █████╗  ███████║██║  ██║█████╗  ██████╔╝██████╔╝██║   ██║███████║██████╔╝██║  ██║
 ██║     ██╔══╝  ██╔══██║██║  ██║██╔══╝  ██╔══██╗██╔══██╗██║   ██║██╔══██║██╔══██╗██║  ██║
 ███████╗███████╗██║  ██║██████╔╝███████╗██║  ██║██████╔╝╚██████╔╝██║  ██║██║  ██║██████╔╝
 ╚══════╝╚══════╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝ 
                                                               
    )" << endl
         << endl;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "                           无尽模式排行榜\n\n";

    // 显示表头
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << setw(6) << left << "排名"
         << setw(15) << left << "玩家名"
         << setw(10) << left << "得分"
         << "日期时间" << endl;

    cout << "    -----------------------------------------------------" << endl;

    // 读取排行榜
    string filepath = GetLeaderboardFilePath();
    vector<ScoreRecord> records;
    ifstream inFile(filepath, ios::binary);

    if (!inFile.is_open())
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "\n                   排行榜文件无法打开！\n";
        cout << "                   文件路径：" << filepath << "\n\n";
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    else
    {
        ScoreRecord record;
        while (inFile.read(reinterpret_cast<char *>(&record), sizeof(ScoreRecord)))
        {
            records.push_back(record);
        }
        inFile.close();
    }

    // 显示排行榜数据
    if (records.empty())
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "\n                     暂无排行数据！\n";
    }
    else
    {
        for (size_t i = 0; i < records.size(); i++)
        {
            if (i == 0)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // 金色
            }
            else if (i == 1)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); // 银色
            }
            else if (i == 2)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // 铜色
            }
            else
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 普通色
            }

            cout << setw(6) << left << (i + 1)
                 << setw(15) << left << records[i].playerName
                 << setw(10) << left << records[i].score
                 << records[i].date << endl;
        }
    }

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "\n\n                    按任意键返回主菜单...";

    _getch();
}
