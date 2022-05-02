#ifndef MYKLEE_H
#define MYKLEE_H

#include <QObject>

class myklee : public QObject
{
    Q_OBJECT
public:
    explicit myklee(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MYKLEE_H