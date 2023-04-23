#pragma once

#include "battlefieldcoords.h"
#include "cshipsatcoords.h"

#include <QObject>

#include <optional>

class CAbstractBattleField;
class CShipAtCoords;
class CComputerPlayer : public QObject
{
public:
    explicit CComputerPlayer(CAbstractBattleField* battleField, QObject* parent = nullptr);

    void init();

private:
    void doMove();
    void hit(const CShipAtCoords& s);

    BattleFieldCoords::BattleFieldCoords doMoveEasy() const;
    BattleFieldCoords::BattleFieldCoords doMoveMedium() const;
    BattleFieldCoords::BattleFieldCoords doMoveHard() const;

    BattleFieldCoords::BattleFieldCoords justSomeRandomMove() const;

    std::optional<BattleFieldCoords::BattleFieldCoords> strategicMove() const;
    std::optional<BattleFieldCoords::BattleFieldCoords> findNextHit() const;

    bool isValidMove(const CShipAtCoords& s) const;

    std::vector<BattleFieldCoords::BattleFieldCoords> getAvailableFields() const;

    CShipsAtCoords::const_iterator getMinOrMax(const bool isMin,
                                               const BattleFieldCoords::EDirections dir,
                                               const CShipsAtCoords& filtered) const;
    std::optional<BattleFieldCoords::BattleFieldCoords> appendToMinOrMax(const bool isMin,
                                                                         const BattleFieldCoords::EDirections dir,
                                                                         const CShipsAtCoords& filtered) const;

    CAbstractBattleField* _battleField;
    std::vector<unsigned int> _sunkShips = {};
    CShipsAtCoords _hits = {};
};
