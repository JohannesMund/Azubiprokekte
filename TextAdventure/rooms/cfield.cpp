#include "cfield.h"
#include "cgamemanagement.h"

CField::CField()
{
}

std::string CField::mapSymbol() const
{
    return CRoom::mapSymbol();
}

void CField::execute()
{
    CRoom::execute();

    if (_encounterPossible && !hasTask())
    {
        CGameManagement::getInstance()->executeRandomEncounter(CEncounter::eField);
    }
}