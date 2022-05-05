#include "shadow.h"

shadow::shadow()
{
    this->setPixmap(QPixmap("://res/shadow.png"));
}
shadow::shadow(QPoint pos){
    this->setPixmap(QPixmap("://res/shadow.png"));
    this->setPos(pos);
}
