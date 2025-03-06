#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

// 记录结构体 - 使用定长字符数组而非std::string
struct ScoreRecord
{
    char playerName[15]; // 固定大小的字符数组，最多存储14个字符+'\0'
    int score;
    char date[20]; // 固定大小的字符数组，存储日期时间
};

// 初始化排行榜文件 - 如果文件不存在则创建
void InitializeLeaderboard();

// 获取排行榜文件路径
std::string GetLeaderboardFilePath();

// 保存分数到排行榜
bool SaveScore(const std::string &playerName, int score);

// 显示排行榜
void ShowLeaderboard();

// 获取当前日期时间字符串
std::string GetCurrentDateTimeString();

// 检查排行榜文件是否可写
bool IsLeaderboardWritable();
