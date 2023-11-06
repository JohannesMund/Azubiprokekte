#include "cjunkitem.h"
#include "randomizer.h"
#include "ressources.h"

CJunkItem::CJunkItem() : CItem()
{
    auto it = Ressources::Items::getRandomRubbishItems();
    _name = it.first;
    _description = it.second;

    _isSellable = true;
    _value = Randomizer::getRandom(10) + 5;
}

std::function<bool(const CItem*)> CJunkItem::junkItemFilter()
{
    return [](const CItem* item) -> bool { return dynamic_cast<const CJunkItem*>(item) != nullptr; };
}