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

    void setPaintAreaSize(const QSize &s);

    QSize paintAreaSize() const;

protected:
    void paintEvent(QPaintEvent *event) override;

protected:
    virtual void drawAll(QPainter &p) = 0;

protected:
    virtual QRect paintAreaRect() const;

    void autoSetPaintAreaSize();

private:
    void initMember();
    void initUI();

protected:
    QSize _sizePaintArea;

};

}   // `cs`

#endif // CSARTWARE_H
