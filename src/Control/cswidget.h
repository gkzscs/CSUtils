#ifndef CSWIDGET_H
#define CSWIDGET_H

#include <QWidget>
#include "csutils_global.h"


namespace cs
{   // Start of namespace `cs`

class CSLayout;

class CSUTILS_EXPORT CSWidget : public QWidget
{
    Q_OBJECT

public:
    CSWidget(QWidget *parent = nullptr);
    virtual ~CSWidget() override;

    QPoint globalPos() const;

    void setLayout(CSLayout *layout);
    CSLayout *layout() const;

protected:
    void init();
    virtual void initMember();
    virtual void initUI();
    virtual void initSignalSlot();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

protected:
    CSLayout *_layout;

};

} // End of namespace `cs`


#endif // CSWIDGET_H
