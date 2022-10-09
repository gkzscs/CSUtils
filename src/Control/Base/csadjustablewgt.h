#ifndef CSAdjustableWgt_H
#define CSAdjustableWgt_H

#include <QWidget>
#include <QToolButton>


namespace cs
{

class CSUTILS_EXPORT CSAdjustableWgt : public QWidget
{
    Q_OBJECT

protected:
    enum Direction
    {
        Unknown,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
        Up,
        Down,
        Left,
        Right
    };

public:
    CSAdjustableWgt(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

protected:
    Direction calcDirection(const QPoint &pos);
    void autoReshapeMouse(const QPoint &pos);
    void autoResize(const QPoint &pos);
    bool isInside(const QPoint &pos);

private:
    void initMember();
    void initUI();

protected:
    bool _pressed;
    Direction _direction;
    QPoint _offset;

};

}   // `cs`

#endif // CSAdjustableWgt_H
