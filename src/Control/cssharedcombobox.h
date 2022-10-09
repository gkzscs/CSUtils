#ifndef CSSHAREDCOMBOBOX_H
#define CSSHAREDCOMBOBOX_H

#include "Control/Base/cswidget.h"


namespace cs
{

class CSUTILS_EXPORT CSSharedComboBox : public cs::CSWidget
{
    Q_OBJECT

public:
    enum ContentMode
    {
        IconOnly,
        TextOnly,
        TextBesideIcon
    };

    // Inner struct, used to store information of an item
    struct ItemInfo
    {
        QIcon icon;
        QString text;
        QVariant data;

        explicit ItemInfo(const QIcon &tmpIcon, const QString &tmpText, const QVariant &userData = QVariant())
            : icon(tmpIcon), text(tmpText), data(userData) {}
        explicit ItemInfo(const QIcon &tmpIcon)
            : icon(tmpIcon) {}
        explicit ItemInfo(const QString &tmpText)
            : text(tmpText) {}
    };

public:
    CSSharedComboBox(QWidget *parent = nullptr);
    ~CSSharedComboBox() override;

    void popup(QWidget *wgt = nullptr);

    void addItem(const QString &text, const QVariant &userData = QVariant());
    void addItem(const QIcon &icon, const QString &text, const QVariant &userData = QVariant());
    void addItems(const QStringList &texts);
    void insertItem(int index, const QString &text, const QVariant &userData = QVariant());
    void insertItem(int index, const QIcon &icon, const QString &text, const QVariant &userData = QVariant());
    void insertItems(int index, const QStringList &texts);
    void removeItem(int index);

    void clear();
    void setContentMode(ContentMode md);
    void setBgColor(const QColor &cl);
    void setColor(const QColor &cl);
    void setPageMaxCount(int n);
    void setCurrentIndex(int index);
    void setCurrentText(const QString &text);
    void setIconSize(const QSize &size);
    void setFont(const QFont &f);
    void setItemText(int index, const QString &text);
    void setItemIcon(int index, const QIcon &icon);
    void setItemData(int index, const QVariant &value);

    inline ContentMode contentMode() const { return _contentMode; }
    inline QColor bgColor() const { return _bgColor; }
    inline QColor color() const { return _color; }
    inline QSize iconSize() const { return _sizeIcon; }
    inline int pageMaxCount() const { return _pageMaxCount; }
    inline int count() const { return _listItemInfos.size(); }
    int findText(const QString &text) const;
    int findData(const QVariant &data) const;
    int currentIndex() const;
    QString currentText() const;
    QVariant currentData() const;
    QString itemText(int index) const;
    QIcon itemIcon(int index) const;
    QVariant itemData(int index) const;

protected:
    void paintEvent(QPaintEvent *e) override;
    void showEvent(QShowEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;

protected:
    void drawItems(QPainter &p);
    void drawScrollBar(QPainter &p);
    void drawBorder(QPainter &p);

    void drawItemBackground(int index, QPainter &p);
    void drawItemIcon(int index, QPainter &p);
    void drawItemText(int index, QPainter &p);
    void drawBaseScrollBar(QPainter &p);
    void drawCurrentScrollBar(QPainter &p);

    void updateProperItemHeight();
    void updateProperIconSize();
    void updateProperSize();
    void updateOffsetYByIndex(int offsetIdx);

    int calcFontHeight() const;
    int calcFirstVisibleItemIndex() const;
    int calcIndexOffset(int offsetY) const;
    QRect calcContentRect() const;
    QRect calcItemRect(int idx) const;
    QRect calcItemIconRect(int idx) const;
    QRect calcItemTextRect(int idx) const;
    QRect calcBaseScrollBarRect() const;
    QRect calcCurrentScrollBarRect() const;
    QRect calcBorderRect() const;

    int findItemByPos(int y) const;
    QColor newColor(const QColor  &cl) const;

private:
    void initMember();
    void initUI();

signals:
    void activated(int index);
    void activated(const QString &);
    void currentIndexChanged(int index);
    void currentTextChanged(const QString &);

protected:
    bool _pressedProgrssBar;
    int _pageMaxCount;
    int _tmpCurIndex;
    int _curIndex;
    int _itemHeight;
    int _tmpOffsetY;
    int _offsetY;
    int _pressedY;
    ContentMode _contentMode;
    QSize _sizeIcon;
    QColor _bgColor;
    QColor _color;
    QList<ItemInfo *> _listItemInfos;

};

}   // cs

#endif // CSSHAREDCOMBOBOX_H
