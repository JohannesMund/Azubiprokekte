#pragma once

#include "cbattle.h"

#include <optional>
#include <string>

class CEnemy
{
public:
    CEnemy();

    virtual ~CEnemy()
    {
    }

    virtual void preBattle();

    virtual void preBattleAction();
    virtual void battleAction(bool& endRound);
    virtual void postBattleAction();

    virtual void postBattle();

    virtual void spoilsOfWar();

    std::string name() const;
    std::string weapon() const;
    unsigned int level() const;

    unsigned int initiative() const;

    bool isDead() const;
    bool hasExtendedWeaponChoice() const;

    void addHp(const int i);
    void dealDamage(const int i);
    unsigned int hp() const;

    std::optional<CBattle::EWeapons> peek();

protected:
    unsigned int _level;
    unsigned int _hp;
    unsigned int _initiative;

    bool _extendedWeaponChoice = false;

    std::string _name;
    std::string _weapon;

    static unsigned int basicXP(const unsigned int level);

private:
    std::optional<CBattle::EWeapons> _battleDecision;
};