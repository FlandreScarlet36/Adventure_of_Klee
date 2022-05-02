#ifndef MYKLEE_H
#define MYKLEE_H

#include <QGraphicsPixmapItem>

class myklee : public QGraphicsPixmapItem
{
public:
    explicit myklee();
    float moveSpeed;
};

#endif // MYKLEE_H
