#include "cjunkarmor.h"
#include "cenemy.h"
#include "console.h"
#include "randomizer.h"

#include <format>
CJunkArmor::CJunkArmor() : CArmor()
{
    _levelCap = 4;
    _namesByLevel = {"Ripped T-Shirt", "White T-Shirt", "Fashionable T-Shirt", "Sweater", "Hoodie"};
    _description = "Looks like mere clothing, but should offer a little protection.";
}

void CJunkArmor::battleEffect(CEnemy* enemy)
{
    Console::printLn(std::format("You feel confident, that your armor will protect you from the furious attacks of {}",
                                 enemy->name()));
}

int CJunkArmor::shield(const unsigned int i)
{
    int shieldAmount = Randomizer::getRandom(_level + 1);
    if (shieldAmount == 0)
    {
        return i;
    }

    if (Randomizer::getRandom(100) <= _level * 10)
    {
        Console::printLn(std::format("Your armor absorbs {} damage", shieldAmount));
        return std::max(i - shieldAmount, 0U);
    }

    return i;
}