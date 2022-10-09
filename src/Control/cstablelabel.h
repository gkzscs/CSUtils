#ifndef CSTABLELABEL_H
#define CSTABLELABEL_H

#include "Control/Base/cswidget.h"


namespace cs
{

class CSUTILS_EXPORT CSTableLabel : public cs::CSWidget
{
    Q_OBJECT

public:
    CSTableLabel(QWidget *parent = nullptr);
    ~CSTableLabel() override;

    void clear();
    void setAlignment(Qt::Alignment align);
    void setRowCount(int n);
    void setColumnCount(int n);
    void setText(int row, int col, const QString &txt);
    void setText(const QStringList &listTxts);
    void setBgColor(const QColor &cl);
    void setColor(const QColor &cl);

    Qt::Alignment alignment() const;
    int rowCount() const;
    int columnCount() const;
    QString text(int row, int col) const;
    QStringList textList() const;
    QColor bgColor() const;
    QColor color() const;

protected:
    void paintEvent(QPaintEvent *event) override;

protected:
    void drawText(QPainter &p);

protected:
    QRect calcTextRects(int row, int col) const;

    inline int capacity() const;
    inline int index(int row, int col) const;

private:
    void initMember();
    void initUI();

protected:
    int _rowCount;
    int _columnCount;
    QColor _colorBg;
    QColor _color;
    Qt::Alignment _align;
    QVector<QString> _vecTxts;

};

}   // cs

#endif // CSTABLELABEL_H
