#include "GameWidget.h"
#include <QPainter>
#include <QMessageBox>
GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent), m_gameLogic(m_mapManager, this)
{
    setFixedSize(600, 400);
    setFocusPolicy(Qt::StrongFocus);
    connect(&m_gameLogic, &GameLogic::gameUpdated,
            this, static_cast<void (QWidget::*)()>(&QWidget::update));
    connect(&m_gameLogic, &GameLogic::gameWon, this, &GameWidget::handleGameWon);
    connect(&m_gameLogic, &GameLogic::gameLost, this, &GameWidget::handleGameLost);
}

void GameWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);
    const int gridSize = GRID_SIZE;
    for(int y = 0; y < m_mapManager.getMapHeight(); y++) {
        for(int x = 0; x < m_mapManager.getMapWidth(); x++) {
            QRect cellRect(x * gridSize, y * gridSize, gridSize, gridSize);
            drawCell(painter, x, y, cellRect);
        }
    }
    painter.setFont(QFont("Arial", 14));
    painter.drawText(QRect(10, height() - 30, 200, 30),
                     QString("剩余步数: %1").arg(m_gameLogic.remainingSteps()));
}
void GameWidget::drawCell(QPainter &painter, int x, int y, const QRect &rect) {
    CellType type = m_mapManager.getCell(x, y);
    painter.save();
    painter.setPen(Qt::black);
    painter.setBrush(type == Wall ? Qt::darkGray : Qt::white);
    painter.drawRect(rect);
    QString text;
    switch(type) {
    case Player: text = "人"; break;
    case Stone:  text = "石"; break;
    case Key:    text = "钥"; break;
    case Box:    text = "箱"; break;
    case Door:   text = "门"; break;
    case Thorn:  text = m_gameLogic.isThornActive() ? "刺" : ""; break;
    default: break;
    }
    painter.drawText(rect, Qt::AlignCenter, text);
    painter.restore();
}
void GameWidget::keyPressEvent(QKeyEvent *event) {
    QPoint pos = m_mapManager.getPlayerPosition();
    int dx = 0, dy = 0;
    switch (event->key()) {
    case Qt::Key_Up:    dy = -1; break;
    case Qt::Key_Down:  dy = 1;  break;
    case Qt::Key_Left:  dx = -1; break;
    case Qt::Key_Right: dx = 1;  break;
    default: QWidget::keyPressEvent(event); return;
    }
    bool moved = m_gameLogic.movePlayer(dx, dy);
    if (!moved) {
        int targetX = pos.x() + dx;
        int targetY = pos.y() + dy;
        if (m_mapManager.getCell(targetX, targetY) == Stone) {
            m_gameLogic.kickStone(targetX, targetY, dx, dy);
        }
    }
    event->accept();
}
void GameWidget::handleGameWon() {
    showGameOver("win!");
}

void GameWidget::handleGameLost() {
    showGameOver("lose!");
}

void GameWidget::showGameOver(const QString &message) {
    QMessageBox::information(this, "Game Over!", message);
    close();
}
