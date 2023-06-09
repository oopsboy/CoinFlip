﻿#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mymainwindow.h"
#include "coinbutton.h"

class PlayScene : public MyMainWindow
{
    Q_OBJECT
public:
    PlayScene(int level, QWidget *parent = nullptr);

    //翻动row行，col列
    void flip(int row, int col);

    //判断胜利
    void judgWin();

signals:
    //点击返回按键发射的信号
    void backBtnClicked();

protected:
    void paintEvent(QPaintEvent *event);

private:
    //硬币按键数组
    CoinButton *mCoins[4][4];
    //胜利的状态
    bool mHasWin;

};

#endif // PLAYSCENE_H
