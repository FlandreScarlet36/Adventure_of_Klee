#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsPixmapItem>//元素
#include <QGraphicsScene>//场景
#include <QGraphicsView>//视图
#include <QTimer>
#include <QList>
#include <myklee.h>
#include <mypushbtn.h>
#include <bomb.h>
#include <QMediaPlayer>
#include <fish.h>
#include <effe.h>
#include <QMediaPlaylist>
#include <ball.h>

//元素--》场景--》视图

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void kleeMove();
    void kleeBomb();
    void kleeHop();
    void kleeBall();
    void summonFish();
    void Collision();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::Widget *ui;
    QGraphicsPixmapItem myBg;
    QGraphicsPixmapItem myTitle;
    QGraphicsPixmapItem option;
    QGraphicsPixmapItem haoYe;
    QGraphicsPixmapItem ground;
    QGraphicsPixmapItem ground2;
    QGraphicsPixmapItem lake;
    QGraphicsPixmapItem option2;
    QGraphicsScene myGameScene;
    QGraphicsScene myStartScene;
    QGraphicsScene myBallScene;
    QGraphicsView myGameView;
    QList<int> myKeyList;
    QList<Bomb*> myBombList;
    QList<Fish*> myFishList;
    QTimer *myKleeMoveTimer;
    QTimer *myBombTimer;
    QTimer *myFishSummonTimer;
    QTimer *myFishMoveTimer;
    QTimer *myShadowMoveTimer;
    QTimer *myBallMoveTimer;
    QTimer *myKaeyaMoveTimer;
    QMediaPlayer TitleBGM;
    QMediaPlayer KleeDC;
    QMediaPlayer KleeAttack;
    myklee myKlee;
    myklee myKaeya;
    Ball myBall;

    int left;
    int right;
    int scene;
    bool isBall=false;
    bool kaeyaturn=true;
};

#endif // WIDGET_H
