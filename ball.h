#ifndef BALL_H
#define BALL_H

#include <QGraphicsPixmapItem>

class Ball : public QGraphicsPixmapItem
{
public:
    Ball();
    void BallMove();
    int speed;
    int upSpeed;
    int dir;

};

#endif // BALL_H
