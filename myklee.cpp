#include "myklee.h"

myklee::myklee()
{

    this->setPixmap(QPixmap("://res/Klee.png"));
    this->setPos(545,730);
    moveSpeed=6;
    faceto=1;
    coolDown=true;
    kleeshadow.setY(823);
}
void myklee::jump(){
    this->moveBy(0,-upSpeed);
    upSpeed--;
}
