#include "ball.h"

Ball::Ball(){
    speed=10;
    upSpeed=10;
}
void Ball::BallMove()
{
    this->moveBy(dir*speed,0);
        this->moveBy(0,-upSpeed);
        upSpeed--;
}
