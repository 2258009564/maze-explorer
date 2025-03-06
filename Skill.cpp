#include "Skill.h"
#include "GameController.h"
#include <cstdlib>

// 基础技能实现
Skill::Skill(const std::string &skillName, const std::string &skillDescription, int skillCooldown)
    : name(skillName), description(skillDescription), available(true), cooldown(skillCooldown), currentCooldown(0)
{
}

void Skill::updateCooldown()
{
    if (!available && currentCooldown > 0)
    {
        currentCooldown--;
        if (currentCooldown <= 0)
        {
            available = true;
            currentCooldown = 0;
        }
    }
}

// 传送技能实现
TeleportSkill::TeleportSkill()
    : Skill("传送", "随机传送到一个安全位置", 10)
{
}

bool TeleportSkill::use(GameController *game)
{
    if (!available)
        return false;

    // 传送逻辑 - 由GameController实现
    bool success = game->teleportPlayerToSafeLocation();

    if (success)
    {
        available = false;
        currentCooldown = cooldown;
    }

    return success;
}

// 破墙技能实现
WallBreakerSkill::WallBreakerSkill()
    : Skill("墙破", "打破周围一圈墙壁", 15)
{
}

bool WallBreakerSkill::use(GameController *game)
{
    if (!available)
        return false;

    // 破墙逻辑 - 由GameController实现
    bool success = game->breakWallsAroundPlayer();

    if (success)
    {
        available = false;
        currentCooldown = cooldown;
    }

    return success;
}

// 冻结敌人技能实现
FreezeEnemiesSkill::FreezeEnemiesSkill()
    : Skill("冻结", "让敌人停止行动五回合", 20)
{
}

bool FreezeEnemiesSkill::use(GameController *game)
{
    if (!available)
        return false;

    // 冻结逻辑 - 由GameController实现
    bool success = game->freezeAllEnemies(5);

    if (success)
    {
        available = false;
        currentCooldown = cooldown;
    }

    return success;
}