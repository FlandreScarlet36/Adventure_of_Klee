#include "myklee.h"

myklee::myklee()
{

    this->setPixmap(QPixmap("://res/Klee.png"));
    this->setPos(300,730);
    moveSpeed=6;
    faceto=1;
}
void myklee::jump(){
    this->moveBy(0,-upSpeed);
    upSpeed--;
}
