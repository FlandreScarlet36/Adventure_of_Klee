#ifndef BOMB_H
#define BOMB_H

#include <QGraphicsPixmapItem>

class Bomb : public QGraphicsPixmapItem
{
public:
    explicit Bomb(QObject *parent = nullptr);
    Bomb(QPoint pos);
    int speed;
    int upSpeed;
    int jumpable = 3;
    void BombMove(QPoint dir=QPoint(1,0));
};

#endif // BOMB_H
