#include "cstartingroom.h"
#include "cgamemanagement.h"
#include "cjunkshield.h"
#include "cjunksword.h"
#include "console.h"

#include <format>

CStartingRoom::CStartingRoom()
{
    _encounterPossible = false;
    _taskPossible = false;
}

void CStartingRoom::execute()
{
    if (seen())
    {
        CRoom::execute();
        Console::printLn("You can still see, where you woke up, when you started your adventure,");
        return;
    }

    auto sword = new CJunkSword();

    Console::br();
    Console::printLn("You whake up, somewhere.");
    Console::printLn("You have not the slightest idea, where you are.");
    Console::printLn("You look around, and realize, that you are utterly defenseless. You need something to defend "
                     "yourself. Hidden beneath one of the bushes, you see someting:");
    Console::printLn(sword->description());
    Console::printLn("This seems to be a decent weapom, at least for now.");
    Console::br();
    char input;
    do
    {
        Console::printLn("[T]ake it [L]eave it");
        input = Console::getAcceptableInput("tl");
        if (input == 't')
        {
            Console::br();
            Console::printLn(std::format("You take the {} and equip it. It looks good on you.", sword->name()));
            CGameManagement::getInventoryInstance()->addItem(sword);
        }
        else
        {
            Console::br();
            Console::printLn("Your parents always taught you, not to pick up stuff from the ground. Who knows wo owns "
                             "this sword. You leave the Sword where it is and turn around.");
            Console::printLn(
                "Than you start thinking. You are still defenseless. Maybe you should re-think your decision.");
        }
    } while (input != 't');

    auto shield = new CJunkShield();

    Console::br();
    Console::printLn("Having the sword, you look further. You still do not feel like a big, sturdy warrior. "
                     "Something is missing.");
    Console::printLn("Wait, is that...?");
    Console::printLn(shield->description());

    do
    {
        Console::br();
        Console::printLn("[T]ake it [L]eave it");
        input = Console::getAcceptableInput("tl");
        if (input == 't')
        {
            Console::br();
            Console::printLn(std::format("You take the {} and equip it. Now you feel complete.", shield->name()));
            CGameManagement::getInventoryInstance()->addItem(shield);
        }
        else
        {
            Console::br();
            Console::printLn("Ok, by now, you should have realized, that you will not leave without the shield. Let's "
                             "shorten this, ok?");
        }
    } while (input != 't');

    Console::br();
    Console::printLn(
        "Now, that you are equipped, it is time to start your adventure. You look around where you are and find:");
    Console::br();

    CRoom::execute();

    _encounterPossible = true;
    _taskPossible = true;
}

std::string CStartingRoom::mapSymbol()
{
    return "*";
}