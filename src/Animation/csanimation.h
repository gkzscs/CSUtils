#ifndef CSANIMATION_H
#define CSANIMATION_H

#include <QWidget>
#include <QTime>


namespace cs
{

class CSUTILS_EXPORT CSAnimation : public QWidget
{
    Q_OBJECT

public:
    CSAnimation(QWidget *parent = nullptr);

    void start();
    void stop();
    bool active() const;

    void setDuration(int msec);
    void setSpeed(int n);

    int duration() const;
    int speed() const;

protected:
    void initMember();
    void initUI();
    void initSignalSlot();

protected:
    std::tuple<double, double> scaleRatio() const;

protected:
    // Derived class should override this method
    virtual void drawAll(QPainter &p);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

protected:
    QTimer *_timerDraw;
    QTimer *_timerDuration;

};

}   // End of `cs`

#endif // CSANIMATION_H
