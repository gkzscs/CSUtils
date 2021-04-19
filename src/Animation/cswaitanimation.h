#ifndef WAITANIMATION_H
#define WAITANIMATION_H

#include "csanimation.h"


namespace cs
{

class CSUTILS_EXPORT CSWaitAnimation : public CSAnimation
{
    Q_OBJECT

public:
    CSWaitAnimation(QWidget *parent = nullptr);

    void setInfo(const QString &info);

    QString info() const;

protected:
    void initMember();
    void initSignalSlot();

protected:
    void drawAll(QPainter &p) override;
    void drawDots(QPainter &p);
    void drawInfo(QPainter &p);

protected:
    int _angle;
    QString _info;

};

}   // End of `cs`

#endif // WAITANIMATION_H
