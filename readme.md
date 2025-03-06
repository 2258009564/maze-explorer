<div align="center">
  <img src="assets/logo.png" alt="Maze Explorer Logo" width="200">
  <h1>Maze Explorer | 迷宫探险家</h1>
  
  [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
  [![Language: C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
  [![Platform: Windows](https://img.shields.io/badge/Platform-Windows-brightgreen.svg)](https://www.microsoft.com/windows)
  [![Version: 1.0.0](https://img.shields.io/badge/Version-1.0.0-orange.svg)](https://github.com/2258009564/mazeexplorer)
</div>

<p align="center"><i>穿梭迷宫、击败敌人、探索未知 - 控制台游戏的全新境界</i></p>

---

## 🌟 项目概览

**Maze Explorer** 是一款精心打造的控制台迷宫冒险游戏，采用现代 C++开发。游戏将玩家置于由算法精密生成的迷宫世界中，在这里，每一次探索都是独一无二的体验。面对诡谲多变的地形、智能的敌人 AI 和精妙的技能系统，玩家需要运用战略智慧，寻找通往胜利的道路。

<div align="center">
  <table>
    <tr>
      <td><b>🎮 多样化游戏模式</b></td>
      <td><b>🧠 挑战智力极限</b></td>
      <td><b>🏆 全球排行榜系统</b></td>
    </tr>
  </table>
</div>

## ✨ 核心特性

- **算法驱动的迷宫生成** — 每局游戏都拥有独特的迷宫布局，确保无限重玩价值
- **AI 智能敌人系统** — 采用高级寻路算法，提供真正的挑战性对抗体验
- **精心设计的技能机制** — 包括空间传送、地形改造与时间控制等多元化能力
- **高级控制台渲染技术** — 突破传统 ASCII 界限，呈现丰富多彩的游戏世界
- **双重游戏模式** — 经典模式挑战解谜能力，无尽模式考验生存技巧
- **云端排行榜** — 与全球玩家竞技，彰显你的探险天赋

## 🎯 游戏模式详解

<div align="center">
<table>
<tr>
    <th width="50%">🏰 经典模式</th>
    <th width="50%">⏱️ 无尽模式</th>
</tr>
<tr>
    <td>
    挑战完美平衡的迷宫难题，玩家可自定义迷宫规模与敌人密度，打造专属游戏体验。战略规划每一步，最终抵达终点获得胜利。
    </td>
    <td>
    在不断演化的迷宫中挑战自我极限，随时间推移难度指数级增长，敌人变得更加凶猛迅捷。你能创造多高的分数，在排行榜上留名？
    </td>
</tr>
</table>

## ⌨️ 操作指南
|    按键     | 功能                    |
| :---------: | ----------------------- |
| **W/A/S/D** | 角色移动（上/左/下/右） |
| **Tab/↑↓**  | 技能切换                |
|  **Enter**  | 技能释放                |
|    **Q**    | 退出游戏                |
</div>

## 🔮 高级技能系统

<div align="center">
  <table>
    <tr>
      <th>技能名称</th>
      <th>图标</th>
      <th>效果描述</th>
      <th>战略价值</th>
    </tr>
    <tr>
      <td>空间传送</td>
      <td>🌀</td>
      <td>瞬间转移至安全区域</td>
      <td>紧急规避险境，战略性撤退</td>
    </tr>
    <tr>
      <td>地形破坏</td>
      <td>💥</td>
      <td>摧毁周围墙壁障碍</td>
      <td>开辟新路径，创造战术优势</td>
    </tr>
    <tr>
      <td>时间冻结</td>
      <td>❄️</td>
      <td>暂停敌人活动</td>
      <td>争取思考时间，安全探索</td>
    </tr>
  </table>
</div>

## 🎭 游戏元素图鉴

- **探险者(我)** `🟢` — 由玩家控制的主角，寻找迷宫出口的勇者
- **幽灵敌人(鬼)** `🟣` — 具有智能追踪能力的对手，接触即告失败
- **迷宫墙壁(墙)** `⬛` — 构成迷宫的基本元素，阻碍移动的固体障碍
- **危险陷阱(危)** `🟡` — 隐藏的威胁，触发后导致游戏结束
- **终点之门(家)** `🔴` — 胜利的象征，抵达此处完成挑战

## 🛠️ 技术架构

本游戏采用现代 C++技术栈开发，核心技术包括：

- 随机迷宫生成算法
- A\*寻路算法（用于敌人追踪）
- 基于时间的游戏循环
- 面向对象的技能系统设计
- 二进制文件处理（用于排行榜）
- Windows 控制台彩色输出

## 安装和运行

### 系统要求

- Windows 操作系统
- 支持 UTF-8 字符集的控制台

### 运行方法

#### 打开MazeExplorer\x64\Release中的.exe文件 然后开始游玩。

## 🗂️ 项目结构

```
maze-explorer/
├── main.cpp                // 程序入口点
├── GameController.h/cpp    // 游戏主控制器
├── UIManager.h/cpp         // 用户界面管理
├── Enemy.h/cpp             // 敌人类定义
├── Skill.h/cpp             // 技能系统
├── MazeGenerator.h/cpp     // 迷宫生成器
├── PathFinder.h/cpp        // 寻路算法
├── Leaderboard.h/cpp       // 排行榜系统
├── EndlessMode.h/cpp       // 无尽模式
├── Menu.h/cpp              // 菜单系统
└── CommonDefs.h            // 通用定义和枚举
```

## 👩‍💻 关于开发者：你的迷宫向导 Alisa

<div align="center">
  <img src="assets/alisa_avatar.png" alt="Alisa's Avatar" width="150" style="border-radius:50%">
</div>

嗨！👋 我是 **Alisa**，一个热爱编程、痴迷游戏设计的独立开发者！

> 💭 _"代码就像迷宫，每一行都是通向创意的路径!"_

## 联系

如果你喜欢这个游戏，或者有任何建议和反馈，请别犹豫，马上联系我吧！我总是很乐意听到玩家的声音！✨

📧 **Email**: [alisa2258009564@gmail.com](mailto:alisa2258009564@gmail.com)  
💻 **GitHub**: [@2258009564](https://github.com/2258009564)

---

## 许可证

本项目采用 MIT 许可证。详情请查看 LICENSE 文件。
（有这东西吗？）

## 致谢

感谢所有为本项目提供帮助和支持的人！

---

© 2025 alisa. All rights reserved.
