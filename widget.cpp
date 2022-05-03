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
    ground.setPixmap(QPixmap("://res/ground.png"));
    option.setPixmap(QPixmap("://res/option.png"));
    ground.setPos(0,800);
    myTitle.setScale(1.7);
    myTitle.setPos(this->width()*0.5-440,30);
    haoYe.setScale(1.5);
    haoYe.setPos(0,this->height()-450);
    option.setScale(1.5);
    option.setPos(this->width()*0.5-400,300);

    myStartScene.addPixmap(QPixmap("://res/Bg.png"));
    myStartScene.addItem(&myTitle);
    myGameScene.addItem(&myBg);
    myGameScene.addItem(&ground);
    myStartScene.addItem(&haoYe);
    myGameScene.addItem(&myKlee);
    myGameScene.addItem(&option);
    myGameView.setScene(&myStartScene);//设置场景为开始场景

    this->TitleBGM.setMedia(QUrl("qrc:/res/TitleBGM.mp3"));
    this->GameBGM.setMedia(QUrl("qrc:/res/GameBGM.mp3"));
    this->KleeDC.setMedia(QUrl("qrc:/res/可莉登场.mp3"));
    this->TitleBGM.play();
    this->TitleBGM.setVolume(10);
    this->GameBGM.setVolume(20);

    MyPushBtn *startBtn=new MyPushBtn(":/res/StartBtn.png");
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.475);
    myStartScene.addWidget(startBtn);
    connect(startBtn,&MyPushBtn::clicked,[=](){
        qDebug()<<"Game Start!";
        this->TitleBGM.setVolume(5);
        this->TitleBGM.stop();
        this->GameBGM.play();
        this->KleeDC.play();
        startBtn->zoom1();
        startBtn->zoom2();
        QTimer::singleShot(500,this,[=](){
            myGameView.setScene(&myGameScene);
        });
        QTimer::singleShot(5000,this,[=](){
            myGameScene.removeItem(&option);//结束引导
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
    MyPushBtn *exitBtn2=new MyPushBtn(":/res/leave2.png");
    exitBtn2->move(10,10);
    myGameScene.addWidget(exitBtn2);
    connect(exitBtn2,&MyPushBtn::clicked,this,[=](){
        qDebug()<<"布响丸辣！";
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
    myKleeMoveTimer->start(10);
    connect(myKleeMoveTimer,&QTimer::timeout,this,[=](){
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
        kleeMove();
        if(myKlee.y()<730){
            myKlee.jump();                            //落地检测
        }

    });

    myBombTimer=new QTimer(this);
    myBombTimer->start(15);
    connect(myBombTimer,&QTimer::timeout,[this](){   //炸弹移动定时器
       for(auto bomb:myBombList)
       {
           bomb->BombMove(QPoint(bomb->dir,0));
           if(bomb->y()>=740&&bomb->upSpeed<0&&bomb->jumpable!=0){
               bomb->upSpeed=15;
               bomb->jumpable--;
           }
           if(bomb->jumpable==0){
               myBombList.removeOne(bomb);
               bomb->moveBy(-50,-70);
               bomb->setPixmap(QPixmap(":/res/boom.png"));
               QTimer::singleShot(250,this,[=](){
                   bomb->setPixmap(QPixmap(":/res/boom2.png"));
               });
               QTimer::singleShot(500,this,[=](){
                   myGameScene.removeItem(bomb); //炸弹弹三下爆炸
               });
           }
       }
    });
}

Widget::~Widget()
{
    delete ui;
}
void Widget::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_K:
    //case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
        myKeyList.append(event->key());//添加到按键组合
        break;
    case Qt::Key_J:
        if(myKlee.coolDown){
            kleeBomb();
        }
        break;
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
        case Qt::Key_K:
            if(myKlee.y()>=730){
                myKlee.upSpeed=20;
                myKlee.moveBy(0,-myKlee.moveSpeed);//弹起来吧！
            }
            break;
//        case Qt::Key_S:
//            myKlee.moveBy(0,1*myKlee.moveSpeed);break;
        case Qt::Key_A:
            myKlee.faceto=-1;
            myKlee.setPixmap(QPixmap("://res/Kleem.png"));
            myKlee.moveBy(-1*myKlee.moveSpeed,0);break;
        case Qt::Key_D:
            myKlee.faceto=1;
            myKlee.setPixmap(QPixmap("://res/Klee.png"));
            myKlee.moveBy(1*myKlee.moveSpeed,0);break;
            }
    }
}
void Widget::kleeBomb(){
    int r=qrand()%3;
    if(r==1){
        this->KleeAttack.setMedia(QUrl("qrc:/res/嘿咻.mp3"));
    }
    if(r==2){
        this->KleeAttack.setMedia(QUrl("qrc:/res/蹦蹦炸弹.mp3"));
    }
    if(r==3){
        this->KleeAttack.setMedia(QUrl("qrc:/res/弹起来吧.mp3"));
    }
    this->KleeAttack.play();
    Bomb* newBomb =new Bomb(QPoint(myKlee.x(),myKlee.y()-3));
    if(myKlee.faceto==-1){
        newBomb->setPixmap(QPixmap("://res/Bomb.png"));
    }
    if(myKlee.faceto==1){
        newBomb->setPixmap(QPixmap("://res/Bombm.png"));
    }
    newBomb->upSpeed=15;
    newBomb->jumpable=3;
    newBomb->dir=myKlee.faceto;
    myGameScene.addItem(newBomb);
    myBombList.append(newBomb);
    myKlee.coolDown=false;
    QTimer::singleShot(1300,this,[=](){
        myKlee.coolDown=true;
    });
}

