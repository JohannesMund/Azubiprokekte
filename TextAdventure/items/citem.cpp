#include "citem.h"
#include "cenhancableitem.h"
#include "console.h"

#include <format>

using namespace std;

CItem::CItem()
{
}

void CItem::view()
{
    Console::printLn(format("You decide to take a look at: {}", _name));
    Console::printLn(_description);
    Console::hr();
}

bool CItem::isUsableFromInventory() const
{
    return _isUsableFromInventory;
}

bool CItem::isUsableFromBattle() const
{
    return _isUsableFromBattle;
}

bool CItem::hasDeathEffect() const
{
    return _hasDeathEffect;
}

bool CItem::hasBattleEffect() const
{
    return _hasBattleEffect;
}

bool CItem::hasDurableBattleEffect() const
{
    return _hasDurableBattleEffect;
}

bool CItem::hasShieldingAction() const
{
    return _hasShieldingAction;
}

bool CItem::isConsumable() const
{
    return _isConsumable;
}

std::function<bool(const CItem*)> CItem::nameFilter(const std::string& name)
{
    return [&name](const CItem* item) { return item->name().compare(name) == 0; };
}

std::function<bool(const CItem*)> CItem::battleEffectFilter()
{
    return [](const CItem* item) { return item->hasBattleEffect(); };
}

std::function<bool(const CItem*)> CItem::durableBattleEffectFilter()
{
    return [](const CItem* item) { return item->hasDurableBattleEffect(); };
}

std::function<bool(const CItem*)> CItem::shieldingActionFilter()
{
    return [](const CItem* item) { return item->hasShieldingAction(); };
}

std::function<bool(const CItem*)> CItem::deathEffectFilter()
{
    return [](const CItem* item) { return item->hasDeathEffect(); };
}

string CItem::name() const
{
    return _name;
}

string CItem::description() const
{
    return _description;
}

bool CItem::isSellable() const
{
    return _isSellable;
}

unsigned int CItem::value() const
{
    return _value;
}
