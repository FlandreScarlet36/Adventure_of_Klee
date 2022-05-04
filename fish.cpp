#include "fish.h"

Fish::Fish(QPoint pos)
{

    this->setPixmap(QPixmap("://res/fish.png"));
    this->speed=qrand()%4+3;
    this->setPos(pos);
    die=false;
}
void Fish::move(){
    this->moveBy(speed,0);
}
