#include "bomb.h"
#include <QTimer>

Bomb::Bomb(QObject *parent)
{

}
Bomb::Bomb(QPoint pos){
    speed=6;
    upSpeed=10;
    this->setPos(pos);
    this->setPixmap(QPixmap("://res/Bomb.png"));
}
void Bomb::BombMove(QPoint dir)
{
    this->moveBy(dir.x()*speed,dir.y()*speed);
        this->moveBy(0,-upSpeed);
        upSpeed--;
}

