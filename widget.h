#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsPixmapItem>//元素
#include <QGraphicsScene>//场景
#include <QGraphicsView>//视图
#include<QTimer>
#include <QList>
#include <myklee.h>
#include <mypushbtn.h>
#include <bomb.h>
#include <QMediaPlayer>

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

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::Widget *ui;
    QGraphicsPixmapItem myBg;
    QGraphicsPixmapItem myTitle;
    QGraphicsPixmapItem haoYe;
    QGraphicsPixmapItem ground;
    QGraphicsScene myGameScene;
    QGraphicsScene myStartScene;
    QGraphicsView myGameView;
    QList<int> myKeyList;
    QList<Bomb*> myBombList;
    QTimer *myKleeMoveTimer;
    QTimer *myBombTimer;
    QMediaPlayer TitleBGM;
    QMediaPlayer GameBGM;
    QMediaPlayer KleeDC;
    QMediaPlayer KleeAttack;
    myklee myKlee;
};

#endif // WIDGET_H
