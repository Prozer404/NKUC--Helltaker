#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "MapManager.h"
#include <QObject>

class GameLogic : public QObject {
    Q_OBJECT
public:
    explicit GameLogic(MapManager &mapManager, QObject *parent = nullptr);
    bool movePlayer(int dx, int dy);
    void kickStone(int x, int y, int dx, int dy);
    bool isThornActive() const;
    bool checkWinCondition() const;
    bool checkLoseCondition() const;
    int remainingSteps() const { return m_stepsLeft; }
    bool hasKey() const { return m_hasKey; }
signals:
    void gameUpdated();
    void gameWon();
    void gameLost();
private:
    MapManager &m_mapManager;
    int m_stepsLeft = 30;
    bool m_hasKey = false;
    bool m_gameOver = false;
    void consumeStep();
    bool moveStone(int fromX, int fromY, int dx, int dy);
    void updatePlayerPosition(int x, int y);
    void cleanPosition();
};
#endif // GAMELOGIC_H
