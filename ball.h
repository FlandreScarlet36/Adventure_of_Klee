#ifndef BALL_H
#define BALL_H

#include <QGraphicsPixmapItem>

class Ball : public QGraphicsPixmapItem
{
public:
    explicit Ball(QObject *parent = nullptr);
    Ball(QPoint pos);

signals:

public slots:
};

#endif // BALL_H
