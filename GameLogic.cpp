#include "GameLogic.h"
#include <QMessageBox>
#include <QTimer>

GameLogic::GameLogic(MapManager &mapManager, QObject *parent)
    : QObject(parent), m_mapManager(mapManager) {

    connect(this, &GameLogic::gameUpdated,
            [](){ qDebug() << "GameUpdated signal emitted"; });
}
bool GameLogic::movePlayer(int dx, int dy) {
    if (m_gameOver) return false;
    QPoint pos = m_mapManager.getPlayerPosition();
    int newX = pos.x() + dx;
    int newY = pos.y() + dy;
    if (!m_mapManager.isValidPosition(newX, newY)) return false;
    CellType target = m_mapManager.getCell(newX, newY);
    if (target == Empty || target == Key) {
        if (target == Key) {
            m_hasKey = true;
            m_mapManager.setCell(newX, newY, Empty);
        }
        updatePlayerPosition(newX, newY);
        consumeStep();
        emit gameUpdated();
        return true;
    }
    if (target == Stone) {
        if (moveStone(newX, newY, dx, dy)) {
            consumeStep();
            emit gameUpdated();
            return true;
        }
        return false;
    }
    if (target == Thorn && isThornActive()) {
        consumeStep();
        emit gameUpdated();
        return true;
    }
    if (target == Box && m_hasKey) {
        emit gameWon();
        m_gameOver = true;
        emit gameUpdated();
        return true;
    }
    if (target == Door && m_hasKey) {
        m_mapManager.setCell(newX, newY, Empty);
        updatePlayerPosition(newX, newY);
        consumeStep();
        emit gameUpdated();
        return true;
    }
    return false;
}
void GameLogic::kickStone(int x, int y, int dx, int dy) {
    if (moveStone(x, y, dx, dy)) {
        consumeStep();
        emit gameUpdated();
    }
}
bool GameLogic::isThornActive() const {
    return 1;
}

bool GameLogic::checkWinCondition() const {
    return m_gameOver && m_hasKey;
}
bool GameLogic::checkLoseCondition() const {
    return m_stepsLeft <= 0;
}
void GameLogic::consumeStep() {
    if(--m_stepsLeft <= 0) {
        emit gameLost();
        m_gameOver = true;
    }
}
bool GameLogic::moveStone(int fromX, int fromY, int dx, int dy) {
    int newX = fromX + dx;
    int newY = fromY + dy;

    if(m_mapManager.isValidPosition(newX, newY) &&
        m_mapManager.getCell(newX, newY) == Empty)
    {
        m_mapManager.setCell(newX, newY, Stone);
        m_mapManager.setCell(fromX, fromY, Empty);
        return true;
    }
    return false;
}
void GameLogic::updatePlayerPosition(int x, int y) {
    QPoint oldPos = m_mapManager.getPlayerPosition();
    m_mapManager.setCell(oldPos.x(), oldPos.y(), Empty);
    m_mapManager.setCell(x, y, Player);
    m_mapManager.setPlayerPosition(x, y);
}
