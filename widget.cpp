#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>
#include <QTimer>
#include <QPushButton>
#include <mypushbtn.h>
#include <QDebug>
#include <bomb.h>
#include <fish.h>
#include <effe.h>
#include <QMediaPlaylist>
#include <QMediaPlayer>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(1412,1000);
    this->setWindowIcon(QPixmap(":/res/ICON.jpg"));
    this->setWindowTitle("假日冒险？出发！");
    myGameView.setSceneRect(QRect(0,0,1412,1000));
    myGameScene.setSceneRect(QRect(0,0,1412,1000));
    myStartScene.setSceneRect(QRect(0,0,1412,1000));
    left=0;
    right=1412;

    myBg.setPixmap(QPixmap("://res/Bg2.png"));
    myTitle.setPixmap(QPixmap("://res/Title.png"));
    haoYe.setPixmap(QPixmap("://res/好耶.png"));
    ground.setPixmap(QPixmap("://res/ground.png"));
    ground2.setPixmap(QPixmap("://res/ground2.png"));
    option.setPixmap(QPixmap("://res/option.png"));
    option2.setPixmap(QPixmap("://res/option2.png"));
    lake.setPixmap(QPixmap("://res/lake.png"));
    myBall.setPixmap(QPixmap("://res/ball.png"));
    myKaeya.setPixmap(QPixmap("://res/kaeya.png"));
    ground.setPos(0,800);
    ground2.setPos(0,1000-320);
    lake.setPos(0,800);
    myTitle.setScale(1.7);
    myTitle.setPos(this->width()*0.5-440,30);
    haoYe.setScale(1.5);
    haoYe.setPos(0,this->height()-450);
    option.setScale(1.5);
    option.setPos(this->width()*0.5-300,200);
    option2.setScale(1.5);
    option2.setPos(this->width()*0.5-300,200);

    myStartScene.addPixmap(QPixmap("://res/Bg.png"));
    myBallScene.addPixmap(QPixmap("://res/Bg2.png"));
    myBallScene.addItem(&ground2);
    myStartScene.addItem(&myTitle);
    myGameScene.addItem(&myBg);
    myGameScene.addItem(&ground);
    myGameScene.addItem(&ground);
    myGameScene.addItem(&lake);
    myBallScene.addItem(&option2);
    lake.hide();
    myStartScene.addItem(&haoYe);

    myKlee.setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    myKlee.kleeshadow.setCacheMode(QGraphicsItem::ItemCoordinateCache);

    MyPushBtn *teleport=new MyPushBtn(":/res/teleport1.png");
    MyPushBtn *teleport2=new MyPushBtn(":/res/teleport2.png");
    MyPushBtn *teleport22=new MyPushBtn(":/res/teleport2.png");
    MyPushBtn *teleportBall=new MyPushBtn("://res/wanqiu.png");
    myGameScene.addWidget(teleport);
    myGameScene.addWidget(teleport2);
    myGameScene.addWidget(teleportBall);
    myBallScene.addWidget(teleport22);
    myBallScene.addItem(&myBall);
    myBallScene.addItem(&myKaeya);
    myBallScene.addItem(&myKaeya.kleeshadow);
    teleport2->hide();
    myGameScene.addItem(&option);
    myGameScene.addItem(&myKlee.kleeshadow);
    myGameScene.addItem(&myKlee);
    myGameView.setScene(&myStartScene);//设置场景为开始场景

    this->TitleBGM.setMedia(QUrl("qrc:/res/TitleBGM.mp3"));

    QMediaPlaylist *playlist = new QMediaPlaylist(this);
    playlist->addMedia(QUrl("qrc:/res/GameBGM.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);

    this->KleeDC.setMedia(QUrl("qrc:/res/可莉登场.mp3"));
    this->TitleBGM.play();
    this->TitleBGM.setVolume(10);
    music->setVolume(20);

    MyPushBtn *startBtn=new MyPushBtn(":/res/StartBtn.png");
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.475);
    myStartScene.addWidget(startBtn);
    connect(startBtn,&MyPushBtn::clicked,[=](){
        qDebug()<<"Game Start!";
        this->TitleBGM.setVolume(5);
        this->TitleBGM.stop();
        music->play();
        this->KleeDC.play();
        startBtn->zoom1();
        startBtn->zoom2();
        myKlee.lowest=750;
        QTimer::singleShot(500,this,[=](){
            myGameView.setScene(&myGameScene);
        });
        QTimer::singleShot(8000,this,[=](){
            myGameScene.removeItem(&option);//结束引导
        });
    });
    //开始按钮
    teleport->move(280,800-300);scene=1;
    teleport->show();
    connect(teleport,&MyPushBtn::clicked,[=](){ //传送锚点传送
        teleport->zoom1();
        teleport->zoom2();
        QTimer::singleShot(500,this,[=](){
            teleport->hide();
            teleportBall->hide();
            myKlee.lowest=890;
            left=720;
            ground.hide();
            lake.show();
            myKlee.hide();
            myKlee.setPos(1100,730);
            myGameScene.addWidget(teleport2);
            teleport2->show();
            myKlee.show();
            scene=2;
        });
    });

    teleport2->move(1210,800-300);
    summonFish();
    connect(teleport2,&MyPushBtn::clicked,[=](){ //传送锚点传送回家
        teleport2->zoom1();
        teleport2->zoom2();
        QTimer::singleShot(500,this,[=](){
            teleport2->hide();
            teleport->show();
            teleportBall->show();
            myKlee.lowest=750;
            left=0;
            lake.hide();
            ground.show();
            myKlee.setPos(300,730);
            scene=1;
        });
    });
    teleport22->move(280,800-300);
    connect(teleport22,&MyPushBtn::clicked,[=](){ //传送锚点传送回家
        teleport22->zoom1();
        teleport22->zoom2();
        myFishMoveTimer->start(20);
        myFishSummonTimer->start(1000+qrand()%1000);
        myBombTimer->start(15);
        QTimer::singleShot(500,this,[=](){
            myKlee.setPos(545,730);
            scene = 1;
            right=this->width();
            myBallScene.removeItem(&myKlee);
            myBallScene.removeItem(&myKlee.kleeshadow);
            myGameScene.addItem(&myKlee.kleeshadow);
            myGameScene.addItem(&myKlee);
            myGameView.setScene(&myGameScene);
        });
    });
    teleportBall->move(975,800-148);
    connect(teleportBall,&MyPushBtn::clicked,[=](){ //传送锚点传送去打球

        myFishMoveTimer->stop();
        myFishSummonTimer->stop();
        myBombTimer->stop();
        teleportBall->zoom1();
        teleportBall->zoom2();
        QTimer::singleShot(5000,this,[=](){
            option2.hide();
        });
        QTimer::singleShot(500,this,[=](){
            scene = 3;
            right=750;
            myKaeya.setPos(1100,725);
            myKlee.setPos(300,730);
            myBall.hide();
            myGameScene.removeItem(&myKlee);
            myGameScene.removeItem(&myKlee.kleeshadow);
            myBallScene.addItem(&myKlee.kleeshadow);
            myBallScene.addItem(&myKlee);
            myGameView.setScene(&myBallScene);
        });
    });
    MyPushBtn *exitBtn=new MyPushBtn(":/res/Camp.png");
    myStartScene.addWidget(exitBtn);
    exitBtn->move(this->width()*0.8,this->height()*0.5);
    connect(exitBtn,&MyPushBtn::clicked,[=](){
        qDebug()<<"布响丸辣!";
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
    MyPushBtn *exitBtn3=new MyPushBtn(":/res/leave2.png");
    exitBtn3->move(10,10);
    myBallScene.addWidget(exitBtn3);
    connect(exitBtn3,&MyPushBtn::clicked,this,[=](){
        qDebug()<<"布响丸辣！";
        exitBtn3->zoom1();
        exitBtn3->zoom2();
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
        if(myKlee.x()<left){
            myKlee.setX(left);
        }
        if(myKlee.x()>right-myKlee.pixmap().width()){
            myKlee.setX(right-myKlee.pixmap().width());
        }
        if(myKlee.y()<0){
            myKlee.setY(0);
        }
        if(myKlee.y()>730){
            myKlee.setY(730);
        }
        kleeMove();
        myKlee.kleeshadow.setX(myKlee.x()+18);
        if(myKlee.y()<730){
            myKlee.jump();                            //落地检测
        }
        if(myKlee.coolDown==true&&myKlee.faceto==1)
                myKlee.setPixmap(QPixmap("://res/Klee.png"));
        if(myKlee.coolDown==true&&myKlee.faceto==-1)
                myKlee.setPixmap(QPixmap("://res/Kleem.png"));
        if(myKlee.coolDown==false&&myKlee.faceto==-1)
                myKlee.setPixmap(QPixmap("://res/KleeBomb.png"));
        if(myKlee.coolDown==false&&myKlee.faceto==1)
                myKlee.setPixmap(QPixmap("://res/KleeBombm.png"));

    });

    myBombTimer=new QTimer(this);
    myBombTimer->start(15);
    connect(myBombTimer,&QTimer::timeout,[this](){   //炸弹移动定时器
       for(auto bomb:myBombList)
       {
           bomb->BombMove(QPoint(bomb->dir,0));
           if(bomb->y()>=myKlee.lowest&&bomb->upSpeed<0&&bomb->jumpable!=0){
               bomb->upSpeed=15;
               bomb->jumpable--;
               QMediaPlayer *hop = new QMediaPlayer();
               hop->setMedia(QUrl("qrc:/res/hop.mp3"));
               hop->setVolume(10);
               hop->play();
           }
           bomb->bombshadow.setX(bomb->x()+10);
           if(bomb->jumpable==0){
               bomb->bombshadow.hide();
               myBombList.removeOne(bomb);
               bomb->moveBy(-100,-100);
               bomb->setPixmap(QPixmap(":/res/boom.png"));
               QTimer::singleShot(100,this,[=](){
                   bomb->setPixmap(QPixmap(":/res/boom2.png"));
               });
               QTimer::singleShot(200,this,[=](){
                   myGameScene.removeItem(bomb); //炸弹弹三下爆炸
               });
               QMediaPlayer *end = new QMediaPlayer();
               end->setVolume(10);
               end->setMedia(QUrl("qrc:/res/end.mp3"));
               end->play();
           }
           Collision();

       }
    });
    //开启鱼移动定时器
    myFishMoveTimer = new QTimer(this);
    myFishMoveTimer->start(20);
    connect(myFishMoveTimer,&QTimer::timeout,[this](){
       for(auto Fish:myFishList){
           if(scene==2)
               Fish->show();
           else {
               Fish->hide();
           }
           if(!Fish->die)
           Fish->move();
       }
    });
    myBallMoveTimer = new QTimer(this);
    myBallMoveTimer->start(17);
    connect(myBallMoveTimer,&QTimer::timeout,[=](){
       myBall.BallMove();
       if(myBall.y()>=830) {
          myBall.hide();
          isBall=false;
          kaeyaturn=false;
       }
       if(myBall.collidesWithItem(&myKlee)){
           myBall.upSpeed=20+qrand()%16;
           myBall.speed=7+qrand()%8;
           myBall.dir=1;
           kaeyaturn=true;
       }
       if(myBall.collidesWithItem(&myKaeya)){
           myBall.upSpeed=20+qrand()%16;
           myBall.speed=7+qrand()%8;
           myBall.dir=-1;kaeyaturn=false;
       }
    });
    myKaeyaMoveTimer = new QTimer(this);
    myKaeyaMoveTimer->start(10);
    connect(myKaeyaMoveTimer,&QTimer::timeout,[=](){
        if((myBall.x()<myKaeya.x()&&myBall.x()>700)&&kaeyaturn&&myKaeya.x()-myBall.x()>300){
            myKaeya.moveBy(-10,0);
        }
        if((myBall.x()<myKaeya.x()&&myBall.x()>700)&&kaeyaturn&&myKaeya.x()-myBall.x()<=300){
            myKaeya.moveBy(-5,0);
        }
        if((myBall.x()>myKaeya.x()&&myBall.x()>700)&&kaeyaturn){
            myKaeya.moveBy(10,0);
        }
        myKaeya.kleeshadow.setX(myKaeya.x()+10);
        if(myKaeya.y()>725){
            myKaeya.setY(725);
        }
        if(myKaeya.x()>this->width()-70){
            myKaeya.setX(this->width()-70);
        }
        if(myKaeya.y()<725)
        {
            myKaeya.jump();
        }
        if(myBall.x()==myKaeya.x()&&myKaeya.y()==725){
            myKaeya.upSpeed=20;
            myKaeya.moveBy(0,-myKaeya.upSpeed);
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
        if(myKlee.coolDown&&scene!=3){
            kleeBomb();
            myKlee.kleeshadow.show();
        }
        if(myKlee.coolDown&&scene==3&&!isBall){
            kleeBall();
            myKlee.kleeshadow.show();
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
            myKlee.moveBy(-1*myKlee.moveSpeed,0);
            break;
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
    if(r==0){
        this->KleeAttack.setMedia(QUrl("qrc:/res/弹起来吧.mp3"));
    }
    this->KleeAttack.play();
    QMediaPlayer *begin = new QMediaPlayer();
    begin->setMedia(QUrl("qrc:/res/begin.mp3"));
    begin->setVolume(10);
    begin->play();
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
    newBomb->bombshadow.setY(myKlee.lowest+75);
    myGameScene.addItem(&newBomb->bombshadow);
    myBombList.append(newBomb);
    myKlee.coolDown=false;
    QTimer::singleShot(1500,this,[=](){
        myKlee.coolDown=true;
    });
}
void Widget::kleeBall(){                      //丢球函数
    int r=qrand()%3;
    QMediaPlayer *b = new QMediaPlayer();
    if(r==1){
        b->setMedia(QUrl("qrc:/res/嘿！.mp3"));
    }
    if(r==2){
        b->setMedia(QUrl("qrc:/res/嘿呀.mp3"));
    }
    if(r==0){
        b->setMedia(QUrl("qrc:/res/嚯咦.mp3"));
    }
    b->play();
    myBall.show();
    isBall=true;
    myBall.setPos(myKlee.x()+30,myKlee.y());
    myBall.upSpeed=30+qrand()%6;
    myBall.dir=1;
    myKlee.coolDown=false;
    QTimer::singleShot(1500,this,[=](){
        myKlee.coolDown=true;
    });
}
void Widget::summonFish(){
    myFishSummonTimer=new QTimer(this);
    myFishSummonTimer->start(1000+qrand()%1000);
    connect(myFishSummonTimer,&QTimer::timeout,this,[=](){
        int flag=qrand()%2,x;
        if(flag==0){
            x=-200;
        }
        if(flag==1){
            x=1612;
        }
        Fish* fish=new Fish(QPoint(x,920+qrand()%20));
        if(flag==1){
            fish->speed=-fish->speed;
            fish->setPixmap(QPixmap("://res/fishm.png"));
        }
        myGameScene.addItem(fish);
        myFishList.append(fish);
    });
}
void Widget::Collision(){
    for(int i = 0;i<myBombList.size();i++)
        for(int j = 0;j<myFishList.size();j++){
            if(myBombList[i]->collidesWithItem(myFishList[j]))
            {
                effe *meat=new effe(QPoint(myFishList[j]->pos().x()+50,myFishList[j]->pos().y()-20),QPixmap("://res/hotmeat.png"));
                myGameScene.addItem(meat);
                QTimer::singleShot(100,this,[=](){
                    meat->setPixmap(QPixmap("://res/meat.png"));
                });
                QTimer::singleShot(1000,this,[=](){
                    myGameScene.removeItem(meat);
                    delete meat;
                });
                myFishList[j]->die=true;
                myGameScene.removeItem(myFishList[j]); //炸弹弹三下爆炸
                myFishList.removeOne(myFishList[j]);         
            }
        }
}

