#ifndef COMPUTERENEMY_TEST_H
#define COMPUTERENEMY_TEST_H

#include <QObject>
#include <QTest>

#include "computerenemy.h"
#include "playermanagement.h"
#include "playfield.h"
#include "testdefines.h"

class ComputerEnemy_Test : public QObject
{
    Q_OBJECT

private:
    void checkMoveIsValid(const PlayField& playfield, const PlayFieldCoords& coords)
    {
        QVERIFY(coords.isValid());
        QVERIFY(playfield.at(coords) == PlayerManagement::Player::none);
    }

    void doTheMove(const ComputerEnemy& c)
    {
        QFETCH(PlayFieldRepresentation, fieldRep);
        const auto field = populatePlayField(fieldRep);

        auto move = c.doMove(field);
        checkMoveIsValid(field, move);

        QFETCH(PlayFieldCoords, expected);

        if (expected.isValid())
        {
            QCOMPARE(expected, move);
        }
    }

    void makeColumns()
    {
        QTest::addColumn<PlayFieldRepresentation>("fieldRep");
        QTest::addColumn<PlayFieldCoords>("expected");
    }

    void easyData()
    {
        QTest::newRow("Test1") << PlayFieldRepresentation({{{0, 0}, PlayerManagement::Player::plX}})
                               << PlayFieldCoords();
        QTest::newRow("Test2") << PlayFieldRepresentation({{{0, 0}, PlayerManagement::Player::plX},
                                                           {{1, 0}, PlayerManagement::Player::plO}})
                               << PlayFieldCoords();

        QTest::newRow("Test3") << PlayFieldRepresentation({{{0, 0}, PlayerManagement::Player::plX},
                                                           {{1, 0}, PlayerManagement::Player::plO},
                                                           {{0, 1}, PlayerManagement::Player::plX}})
                               << PlayFieldCoords();
    }

    void mediumData()
    {

        QTest::newRow("Test4") << PlayFieldRepresentation({
                                      {{0, 0}, PlayerManagement::Player::plX},
                                      {{1, 0}, PlayerManagement::Player::plX},
                                      {{0, 1}, PlayerManagement::Player::plO},
                                      {{0, 2}, PlayerManagement::Player::plO},
                                  })
                               << PlayFieldCoords(2, 0);

        QTest::newRow("Test5") << PlayFieldRepresentation({
                                      {{0, 0}, PlayerManagement::Player::plX},
                                      {{1, 1}, PlayerManagement::Player::plX},
                                      {{0, 1}, PlayerManagement::Player::plO},
                                      {{0, 2}, PlayerManagement::Player::plO},
                                  })
                               << PlayFieldCoords(2, 2);

        QTest::newRow("Test6") << PlayFieldRepresentation({
                                      {{0, 2}, PlayerManagement::Player::plX},
                                      {{1, 2}, PlayerManagement::Player::plX},
                                      {{0, 1}, PlayerManagement::Player::plO},
                                      {{1, 1}, PlayerManagement::Player::plO},
                                  })
                               << PlayFieldCoords(2, 2);

        QTest::newRow("Test7") << PlayFieldRepresentation({
                                      {{0, 0}, PlayerManagement::Player::plX},
                                      {{0, 1}, PlayerManagement::Player::plX},
                                      {{1, 0}, PlayerManagement::Player::plO},
                                      {{1, 1}, PlayerManagement::Player::plO},
                                  })
                               << PlayFieldCoords(0, 2);
    }

    void hardData()
    {
        QTest::newRow("Test8") << PlayFieldRepresentation({
                                      {{0, 0}, PlayerManagement::Player::plO},
                                      {{1, 1}, PlayerManagement::Player::plO},
                                  })
                               << PlayFieldCoords(2, 2);

        QTest::newRow("Test9") << PlayFieldRepresentation({
                                      {{1, 0}, PlayerManagement::Player::plX},
                                      {{0, 1}, PlayerManagement::Player::plX},
                                      {{2, 2}, PlayerManagement::Player::plO},
                                      {{1, 1}, PlayerManagement::Player::plO},
                                  })
                               << PlayFieldCoords(0, 0);
        QTest::newRow("Test10") << PlayFieldRepresentation({
                                       {{1, 0}, PlayerManagement::Player::plX},
                                       {{0, 1}, PlayerManagement::Player::plX},
                                       {{0, 2}, PlayerManagement::Player::plO},
                                       {{2, 2}, PlayerManagement::Player::plO},
                                   })
                                << PlayFieldCoords(1, 2);
    }

    void insaneData()
    {
        QTest::newRow("Test11") << PlayFieldRepresentation() << PlayFieldCoords(0, 0);
        QTest::newRow("Test12") << PlayFieldRepresentation({
                                       {{0, 0}, PlayerManagement::Player::plO},
                                   })
                                << PlayFieldCoords(1, 1);
        QTest::newRow("Test13") << PlayFieldRepresentation({
                                       {{0, 2}, PlayerManagement::Player::plO},
                                   })
                                << PlayFieldCoords(1, 1);
        QTest::newRow("Test14") << PlayFieldRepresentation({
                                       {{2, 0}, PlayerManagement::Player::plO},
                                   })
                                << PlayFieldCoords(1, 1);
        QTest::newRow("Test15") << PlayFieldRepresentation({
                                       {{2, 2}, PlayerManagement::Player::plO},
                                   })
                                << PlayFieldCoords(1, 1);
        QTest::newRow("Test16") << PlayFieldRepresentation({
                                       {{0, 1}, PlayerManagement::Player::plO},
                                   })
                                << PlayFieldCoords(1, 1);
        QTest::newRow("Test17") << PlayFieldRepresentation({
                                       {{2, 1}, PlayerManagement::Player::plO},
                                   })
                                << PlayFieldCoords(1, 1);
        QTest::newRow("Test18") << PlayFieldRepresentation({
                                       {{1, 0}, PlayerManagement::Player::plO},
                                   })
                                << PlayFieldCoords(1, 1);
        QTest::newRow("Test19") << PlayFieldRepresentation({
                                       {{1, 2}, PlayerManagement::Player::plO},
                                   })
                                << PlayFieldCoords(1, 1);
    }

private slots:
    void test_doMove_easy_data()
    {
        makeColumns();
        easyData();
    }

    void test_doMove_easy()
    {
        ComputerEnemy c;
        c.setDifficulty(ComputerEnemy::Difficulty::easy);
        doTheMove(c);
    }

    void test_doMove_medium_data()
    {
        makeColumns();
        easyData();
        mediumData();
    }

    void test_doMove_medium()
    {
        ComputerEnemy c;
        c.setDifficulty(ComputerEnemy::Difficulty::medium);
        doTheMove(c);
    }

    void test_doMove_hard_data()
    {
        makeColumns();
        easyData();
        mediumData();
        hardData();
    }

    void test_doMove_hard()
    {
        ComputerEnemy c;
        c.setDifficulty(ComputerEnemy::Difficulty::hard);
        doTheMove(c);
    }

    void test_doMove_insane_data()
    {
        makeColumns();
        easyData();
        mediumData();
        hardData();
        insaneData();
    }

    void test_doMove_insane()
    {
        ComputerEnemy c;
        c.setDifficulty(ComputerEnemy::Difficulty::insane);
        doTheMove(c);
    }
};

#endif // COMPUTERENEMY_TEST_H
