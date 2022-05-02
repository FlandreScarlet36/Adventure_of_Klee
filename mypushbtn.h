#ifndef MYPUSHBTN_H
#define MYPUSHBTN_H

#include <QObject>

class mypushbtn : public QObject
{
    Q_OBJECT
public:
    explicit mypushbtn(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MYPUSHBTN_H