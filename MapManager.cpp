#include "MapManager.h"

MapManager::MapManager() {
    initializeLevel();
}
void MapManager::initializeLevel() {
    m_map = {
        {Wall,  Wall,   Wall,   Wall,   Wall, Wall, Empty, Empty},
        {Wall,  Empty,  Stone,  Empty,  Wall, Wall, Wall, Wall},
        {Wall,  Thorn,  Empty, Player,  Door, Empty, Box, Wall},
        {Wall,  Key,    Empty,  Empty,  Wall, Wall, Wall, Wall},
        {Wall,  Wall,   Wall,   Wall,   Wall, Empty, Empty, Empty}
    };
    for(int y=0; y<m_map.size(); y++) {
        for(int x=0; x<m_map[y].size(); x++) {
            if(m_map[y][x] == Player) {
                m_playerPos = QPoint(x, y);
            }
        }
    }
}
CellType MapManager::getCell(int x, int y) const {
    if(y >=0 && y < m_map.size() && x >=0 && x < m_map[y].size())
        return m_map[y][x];
    return Wall;
}
CellType MapManager::getCell(QPoint pos) const {
    return getCell(pos.x(), pos.y());
}
void MapManager::setCell(int x, int y, CellType type) {
    if(y >=0 && y < m_map.size() && x >=0 && x < m_map[y].size())
        m_map[y][x] = type;
}
QPoint MapManager::getPlayerPosition() const {
    return m_playerPos;
}
int MapManager::getMapWidth() const {
    return !m_map.isEmpty() ? m_map[0].size() : 0;
}
int MapManager::getMapHeight() const {
    return m_map.size();
}
bool MapManager::isValidPosition(int x, int y) const {
    return y >=0 && y < m_map.size() &&
           x >=0 && x < m_map[y].size();
}
void MapManager::setPlayerPosition(int x, int y) {
    if(isValidPosition(x, y)) {
        m_playerPos = QPoint(x, y);
    }
}
