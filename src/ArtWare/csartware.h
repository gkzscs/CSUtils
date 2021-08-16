#ifndef CSARTWARE_H
#define CSARTWARE_H

/*************************************************************************************
 * @author: cs
 * @date: 2021/05/17
 * @brief:
 * The controls of this category are created for special use, they will show different
 * form with different configuration. In other words, they are dynamic, not always the
 * same.
*************************************************************************************/

#include <QWidget>
#include <QPainter>


namespace cs
{

class CSUTILS_EXPORT CSArtWare : public QWidget
{
    Q_OBJECT

public:
    CSArtWare(QWidget *parent = nullptr);

    void setColor(const QColor &color);

    QColor color() const;

protected:
    void paintEvent(QPaintEvent *event) override;

protected:
    virtual void drawAll(QPainter &p) = 0;

protected:
    void scalePainter(QPainter &p);

private:
    void initMember();
    void initUI();

protected:
    QSize _sizeOrg;
    QColor _color;

};

}   // `cs`

#endif // CSARTWARE_H
