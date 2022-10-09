#ifndef CSFoldBox_H
#define CSFoldBox_H

#include "Control/Base/cswidget.h"


namespace cs
{

class CSVBoxLayout;

class CSUTILS_EXPORT CSFoldBox : public cs::CSWidget
{
    Q_OBJECT

public:
    CSFoldBox(QWidget *parent = nullptr);

    void setFold(bool flag);
    void setHead(QWidget *head);
    void setBody(QWidget *body);
    bool isFold() const;
    QWidget *head() const;
    QWidget *body() const;

protected:
    void initMember();
    void initUI();

protected:
    void mousePressEvent(QMouseEvent *e) override;
//    void mouseReleaseEvent(QMouseEvent *e) override;

signals:
    void foldChangeSignal(bool fold);

protected:
    cs::CSVBoxLayout *_vl;
    QWidget *_head;
    QWidget *_body;

    bool _fold;
//    bool _pressed;

};

}   // End of `cs`

#endif // CSFoldBox_H
