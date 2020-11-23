#ifndef CSWIDGET_H
#define CSWIDGET_H

#include <QWidget>
#include "csutils_global.h"


namespace cs
<<<<<<< HEAD:include/Control/cswidget.h
{   // Start of namespace `cs`
=======
{
>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013:src/csutils/cswidget.h

class CSLayout;

class CSUTILS_EXPORT CSWidget : public QWidget
{
    Q_OBJECT

public:
    CSWidget(QWidget *parent = nullptr);
    virtual ~CSWidget() override;

    QPoint globalPos() const;
    void setLayout(CSLayout *lay);
    CSLayout *layout() const;

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

<<<<<<< HEAD:include/Control/cswidget.h
} // End of namespace `cs`
=======
}
>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013:src/csutils/cswidget.h

#endif // CSWIDGET_H
