#ifndef CSMULTICOLUMNLABEL_H
#define CSMULTICOLUMNLABEL_H

#include "Control/Base/cswidget.h"


namespace cs
{

class CSUTILS_EXPORT CSMultiColumnLabel : public cs::CSWidget
{
public:
    CSMultiColumnLabel(QWidget *parent = nullptr);
    ~CSMultiColumnLabel() override;

    void clear();
    void setAlignment(Qt::Alignment align);
    void setColumnCount(int n);
    void setText(int col, const QString &txt);
    void setText(const QStringList &listTxts);
    void setBgColor(const QColor &cl);
    void setColor(const QColor &cl);

    Qt::Alignment alignment() const;
    int columnCount() const;
    QString text(int col) const;
    QStringList textList() const;
    QColor bgColor() const;
    QColor color() const;

protected:
    void paintEvent(QPaintEvent *event) override;

protected:
    void drawText(QPainter &p);

protected:
    QRect calcTextRects(int col) const;

private:
    void initMember();
    void initUI();

protected:
    int _columnCount;
    QColor _colorBg;
    QColor _color;
    Qt::Alignment _align;
    QVector<QString> _vecTxts;

};

}   // cs

#endif // CSMULTICOLUMNLABEL_H
