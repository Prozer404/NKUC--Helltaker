#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <QPoint>
#include <QVector>

enum CellType {
    Empty,
    Wall,
    Player,
    Stone,
    Key,
    Box,
    Door,
    Thorn
};
class MapManager {
public:
    MapManager();
    void initializeLevel();
    CellType getCell(int x, int y) const;
    CellType getCell(QPoint pos) const;
    void setCell(int x, int y, CellType type);
    QPoint getPlayerPosition() const;
    int getMapWidth() const;
    int getMapHeight() const;
    bool isValidPosition(int x, int y) const;
    void setPlayerPosition(int x, int y);
private:
    QVector<QVector<CellType>> m_map;
    QPoint m_playerPos;
};

#endif // MAPMANAGER_H
