#ifndef SHADOW_H
#define SHADOW_H

#include <QGraphicsPixmapItem>

class shadow : public QGraphicsPixmapItem
{
public:
    explicit shadow();
    shadow(QPoint pos);

};

#endif // SHADOW_H
