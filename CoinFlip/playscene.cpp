﻿#include "playscene.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QMenuBar>
#include <QLabel>
#include "coinbutton.h"
#include "dataconfig.h"
#include "QTimer"
#include <QMessageBox>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSound>

PlayScene::PlayScene(int level, QWidget *parent)
    : MyMainWindow{parent}
{
    mHasWin = false;
    //返回按键
    QPushButton *btnBack = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png", this);

    btnBack->resize(72, 32);

    connect(btnBack,&QPushButton::clicked,this,&PlayScene::backBtnClicked);

    btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());

    //添加左下角的label
    QLabel *label = new QLabel(this);
    label->setText(QString("Level: %1").arg(level));
    label->resize(150, 50);
    //设置字体
    label->setFont(QFont("华文新魏", 20));
    label->move(30, this->height()-label->height());

    const int colWidth = 50;
    const int rowHeight = 50;
    const int xOffset = 57;
    const int yOffset = 200;

    //取出第几关的二维数组的数据
    dataConfig data;
    QVector <QVector <int > >  dataArray = data.mData[level];
    //16个硬币按键
    for(int row = 0;row < 4; ++row)
    {
        for(int col = 0;col < 4; ++col)
        {
            CoinButton *btn = new CoinButton(this);
            //存储按键到数组的第几行第几列
            mCoins[row][col] = btn;
            //x 坐标 = 列数 * 列宽
            //y 坐标 = 行数 * 行高
            int x = col * colWidth + xOffset;
            int y = row * rowHeight + yOffset;
            btn->setGeometry(x, y, 50, 50);
            //设置row行col列的值，从dataConfing的数据中获取
            btn->setStat(dataArray[row][col]);

            //每次点击硬币就改变状态，状态置反
            connect(btn,&CoinButton::clicked,[=](){
                //每次点击硬币的时候就改变状态
                //btn->flip();
                this->flip(row, col);
            });
        }
    }
}

void PlayScene::flip(int row, int col)
{
    //如果胜利了，就直接放回
    if(mHasWin)
    {
        return;
    }
    this->mCoins[row][col]->flip();

    //QSound::play(":/res/ConFlipSound.wav");
    QSound *sound = new QSound(":/res/ConFlipSound.wav");
    sound->play();

    //翻动第一个延迟其他
    QTimer::singleShot(100,[=](){
        //翻动上下左右的硬币
        //下一行硬币
        if(row+1<4)
        {
            this->mCoins[row+1][col]->flip();
        }
        //上一行硬币
        if(row-1>=0)
        {
            this->mCoins[row-1][col]->flip();
        }
        if(col-1>=0)
        {
            //左边
            this->mCoins[row][col-1]->flip();
        }
        if(col+1<4)
        {
            //右边
            this->mCoins[row][col+1]->flip();
        }

        //判断游戏是否胜利
        this->judgWin();
    });


}

void PlayScene::judgWin()
{
    //16个硬币按键判断状态都是1
    for(int row = 0; row < 4; ++row)
    {
        for(int col = 0; col < 4; ++col)
        {
            //判断某个硬币是银币，游戏继续
            if(!this->mCoins[row][col]->stat())
            {
                //只要有一个是硬币，游戏继续
                return;
            }
        }
    }

    //所有都是金币的情况下游戏结束
    //QMessageBox::information(this,"恭喜","你已经胜利了");
    mHasWin = true;
    //播放胜利音效
    //QSound::play(":/res/LevelWinSound.wav");
    QSound *sound = new QSound(":/res/LevelWinSound.wav");
    sound->play();
    //播放胜利动画
    QLabel *labelWin = new QLabel(this);
    QPixmap pix = QPixmap(":/res/LevelCompletedDialogBg.png");
    labelWin->setPixmap(pix);
    labelWin->resize(pix.size());
    labelWin->show();
    labelWin->move((this->width()-labelWin->width())/2,-labelWin->height());

    QPropertyAnimation *animation = new QPropertyAnimation(labelWin, "geometry", this);
    animation->setStartValue(labelWin->geometry());
    animation->setEndValue(QRect(labelWin->x(),labelWin->y()+100,labelWin->width(),labelWin->height()));
    animation->setDuration(1000);
    //设置动画运动曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //动画播放完自动删除
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void PlayScene::paintEvent(QPaintEvent *event)
{
    //画背景
    QPainter painter(this);
    //搬动画家到菜单栏下面
    painter.translate(0,this->menuBar()->height());
    //画背景图
    QPixmap pix(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //绘制logo
    pix.load(":/res/Title.png");
    //将logo缩放到50%
    pix = pix.scaled(pix.width()/2,pix.height()/2);
    painter.drawPixmap(0,0,pix);
}
