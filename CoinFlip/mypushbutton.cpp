#include "mypushbutton.h"
#include <QPainter>
#include <QPropertyAnimation>
MyPushButton::MyPushButton(QString normalImg, QString pressedImg,QWidget *parent)
    : QPushButton{parent}
    , mNormalImg(normalImg)
    , mPressedImg(pressedImg)
{
    mStat = Normal;
}

void MyPushButton::moveDown()
{
    //位置大小属性发生变化
    //给定开始位置大小属性
    //给定结束位置大小属性
    //给定速度，给定动画时长

    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry", this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(), this->y()+10,this->width(),this->height()));
    animation->setDuration(100);    //速度
    animation->start(QAbstractAnimation::DeleteWhenStopped);    //动画停止时删除自己

}

void MyPushButton::moveUp()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry", this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(), this->y()-10,this->width(),this->height()));
    animation->setDuration(100);    //速度
    animation->start(QAbstractAnimation::DeleteWhenStopped);    //动画停止时删除自己
}

void MyPushButton::paintEvent(QPaintEvent *ev)
{
    //绘制按键的图片
    QPainter painter(this);
    QPixmap pix;
    if (mStat == Normal)
    {
        pix.load(mNormalImg);
    }
    if (mStat == Pressed)
    {
        pix.load(mPressedImg);
    }
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //绘制按键的文字
    //其中的0,0是居中
    painter.drawText(0,0,this->width(),this->height(),
                     Qt::AlignHCenter|Qt::AlignVCenter, this->text());
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    //鼠标按下状态切换到Pressed
    this->mStat = Pressed;
    update();
    //保证信号和槽功能
    QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    //鼠标松开状态切换到Normal
    this->mStat = Normal;
    update();
    //保证信号和槽功能
    QPushButton::mouseReleaseEvent(e);
}
