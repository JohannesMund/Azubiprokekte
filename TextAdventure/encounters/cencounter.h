#pragma once

#include <functional>
#include <string>

/**
 * @brief The CEncounter class represents an Encounter
 * Encpounters are executed randomly everytime a room is entered, when no task is available
 * @sa Ressources::Config::encounterChance
 * @remark Encounters must be registered
 * @sa EncounterRegister::encounterRegister()
 * @remark Derive from CEncounter to create a new encounter
 */

class CEncounter
{
public:
    /**
     * @brief CEncounter Constructor
     */
    CEncounter();

    /**
     * @brief ~CEncounter Destructor
     */
    virtual ~CEncounter()
    {
    }

    /**
     * @brief execute executes the task
     */
    virtual void execute();

    /**
     * @brief encounterChance implement to set the probability for the encounter to occur
     * @remark the encounterChance is relative to the encounterChance of the BattleEncounter
     * @sa Ressources::Config::fightChance
     * @return  the chance for this encounter to occur, relative to CBattleEncounter
     */
    virtual unsigned int encounterChance() const = 0;

    /**
     * @brief name Name of the encounter
     * @return a string to be displayed, when the encounter executes.
     */
    virtual std::string name() const = 0;

    /**
     * @brief nameFilter
     * @param name
     * @return a name filter function to be used in std containers
     */
    static std::function<bool(const CEncounter*)> nameFilter(const std::string& name);

protected:
    /**
     * @brief canBeExecuted
     * @return true if the encounter can be executed
     * @remark can be overwritten, basis version checks _isSingleExecution && _hasBeenExecuted
     */
    virtual bool canBeExecuted() const;

    /**
     * @brief _isSingleExecution
     * Set to true, if the encounter shall be executed only once
     */
    bool _isSingleExecution = false;

    /**
     * @brief _hasBeenExecuted
     * Set to true, after the encounter has been executed
     * @sa _isSingleExecution
     */
    bool _hasBeenExecuted = false;
};