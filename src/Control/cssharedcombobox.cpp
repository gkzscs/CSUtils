#include "cssharedcombobox.h"
#include <QDesktopWidget>


namespace cs
{

/******************************************* Macros ***********************************************************/
#define VALIDATE_INDEX(idx)      do { if (idx < 0 || idx >= _listItemInfos.size()) return; } while (0)
#define VALIDATE_CURRENT_INDEX(res)  do { if (_curIndex < 0 || _curIndex >= _listItemInfos.size()) return res; } while (0)


/***************************************** Static Constants ****************************************************/
static const int scBaseBarW = 6;


CSSharedComboBox::CSSharedComboBox(QWidget *parent)
    : cs::CSWidget(parent)
{
    initMember();
    initUI();
}

CSSharedComboBox::~CSSharedComboBox()
{
    _listItemInfos.clear();
}

/**
 * @brief CSSharedComboBox::popup
 */
void CSSharedComboBox::popup(QWidget *wgt)
{
    // Move to the left bottom of wgt
    if (wgt)
    {
        auto wgtParent = (wgt->parentWidget() ? wgt->parentWidget() : wgt);
        auto pos = wgtParent->mapToGlobal(wgt->geometry().bottomLeft());
        if (pos.y()+height() > QApplication::desktop()->height())
        {
            pos = QPoint(pos.x(), pos.y()-wgt->height()-height());
        }
        move(pos);
    }

    // Show combo box
    show();
}

void CSSharedComboBox::addItem(const QString &text, const QVariant &userData)
{
    addItem(QIcon(), text, userData);
}

void CSSharedComboBox::addItem(const QIcon &icon, const QString &text, const QVariant &userData)
{
    auto info = new ItemInfo(icon, text, userData);
    _listItemInfos.append(info);

    updateProperSize();
    update();
}

void CSSharedComboBox::addItems(const QStringList &texts)
{
    for (auto txt : texts)
    {
        auto info = new ItemInfo(txt);
        _listItemInfos.append(info);
    }

    updateProperSize();
    update();
}

void CSSharedComboBox::insertItem(int index, const QString &text, const QVariant &userData)
{
    insertItem(index, QIcon(), text, userData);
}

void CSSharedComboBox::insertItem(int index, const QIcon &icon, const QString &text, const QVariant &userData)
{
    if (index < 0 || index > _listItemInfos.size()) return;

    auto info = new ItemInfo(icon, text, userData);
    _listItemInfos.insert(index, info);

    updateProperSize();
    update();
}

void CSSharedComboBox::insertItems(int index, const QStringList &texts)
{
    if (index < 0 || index > _listItemInfos.size()) return;

    for (auto it = texts.rbegin(); it != texts.rend(); ++it)
    {
        auto info = new ItemInfo(QIcon(), *it);
        _listItemInfos.insert(index, info);
    }

    updateProperSize();
    update();
}

void CSSharedComboBox::removeItem(int index)
{
    VALIDATE_INDEX(index);

    _listItemInfos.removeAt(index);

    updateProperSize();
    update();
}

void CSSharedComboBox::clear()
{
    _listItemInfos.clear();
    _pressedProgrssBar = false;
    _curIndex = 0;
    _tmpCurIndex = 0;
    _offsetY = 0;
    _tmpOffsetY = 0;
    _pressedY = 0;

    updateProperSize();
    update();
}

/**
 * @brief Set the mode of content
 * @param md
 */
void CSSharedComboBox::setContentMode(ContentMode md)
{
    _contentMode = md;
    update();
}

/**
 * @brief CSSharedComboBox::setBgColor
 * @param cl
 */
void CSSharedComboBox::setBgColor(const QColor &cl)
{
    _bgColor = cl;
    update();
}

/**
 * @brief Set the color of text
 * @param cl
 */
void CSSharedComboBox::setColor(const QColor &cl)
{
    _color = cl;
    update();
}

/**
 * @brief CSSharedComboBox::setPageMaxCount
 * @param n
 */
void CSSharedComboBox::setPageMaxCount(int n)
{
    _pageMaxCount = n;

    updateProperSize();
    update();
}

/**
 * @brief CSSharedComboBox::setCurrentIndex
 * @param index
 */
void CSSharedComboBox::setCurrentIndex(int index)
{
    VALIDATE_INDEX(index);

    _curIndex = index;
    update();

    // Emit signal
    emit currentIndexChanged(index);
    emit currentTextChanged(_listItemInfos.at(index)->text);
}

void CSSharedComboBox::setCurrentText(const QString &text)
{
    auto idx = findText(text);
    setCurrentIndex(idx);    
}

void CSSharedComboBox::setIconSize(const QSize &size)
{
    _sizeIcon = size;
    updateProperIconSize();
    updateProperItemHeight();
    update();
}

void CSSharedComboBox::setFont(const QFont &f)
{
    QWidget::setFont(f);
    updateProperItemHeight();
    update();
}

void CSSharedComboBox::setItemText(int index, const QString &text)
{
    VALIDATE_INDEX(index);

    auto info = _listItemInfos.at(index);
    if (!info) return;

    info->text = text;
}

void CSSharedComboBox::setItemIcon(int index, const QIcon &icon)
{
    VALIDATE_INDEX(index);

    auto info = _listItemInfos.at(index);
    if (!info) return;

    info->icon = icon;
}

void CSSharedComboBox::setItemData(int index, const QVariant &value)
{
    VALIDATE_INDEX(index);

    auto info = _listItemInfos.at(index);
    if (!info) return;

    info->data = value;
}

/**
 * @brief Find the text and return its index, return `-1` if not found
 * @param text
 * @return
 */
int CSSharedComboBox::findText(const QString &text) const
{
    for (int i = 0, n = _listItemInfos.size(); i < n; ++i)
    {
        if (_listItemInfos.at(i)->text != text) continue;
        return i;
    }

    return -1;
}

int CSSharedComboBox::findData(const QVariant &data) const
{
    for (int i = 0, n = _listItemInfos.size(); i < n; ++i)
    {
        if (_listItemInfos.at(i)->data != data) continue;
        return i;
    }

    return -1;
}

int CSSharedComboBox::currentIndex() const
{
    return _curIndex;
}

QString CSSharedComboBox::currentText() const
{
    VALIDATE_CURRENT_INDEX(nullptr);

    auto info = _listItemInfos.at(_curIndex);
    if (!info) return nullptr;

    return info->text;
}

QVariant CSSharedComboBox::currentData() const
{
    VALIDATE_CURRENT_INDEX(QVariant());

    auto info = _listItemInfos.at(_curIndex);
    if (!info) return QVariant();

    return info->data;
}

QString CSSharedComboBox::itemText(int index) const
{
    VALIDATE_CURRENT_INDEX(nullptr);

    auto info = _listItemInfos.at(index);
    if (!info) return nullptr;

    return info->text;
}

QIcon CSSharedComboBox::itemIcon(int index) const
{
    VALIDATE_CURRENT_INDEX(QIcon());

    auto info = _listItemInfos.at(index);
    if (!info) return QIcon();

    return info->icon;
}

QVariant CSSharedComboBox::itemData(int index) const
{
    VALIDATE_CURRENT_INDEX(QVariant());

    auto info = _listItemInfos.at(index);
    if (!info) return QVariant();

    return info->data;
}

void CSSharedComboBox::paintEvent(QPaintEvent *e)
{
    cs::CSWidget::paintEvent(e);

    QPainter p(this);
    drawItems(p);
    drawScrollBar(p);
    drawBorder(p);
}

void CSSharedComboBox::showEvent(QShowEvent *e)
{
    cs::CSWidget::showEvent(e);

    // Reset member variable
    _tmpCurIndex = _curIndex;

    // Play property animation
    {
        QEventLoop loop;
        QPropertyAnimation ani(this, "size");

        connect(&ani, &QPropertyAnimation::finished, &loop, &QEventLoop::quit);

        ani.setDuration(200);
        ani.setStartValue(QSize(width(), 0));
        ani.setEndValue(size());
        ani.start();

        loop.exec();
    }
}

void CSSharedComboBox::mousePressEvent(QMouseEvent *e)
{
    cs::CSWidget::mousePressEvent(e);

    // If pressed on base scroll bar
    const auto &pos = e->pos();
    auto rectBase = calcBaseScrollBarRect();
    if (!rectBase.contains(pos)) return;

    // If pressed inner current scroll bar
    auto rectCurrent = calcCurrentScrollBarRect();
    if (rectCurrent.contains(pos))
    {
        _tmpOffsetY = _offsetY;
        _pressedProgrssBar = true;
        _pressedY = pos.y();
    }
}

void CSSharedComboBox::mouseMoveEvent(QMouseEvent *e)
{
    cs::CSWidget::mouseMoveEvent(e);

    if (_pressedProgrssBar)
    {
        int n = calcIndexOffset(_pressedY - e->y());
        updateOffsetYByIndex(n);

        return;
    }

    auto r = calcContentRect();
    if (!r.contains(e->pos())) return;
    _tmpCurIndex = findItemByPos(e->y());
    update();
}

void CSSharedComboBox::mouseReleaseEvent(QMouseEvent *e)
{
    cs::CSWidget::mouseReleaseEvent(e);

    if (_pressedProgrssBar)
    {
        _pressedProgrssBar = false;
        return;
    }

    // Hide the window
    hide();

    // Reset current index
    auto idx = findItemByPos(e->y());
    setCurrentIndex(idx);

    // Emit signal
    VALIDATE_INDEX(idx);
    emit activated(idx);
    emit activated(_listItemInfos.at(idx)->text);
}

void CSSharedComboBox::wheelEvent(QWheelEvent *e)
{
    cs::CSWidget::wheelEvent(e);

    int n = e->angleDelta().y() / _itemHeight;
    updateOffsetYByIndex(n);
}

/**
 * @brief CSSharedComboBox::drawItems
 * @param p
 */
void CSSharedComboBox::drawItems(QPainter &p)
{
    auto idx = calcFirstVisibleItemIndex();
    auto n = (idx+_pageMaxCount <= count() ? idx+_pageMaxCount : count());

    p.save();
    p.fillRect(rect(), _bgColor);

    p.setPen(_color);

    for (int i = idx; i < n; ++i)
    {
        drawItemBackground(i, p);
        if (_contentMode == IconOnly || _contentMode == TextBesideIcon) drawItemIcon(i, p);
        if (_contentMode == TextOnly || _contentMode == TextBesideIcon) drawItemText(i, p);
    }
    p.restore();
}

/**
 * @brief Draw scroll bar if needed
 * @param p
 */
void CSSharedComboBox::drawScrollBar(QPainter &p)
{
    if (_pageMaxCount >= _listItemInfos.size()) return;

    drawBaseScrollBar(p);
    drawCurrentScrollBar(p);
}

/**
 * @brief CSSharedComboBox::drawItemBackground
 * @param index
 * @param p
 */
void CSSharedComboBox::drawItemBackground(int index, QPainter &p)
{
    VALIDATE_INDEX(index);

    if (index != _tmpCurIndex) return;

    auto r = calcItemRect(index);
    auto color = newColor(_bgColor);

    p.fillRect(r, color);
}

/**
 * @brief CSSharedComboBox::drawBorder
 * @param p
 */
void CSSharedComboBox::drawBorder(QPainter &p)
{
    auto r = calcBorderRect();
    auto color = newColor(_bgColor);

    p.save();
    p.setPen(color);
    p.drawRect(r);
    p.restore();
}

void CSSharedComboBox::drawItemIcon(int index, QPainter &p)
{
    VALIDATE_INDEX(index);

    auto r = calcItemIconRect(index);
    auto icon = _listItemInfos.at(index)->icon;

    p.drawPixmap(r, icon.pixmap(_sizeIcon));
}

void CSSharedComboBox::drawItemText(int index, QPainter &p)
{
    VALIDATE_INDEX(index);

    auto r = calcItemTextRect(index);
    auto txt = _listItemInfos.at(index)->text;

    p.drawText(r, Qt::AlignLeft | Qt::AlignVCenter, txt);
}

void CSSharedComboBox::drawBaseScrollBar(QPainter &p)
{
    auto r = calcBaseScrollBarRect();
    int x = r.x() + r.width()/2;
    auto line = QLine(x, r.y(), x, r.y()+r.height());
    auto pen = p.pen();
    auto cl = newColor(_bgColor);

    pen.setColor(cl);
    pen.setWidth(r.width());
    pen.setCapStyle(Qt::PenCapStyle::RoundCap);

    p.save();
    p.setPen(pen);
    p.drawLine(line);
    p.restore();
}

void CSSharedComboBox::drawCurrentScrollBar(QPainter &p)
{
    auto r = calcCurrentScrollBarRect();
    int x = r.x() + r.width()/2;
    auto line = QLine(x, r.y(), x, r.y()+r.height());
    auto pen = p.pen();
    auto cl = _bgColor;
    if (_pressedProgrssBar) cl = cl.lighter();

    pen.setColor(cl);
    pen.setWidth(r.width());
    pen.setCapStyle(Qt::PenCapStyle::RoundCap);

    p.save();
    p.setPen(pen);
    p.drawLine(line);
    p.restore();
}

/**
 * @brief CSSharedComboBox::calcFontHeight
 * @return
 */
int CSSharedComboBox::calcFontHeight() const
{
    QFontMetrics fm(font());
    return fm.height();
}

void CSSharedComboBox::updateProperItemHeight()
{
    auto txtH = calcFontHeight();
    _itemHeight = qMax(_sizeIcon.height(), txtH);

    updateProperSize();
}

void CSSharedComboBox::updateProperIconSize()
{
    int iconW = qMin(_sizeIcon.width(), _sizeIcon.height());
    _sizeIcon = QSize(iconW, iconW);

    updateProperSize();
}

void CSSharedComboBox::updateProperSize()
{
    auto n = (_listItemInfos.size() < _pageMaxCount ? _listItemInfos.size() : _pageMaxCount);
    resize(width(), n*_itemHeight);
}

/**
 * @brief CSSharedComboBox::updateOffsetY
 */
void CSSharedComboBox::updateOffsetYByIndex(int offsetIdx)
{
    if (_pressedProgrssBar) _offsetY = _tmpOffsetY - offsetIdx*_itemHeight;
    else _offsetY -= offsetIdx*_itemHeight;

    int diffCount = (_listItemInfos.size() < _pageMaxCount ? 0 : _listItemInfos.size() - _pageMaxCount);
    if (_offsetY < 0) _offsetY = 0;
    if (_offsetY > (diffCount*_itemHeight)) _offsetY = diffCount*_itemHeight;
    if (offsetIdx != 0) update();
}

/**
 * @brief CSSharedComboBox::calcVisibleItemIndexes
 * @return
 */
int CSSharedComboBox::calcFirstVisibleItemIndex() const
{
    int h = _itemHeight;
    int idxBegin = _offsetY / h;

    return idxBegin;
}

/**
 * @brief CSSharedComboBox::calcIndexOffset
 * @param offsetY
 * @return
 */
int CSSharedComboBox::calcIndexOffset(int offsetY) const
{
    int baseBarH = height();
    int currentBarH = (_pageMaxCount * height() / _listItemInfos.size());
    int diffY = offsetY * count() * _itemHeight / (baseBarH - currentBarH);
    int n = diffY / _itemHeight;

    return n;
}

/**
 * @brief CSSharedComboBox::calcContentRect
 * @return
 */
QRect CSSharedComboBox::calcContentRect() const
{
    int w = width() - scBaseBarW;

    return QRect(0, 0, w, height());
}

/**
 * @brief CSSharedComboBox::calcItemRect
 * @param idx
 * @return
 */
QRect CSSharedComboBox::calcItemRect(int idx) const
{
    int w = width() - scBaseBarW;
    int h = _itemHeight;
    int x = 0;
    int y = (h * idx) - _offsetY;

    return QRect(x, y, w, h);
}

QRect CSSharedComboBox::calcItemIconRect(int idx) const
{
    auto r = calcItemRect(idx);

    switch (_contentMode)
    {
    case TextOnly:
        r = QRect();
        break;
    case IconOnly:
    case TextBesideIcon:
    {
        int x = 0;
        int y = r.y() + (r.height() - _sizeIcon.height()) / 2;
        r = QRect(x, y, _sizeIcon.width(), _sizeIcon.height());
        break;
    }
    }

    return r;
}

QRect CSSharedComboBox::calcItemTextRect(int idx) const
{
    auto r = calcItemRect(idx);

    switch (_contentMode)
    {
    case IconOnly:
        r = QRect();
        break;
    case TextOnly:
        break;
    case TextBesideIcon:
    {
        int w = r.width() - _sizeIcon.width();
        int x = _sizeIcon.width();
//        int y = r.y() + (r.height() - h) / 2;
        r = QRect(x, r.y(), w, r.height());
        break;
    }
    }
//    auto h = calcFontHeight();
//    int w = r.width() - _sizeIcon.width();
//    int x = _sizeIcon.width();
//    int y = r.y() + (r.height() - h) / 2;

    return r;
}

QRect CSSharedComboBox::calcBaseScrollBarRect() const
{
    int w = scBaseBarW;
    int h = height();
    int x = width() - w;
    int y = 0;

    return QRect(x, y, w, h);
}

QRect CSSharedComboBox::calcCurrentScrollBarRect() const
{
    const int margin = 1;
    int w = scBaseBarW - margin*2;
    int h = (_pageMaxCount * height() / _listItemInfos.size());
    int x = width() - w - margin;
    int y = (_offsetY * height() / (_itemHeight * _listItemInfos.size()));

    return QRect(x, y, w, h);
}

/**
 * @brief CSSharedComboBox::calcBorderRect
 * @return
 */
QRect CSSharedComboBox::calcBorderRect() const
{
    int x = 0;
    int y = 0;
    int w = width()-1;
    int h = height()-1;

    return QRect(x, y, w, h);
}

/**
 * @brief Get the index of item that is on specified position
 * @param y
 * @return
 */
int CSSharedComboBox::findItemByPos(int y) const
{
    return ((y + _offsetY) / _itemHeight);
}

/**
 * @brief Get a new color based on origin color
 * @param cl
 * @return
 */
QColor CSSharedComboBox::newColor(const QColor &cl) const
{
    auto r = (cl.red() + 128) % 255;
    auto g = (cl.green() + 128) % 255;
    auto b = (cl.blue() + 128) % 255;
    auto a = cl.alpha();

    return QColor(r, g, b, a);

}

void CSSharedComboBox::initMember()
{
    _pressedProgrssBar = false;
    _pageMaxCount = 6;
    _curIndex = 0;
    _tmpCurIndex = 0;
    _itemHeight = 20;
    _offsetY = 0;
    _tmpOffsetY = _offsetY;
    _pressedY = 0;
    _contentMode = TextOnly;
    _sizeIcon = QSize(20, 20);
    _bgColor = QColor(0, 0, 0, 150);
    _color = Qt::white;
}

void CSSharedComboBox::initUI()
{
    // Set attribute
    resize(100, 30);
    setWindowFlag(Qt::Popup);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);
}

}   // cs
