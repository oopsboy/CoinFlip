#ifndef COINBUTTON_H
#define COINBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>

class CoinButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CoinButton(QWidget *parent = nullptr);

    int stat() const;
    void setStat(int newStat);

    //setStat带动画的函数
    void setStatWithAnimation(int stat);

    //硬币翻转函数
    void flip();

signals:

private:
    //硬币状态
    int mStat;
    //记录当前动画帧数是第几帧
    int mFrame;
    //定时器
    QTimer mTimer;

protected:
    void paintEvent(QPaintEvent *ev);

};

#endif // COINBUTTON_H
