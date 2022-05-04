#ifndef FISH_H
#define FISH_H

#include <QGraphicsPixmapItem>

class Fish : public QGraphicsPixmapItem
{
public:
    Fish(QPoint pos);
    int speed;
    int dir;
    void move();
    bool die;

};

#endif // FISH_H
