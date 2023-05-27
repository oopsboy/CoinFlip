#include "coinbutton.h"
#include <QPainter>
CoinButton::CoinButton(QWidget *parent)
    : QPushButton{parent}
{
    //初始状态
    this->setStat(0);

    //设置按键不规则样式，去掉边框
    this->setStyleSheet("QPushButton{border:0px;}");


    //动画的定时器信号和槽实现
    connect(&this->mTimer,&QTimer::timeout,[=](){
        if(this->mStat)
        {
            //银币翻转
            this->mFrame--;
        }
        else
        {
            this->mFrame++;
        }

        //加载相应帧的图片
        QString frameName = QString(":/res/Coin000%1.png").arg(this->mFrame);
        this->setIcon(QIcon(frameName));
        //停止计时器
        if(this->mFrame == 8||this->mFrame==1)
        {
            this->mTimer.stop();
        }
    });
}

int CoinButton::stat() const
{
    return mStat;
}

void CoinButton::setStat(int newStat)
{
    mStat = newStat;
    if(this->mStat)
    {
        //金币
        this->setIcon(QIcon(":/res/Coin0001.png"));
    }
    else
    {
        //银币
        this->setIcon(QIcon(":/res/Coin0008.png"));
    }
    //设置icon大小
    this->setIconSize(this->size());
}

void CoinButton::setStatWithAnimation(int stat)
{
    this->mStat = stat;
    //mStat == 1,表示银币翻金币
    if(this->mStat)
    {
        this->mFrame = 8;

    }
    else
    {
        this->mFrame = 1;
    }
    this->mTimer.start(50);   //1000毫秒
}

void CoinButton::flip()
{
    //this->setStat(!this->stat());
    this->setStatWithAnimation(!this->stat());
}

void CoinButton::paintEvent(QPaintEvent *ev)
{
    //绘制按键的图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/BoardNode.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    //调用父类的paintEvent
    QPushButton::paintEvent(ev);
}
