#include "ctown.h"
#include "cgamemanagement.h"
#include "console.h"
#include "ressources.h"

#include <format>

CTown::CTown()
{
    auto town = Ressources::Rooms::getRandomTown();
    _name = town.first;
    _description = town.second;

    _shop.setCityName(_name);
    _church.setCityName(_name);
}

void CTown::execute()
{
    char input;
    do
    {
        Console::printLn(_name, Console::EAlignment::eCenter);
        Console::br();
        CRoom::execute();
        Console::hr();

        std::string navs = "[B]lacksmith [C]hurch [T]avern [S]hop";
        std::string acceptableInputs = "bcts";
        if (CGameManagement::getCompanionInstance()->hasCompanion())
        {
            navs.append(" [F]arm");
            acceptableInputs.append("f");
        }

        Console::printLnWithSpacer(navs, "E[x]it");
        acceptableInputs.append("x");

        input = Console::getAcceptableInput(acceptableInputs);
        if (input == 'b')
        {
            _blackSmith.execute();
        }
        if (input == 'c')
        {
            _church.execute();
        }
        if (input == 's')
        {
            _shop.execute();
        }
        if (input == 't')
        {
            tavern();
        }
        if (input == 'f')
        {
            farm();
        }
    } while (input != 'x');
}

char CTown::mapSymbol()
{
    return 'T';
}

void CTown::tavern()
{
    Console::printLn("To be opened soon");
}

void CTown::farm()
{
    Console::printLn("To be opened soon");
}
