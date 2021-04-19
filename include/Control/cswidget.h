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

    void setCSLayout(CSLayout *layout);
    CSLayout *cslayout() const;

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

protected:
    CSLayout *_layout;

};

} // End of namespace `cs`


#endif // CSWIDGET_H
