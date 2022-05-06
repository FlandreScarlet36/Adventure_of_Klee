#ifndef MYKLEE_H
#define MYKLEE_H

#include <QGraphicsPixmapItem>
#include <shadow.h>

class myklee : public QGraphicsPixmapItem
{
public:
    explicit myklee();
    int moveSpeed;
    int upSpeed;
    bool coolDown;
    int faceto;
    int lowest;
    shadow kleeshadow;
    void jump();
};

#endif // MYKLEE_H
