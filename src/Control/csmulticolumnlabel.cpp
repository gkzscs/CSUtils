#include "csmulticolumnlabel.h"
#include <QPainter>


namespace cs
{

CSMultiColumnLabel::CSMultiColumnLabel(QWidget *parent)
    : cs::CSWidget(parent)
{
    initMember();
    initUI();
}

CSMultiColumnLabel::~CSMultiColumnLabel()
{
    _vecTxts.clear();
}

/**
 * @brief CSMultiColumnLabel::clear
 */
void CSMultiColumnLabel::clear()
{
    for (int i = 0, n = _vecTxts.size(); i < n; ++i)
    {
        _vecTxts[i] = nullptr;
    }
    update();
}

/**
 * @brief Set the alignment of each item
 * @param align
 */
void CSMultiColumnLabel::setAlignment(Qt::Alignment align)
{
    _align = align;
    update();
}

/**
 * @brief Set the column of this label
 * @param n
 */
void CSMultiColumnLabel::setColumnCount(int n)
{
    if (n <= 0) return;

    _columnCount = n;
    _vecTxts.resize(_columnCount);
    update();
}

/**
 * @brief CSMultiColumnLabel::setText
 * @param col
 * @param txt
 */
void CSMultiColumnLabel::setText(int col, const QString &txt)
{
    if (col < 0 || col >= _columnCount) return;

    _vecTxts[col] = txt;
    update();
}

void CSMultiColumnLabel::setText(const QStringList &listTxts)
{
    int n = (listTxts.size() < _columnCount ? listTxts.size() : _columnCount);
    for (auto i = 0; i < n; ++i)
    {
        _vecTxts[i] = listTxts.at(i);
    }
    update();
}

void CSMultiColumnLabel::setBgColor(const QColor &cl)
{
    _colorBg = cl;
    update();
}

/**
 * @brief Set the color of texts
 * @param cl
 */
void CSMultiColumnLabel::setColor(const QColor &cl)
{
    _color = cl;
    update();
}

Qt::Alignment CSMultiColumnLabel::alignment() const
{
    return _align;
}

int CSMultiColumnLabel::columnCount() const
{
    return _columnCount;
}

QString CSMultiColumnLabel::text(int col) const
{
    if (col < 0 || col >= _columnCount) return nullptr;
    return _vecTxts.at(col);
}

/**
 * @brief CSMultiColumnLabel::textList
 * @return
 */
QStringList CSMultiColumnLabel::textList() const
{
    QStringList listTxts;
    for (auto txt : _vecTxts)
    {
        listTxts.append(txt);
    }

    return listTxts;
}

QColor CSMultiColumnLabel::bgColor() const
{
    return _colorBg;
}

QColor CSMultiColumnLabel::color() const
{
    return _color;
}

void CSMultiColumnLabel::paintEvent(QPaintEvent *event)
{
    cs::CSWidget::paintEvent(event);

    QPainter p(this);
    drawText(p);
}

/**
 * @brief CSMultiColumnLabel::drawText
 * @param p
 */
void CSMultiColumnLabel::drawText(QPainter &p)
{
    p.save();
    p.fillRect(rect(), _colorBg);

    p.setPen(_color);
    for (int i = 0; i < _columnCount; ++i)
    {
        auto &&r = calcTextRects(i);
        p.drawText(r, _align, _vecTxts.at(i));
    }
    p.restore();
}

/**
 * @brief Calculate the rect of text by its column
 */
QRect CSMultiColumnLabel::calcTextRects(int col) const
{
    // Reset
    const int space = 0;
    int labX = 0;
    int labY = 0;
    int labW = (width()+space) / _columnCount - space;
    int labH = height();

    for (int i = 0; i < _columnCount; ++i)
    {
        if (i == col) return QRect(labX, labY, labW, labH);
        labX += labW + space;
    }

    return QRect();
}

void CSMultiColumnLabel::initMember()
{
    _columnCount = 1;
    _colorBg = Qt::transparent;
    _color = Qt::white;
    _align = Qt::AlignLeft | Qt::AlignVCenter;
    _vecTxts.resize(_columnCount);
}

void CSMultiColumnLabel::initUI()
{
    resize(300, 30);
    setAttribute(Qt::WA_StyledBackground);
}

}   // cs
