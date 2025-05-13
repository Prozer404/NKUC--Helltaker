#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include "MapManager.h"
#include "GameLogic.h"

class GameWidget : public QWidget {
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    static const int GRID_SIZE = 40;

    MapManager m_mapManager;
    GameLogic m_gameLogic;

    void drawCell(QPainter &painter, int x, int y, const QRect &rect);
    void showGameOver(const QString &message);
private slots:
    void handleGameWon();
    void handleGameLost();
};

#endif // GAMEWIDGET_H
