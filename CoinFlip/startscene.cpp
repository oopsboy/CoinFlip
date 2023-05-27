#include "startscene.h"
#include <QPushButton>
#include "mypushbutton.h"
#include <QTimer>
#include <QSound>


StartScene::StartScene(QWidget *parent)
    : MyMainWindow{parent}
{
    this->setWindowTitle("翻金币");


    MyPushButton *btnStart = new MyPushButton(":/res/MenuSceneStartButton.png",
                                              ":/res/MenuSceneStartButton.png",this);
    btnStart->resize(114, 114);

    //按键水平居中
    //计算方式，x = 窗口宽度/2 - 按键宽度/2, y = 窗口宽度*3/4 - 按键高度/2
    btnStart->move((this->width() - btnStart->width())/2,
                   this->height()*3/4-btnStart->height()/2);

    //第二个窗口返回按键被点击
    connect(&this->mSelectScene,&SelectScene::backBtnClicked,[=](){
        //当第二个窗口的返回按键点击的时候
        //QSound::play(":/res/BackButtonSound.wav");
        QSound *sound = new QSound(":/res/BackButtonSound.wav");
        sound->play();
        this->show();
        this->mSelectScene.hide();
        this->move(this->mSelectScene.pos());
    });
    //开始按键被点击
    connect(btnStart, &MyPushButton::clicked,[=](){
        //QSound::play(":/res/TapButtonSound.wav");
        QSound *sound = new QSound(":/res/TapButtonSound.wav");
        sound->play();
        //将按键设置为不可用
        btnStart->setEnabled(false);
        //播放向下动画
        btnStart->moveDown();
        //等待之前动画播放完
        QTimer::singleShot(150,[=](){
            btnStart->moveUp();
        });

        QTimer::singleShot(300,[=](){
            //将按键设置为可用
            btnStart->setEnabled(true);

            //场景转换，隐藏当前窗口，显示第二个窗口
            this->hide();
            this->mSelectScene.show();
            //将窗口移动到当前窗口位置
            this->mSelectScene.move(this->pos());
        });
    });
}
