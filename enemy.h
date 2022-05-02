#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>

class enemy : public QObject
{
    Q_OBJECT
public:
    explicit enemy(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ENEMY_H