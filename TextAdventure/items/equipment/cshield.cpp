#include "cshield.h"

CShield::CShield() : CEquipment()
{
    _hasBattleEffect = true;
    _hasShieldingAction = true;
}

std::function<bool(const CItem*)> CShield::shieldFilter()
{
    return [](const CItem* item) -> bool { return dynamic_cast<const CShield*>(item) != nullptr; };
}
