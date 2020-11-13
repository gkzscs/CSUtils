#ifndef CSWIDGET_H
#define CSWIDGET_H

#include <QWidget>
#include "csutils_global.h"


class CSUTILS_EXPORT CSWidget : public QWidget
{
    Q_OBJECT

public:
    CSWidget(QWidget *parent = nullptr);
    virtual ~CSWidget() override;

    QPoint globalPos() const;

protected:
    void init();
    virtual void initMember();
    virtual void initUI();
    virtual void initSignalSlot();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
};


#endif // CSWIDGET_H
