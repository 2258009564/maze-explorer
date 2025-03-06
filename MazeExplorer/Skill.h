#pragma once

#include <string>
#include <memory>
#include <vector>

// 前向声明
class GameController;

// 技能基类
class Skill
{
protected:
    std::string name;        // 技能名称
    std::string description; // 技能描述
    bool available;          // 是否可用
    int cooldown;            // 冷却时间
    int currentCooldown;     // 当前剩余冷却时间

public:
    Skill(const std::string &skillName, const std::string &skillDescription, int skillCooldown);
    virtual ~Skill() = default;

    // 使用技能的纯虚函数
    virtual bool use(GameController *game) = 0;

    // 更新冷却时间
    void updateCooldown();

    // 获取技能信息
    bool isAvailable() const { return available; }
    const std::string &getName() const { return name; }
    const std::string &getDescription() const { return description; }
    int getCooldown() const { return cooldown; }
    int getCurrentCooldown() const { return currentCooldown; }
};

// 传送技能 - 随机传送到安全位置
class TeleportSkill : public Skill
{
public:
    TeleportSkill();
    bool use(GameController *game) override;
};

// 破墙技能 - 打破周围一圈墙壁
class WallBreakerSkill : public Skill
{
public:
    WallBreakerSkill();
    bool use(GameController *game) override;
};

// 冻结技能 - 让敌人停止行动五回合
class FreezeEnemiesSkill : public Skill
{
public:
    FreezeEnemiesSkill();
    bool use(GameController *game) override;
};
