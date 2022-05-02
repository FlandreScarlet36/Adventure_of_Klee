#ifndef BOMB_H
#define BOMB_H

#include <QObject>

class bomb : public QObject
{
    Q_OBJECT
public:
    explicit bomb(QObject *parent = nullptr);

signals:

public slots:
};

#endif // BOMB_H