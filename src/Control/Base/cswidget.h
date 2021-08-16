#ifndef CSWIDGET_H
#define CSWIDGET_H

#include <QWidget>
#include "csutils_global.h"


namespace cs
{   // Start of namespace `cs`

class CSTitleBar;
class CSLayout;

class CSUTILS_EXPORT CSWidget : public QWidget
{
    Q_OBJECT

public:
    CSWidget(QWidget *parent = nullptr);
    ~CSWidget() override;

    void setCSLayout(CSLayout *layout);

    CSLayout *cslayout() const;
    QPoint globalPos() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

protected:
    CSLayout *_layout;

};

} // End of namespace `cs`


#endif // CSWIDGET_H
