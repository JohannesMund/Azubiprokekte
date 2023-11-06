#include "cjunksword.h"
#include "cenemy.h"
#include "console.h"

#include <format>
#include <string>

CJunkSword::CJunkSword() : CSword()
{
    _levelCap = 4;
    _namesByLevel = {
        "Stick, shaped like a sword", "Sword, shaped like a stick", "Wooden Sword", "Training Sword", "Sword"};
    _description = "A stick, shaped like a sword. Or a sword, shaped like a stick? It is a sword-stick";
}

void CJunkSword::battleEffect(CEnemy* enemy)
{
    if (_level < 1)
    {
        Console::printLn(std::format(
            "You draw your sword at {} and try to look dangerous. The sword is not helpful at all.", enemy->name()));
    }
}

void CJunkSword::battleBuff(CEnemy* enemy, bool& endRound)
{
    if (doesEquipmentEffectFire())
    {
        Console::printLn("Your shield protects you from the enemy attack");
        enemy->dealDamage(1);
        endRound = true;
    }
}
