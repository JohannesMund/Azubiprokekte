#pragma once

#include "cencounter.h"

class CMysteriousChest : public CEncounter
{
public:
    CMysteriousChest();

    virtual void execute() override;
    virtual unsigned int encounterChance() const override;
    virtual std::string name() const override;
};