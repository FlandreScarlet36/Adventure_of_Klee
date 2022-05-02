#ifndef MYPUSHBTN_H
#define MYPUSHBTN_H

#include <QPushButton>
#include <QString>
class MyPushBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushBtn(QWidget *parent = nullptr);
    MyPushBtn(QString normal,QString press="");
    void zoom1();
    void zoom2();
    QString normalPath;
    QString pressPath;
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYPUSHBTN_H
