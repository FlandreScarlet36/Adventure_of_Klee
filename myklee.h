#ifndef MYKLEE_H
#define MYKLEE_H

#include <QGraphicsPixmapItem>

class myklee : public QGraphicsPixmapItem
{
public:
    explicit myklee();
    float moveSpeed;
    int upSpeed;
    bool coolDown;
    int faceto;
    int lowest;
    void jump();
};

#endif // MYKLEE_H
