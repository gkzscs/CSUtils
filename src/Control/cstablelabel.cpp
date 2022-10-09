#include "cstablelabel.h"
#include <QPainter>


namespace cs
{

CSTableLabel::CSTableLabel(QWidget *parent)
    : cs::CSWidget(parent)
{
    initMember();
    initUI();
}

CSTableLabel::~CSTableLabel()
{
    _vecTxts.clear();
}

/**
 * @brief CSTableLabel::clear
 */
void CSTableLabel::clear()
{
    for (int i = 0, n = _vecTxts.size(); i < n; ++i)
    {
        _vecTxts[i] = nullptr;
    }
    update();
}

/**
 * @brief Set the alignment of each label item
 * @param align
 */
void CSTableLabel::setAlignment(Qt::Alignment align)
{
    _align = align;
    update();
}

/**
 * @brief CSTableLabel::setRowCount
 * @param n
 */
void CSTableLabel::setRowCount(int n)
{
    if (n <= 0) return;

    _rowCount = n;
    _vecTxts.resize(capacity());
    update();
}

/**
 * @brief Set the column of this label
 * @param n
 */
void CSTableLabel::setColumnCount(int n)
{
    if (n <= 0) return;

    _columnCount = n;
    _vecTxts.resize(capacity());
    update();
}

/**
 * @brief CSTableLabel::setText
 * @param col
 * @param txt
 */
void CSTableLabel::setText(int row, int col, const QString &txt)
{
    if (row < 0 || row >= _rowCount) return;
    if (col < 0 || col >= _columnCount) return;

    _vecTxts[index(row, col)] = txt;
    update();
}

void CSTableLabel::setText(const QStringList &listTxts)
{
    int n = (listTxts.size() < capacity() ? listTxts.size() : capacity());
    for (auto i = 0; i < n; ++i)
    {
        _vecTxts[i] = listTxts.at(i);
    }
    update();
}

void CSTableLabel::setBgColor(const QColor &cl)
{
    _colorBg = cl;
    update();
}

/**
 * @brief Set the color of texts
 * @param cl
 */
void CSTableLabel::setColor(const QColor &cl)
{
    _color = cl;
    update();
}

Qt::Alignment CSTableLabel::alignment() const
{
    return _align;
}

int CSTableLabel::rowCount() const
{
    return _rowCount;
}

int CSTableLabel::columnCount() const
{
    return _columnCount;
}

QString CSTableLabel::text(int row, int col) const
{
    if (row < 0 || row >= _rowCount) return nullptr;
    if (col < 0 || col >= _columnCount) return nullptr;
    return _vecTxts.at(index(row, col));
}

/**
 * @brief CSTableLabel::textList
 * @return
 */
QStringList CSTableLabel::textList() const
{
    QStringList listTxts;
    for (auto txt : _vecTxts)
    {
        listTxts.append(txt);
    }

    return listTxts;
}

QColor CSTableLabel::bgColor() const
{
    return _colorBg;
}

QColor CSTableLabel::color() const
{
    return _color;
}

void CSTableLabel::paintEvent(QPaintEvent *event)
{
    cs::CSWidget::paintEvent(event);

    QPainter p(this);
    drawText(p);
}

/**
 * @brief CSTableLabel::drawText
 * @param p
 */
void CSTableLabel::drawText(QPainter &p)
{
    p.save();
    p.fillRect(rect(), _colorBg);

    p.setPen(_color);
    for (int i = 0; i < _rowCount; ++i)
    {
        for (int j = 0; j < _columnCount; ++j)
        {
            auto &&r = calcTextRects(i, j);
            p.drawText(r, _align, _vecTxts.at(index(i, j)));
        }
    }
    p.restore();
}

/**
 * @brief Calculate the rect of text by its column
 */
QRect CSTableLabel::calcTextRects(int row, int col) const
{
    int labW = width() / _columnCount;
    int labH = height() / _rowCount;
    int labX = col * labW;
    int labY = row * labH;

    return QRect(labX, labY, labW, labH);
}

/**
 * @brief Calculate the capacity of this label
 * @return
 */
inline int CSTableLabel::capacity() const
{
    return (_rowCount * _columnCount);
}

/**
 * @brief Calculate the index by row and col
 * @param row
 * @param col
 * @return
 */
inline int CSTableLabel::index(int row, int col) const
{
    return (row * _columnCount + col);
}

void CSTableLabel::initMember()
{
    _rowCount = 1;
    _columnCount = 1;
    _colorBg = Qt::transparent;
    _color = Qt::white;
    _align = Qt::AlignLeft | Qt::AlignVCenter;
    _vecTxts.resize(capacity());
}

void CSTableLabel::initUI()
{
    resize(300, 30);
    setAttribute(Qt::WA_StyledBackground);
}

}   // cs

