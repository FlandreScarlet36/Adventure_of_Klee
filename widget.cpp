#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <QTimer>
#include <QPushButton>
#include <mypushbtn.h>
#include <QDebug>
#include <bomb.h>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(1412,1000);
    this->setWindowIcon(QPixmap(":/res/ICON.jpg"));
    this->setWindowTitle("KleeWar");
    myGameView.setSceneRect(QRect(0,0,1412,1000));
    myGameScene.setSceneRect(QRect(0,0,1412,1000));
    myStartScene.setSceneRect(QRect(0,0,1412,1000));

    myBg.setPixmap(QPixmap("://res/Bg2.png"));
    myTitle.setPixmap(QPixmap("://res/Title.png"));
    haoYe.setPixmap(QPixmap("://res/好耶.png"));
    myTitle.setScale(1.7);
    myTitle.setPos(this->width()*0.5-440,30);
    haoYe.setScale(1.5);
    haoYe.setPos(0,this->height()-450);

    myStartScene.addPixmap(QPixmap("://res/Bg.png"));
    myStartScene.addItem(&myTitle);
    myGameScene.addItem(&myBg);
    myStartScene.addItem(&haoYe);
    myGameScene.addItem(&myKlee);
    myGameView.setScene(&myStartScene);//设置场景为开始场景

    MyPushBtn *startBtn=new MyPushBtn(":/res/StartBtn.png");
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.475);
    myStartScene.addWidget(startBtn);
    connect(startBtn,&MyPushBtn::clicked,[=](){
        qDebug()<<"Game Start!";
        startBtn->zoom1();
        startBtn->zoom2();
        QTimer::singleShot(500,this,[=](){
            myGameView.setScene(&myGameScene);
        });
    });
    //开始按钮
    MyPushBtn *exitBtn=new MyPushBtn(":/res/Camp.png");
    myStartScene.addWidget(exitBtn);
    exitBtn->move(this->width()*0.8,this->height()*0.5);
    connect(exitBtn,&MyPushBtn::clicked,[=](){
        qDebug()<<"Game Start!";
        exitBtn->zoom1();
        exitBtn->zoom2();
        QTimer::singleShot(500,this,[=](){
            this->close();
        });
    });
    //退出按钮
    MyPushBtn *exitBtn2=new MyPushBtn(":/res/Camp.png");
    exitBtn2->move(this->width()*0.8,this->height()*0.5);
    myGameScene.addWidget(exitBtn2);
    connect(exitBtn2,&MyPushBtn::clicked,[=](){
        qDebug()<<"Game Start!";
        exitBtn2->zoom1();
        exitBtn2->zoom2();
        QTimer::singleShot(500,this,[=](){
            this->close();
        });
    });

    myGameView.setParent(this);
    myGameView.show();
    //检测移动定时器
    myKleeMoveTimer = new QTimer(this);
    myKleeMoveTimer->start(5);
    connect(myKleeMoveTimer,&QTimer::timeout,this,&Widget::kleeMove);

    myBombTimer=new QTimer(this);
    myBombTimer->start(10);
    connect(myBombTimer,&QTimer::timeout,[this](){
       for(auto bomb:myBombList)
       {
           bomb->BombMove();
       }
    });
}

Widget::~Widget()
{
    delete ui;
}
void Widget::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
        myKeyList.append(event->key());//添加到按键组合
        break;
    case Qt::Key_E:
        kleeBomb();
        break;
    }
    if(myKlee.x()<0){
        myKlee.setX(0);
    }
    if(myKlee.x()>this->width()-myKlee.pixmap().width()){
        myKlee.setX(this->width()-myKlee.pixmap().width());
    }
    if(myKlee.y()<0){
        myKlee.setY(0);
    }
    if(myKlee.y()>this->height()-myKlee.pixmap().height()){
        myKlee.setY(this->height()-myKlee.pixmap().height());
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event){

    //移除按键组合
    if(myKeyList.contains(event->key())){
        myKeyList.removeOne(event->key());
    }
}
void Widget::kleeMove(){
    for(int keyCode:myKeyList){
        switch (keyCode) {
        case Qt::Key_W:
            myKlee.moveBy(0,-1*myKlee.moveSpeed);break;
        case Qt::Key_S:
            myKlee.moveBy(0,1*myKlee.moveSpeed);break;
        case Qt::Key_A:
            myKlee.moveBy(-1*myKlee.moveSpeed,0);break;
        case Qt::Key_D:
            myKlee.moveBy(1*myKlee.moveSpeed,0);break;

        }
    }
}
void Widget::kleeBomb(){
    Bomb* newBomb =new Bomb(QPoint(myKlee.x(),myKlee.y()));
    myGameScene.addItem(newBomb);
    myBombList.append(newBomb);
}


