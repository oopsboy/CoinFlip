#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    enum MyPushButtonStat
    {
        Normal,
        Pressed
    };
    MyPushButton(QString normalImg, QString pressedImg, QWidget *parent = nullptr);

    //动画函数：往上，往下运动
    void moveDown();
    void moveUp();
protected:
    void paintEvent(QPaintEvent *ev);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:


private:
    //正常状态的图片
    QString mNormalImg;
    QString mPressedImg;
    //按键状态
    MyPushButtonStat mStat;
};

#endif // MYPUSHBUTTON_H
