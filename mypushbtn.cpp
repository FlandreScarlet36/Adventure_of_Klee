#include "mypushbtn.h"
#include <qdebug.h>
#include <QPropertyAnimation>
MyPushBtn::MyPushBtn(QString normal,QString press)
{
    this->normalPath=normal;
    this->pressPath=press;
    QPixmap pix;
    bool flag=pix.load(normal);
    if(!flag){
        qDebug()<<"Load Failed";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    //this->setStyleSheet("QpushButton{border:0px}");

    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->setFlat(true);

}
void MyPushBtn::mousePressEvent(QMouseEvent *e){
    if(this->pressPath != ""){
        QPixmap pix;
        bool flag=pix.load(this->pressPath);
        if(!flag){
            qDebug()<<"Load Failed";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QpushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);
}
void MyPushBtn::mouseReleaseEvent(QMouseEvent *e){
    if(this->pressPath != ""){
        QPixmap pix;
        bool flag=pix.load(this->normalPath);
        if(!flag){
            qDebug()<<"Load Failed";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());

        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //this->setStyleSheet("QpushButton{border:0px}");
        //this->setStyleSheet("background-color:rgba(0,0,0,0)");
        this->setFlat(true);
        this->setStyleSheet("QPushButton{border:none;background:transparent;}");
    }
    return QPushButton::mouseReleaseEvent(e);
}

void MyPushBtn::zoom1(){
    QPropertyAnimation*animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(400);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+15,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushBtn::zoom2(){
    QPropertyAnimation*animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(400);
    animation->setStartValue(QRect(this->x(),this->y()+15,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
