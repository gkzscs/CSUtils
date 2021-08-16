#ifndef CSTREEITEM_H
#define CSTREEITEM_H

#include "Control/Base/cswidget.h"


namespace cs
{

class CSTree;

class CSUTILS_EXPORT CSTreeItem : public cs::CSWidget
{
    Q_OBJECT
    Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)

    friend class CSTree;

public:
    CSTreeItem();
    CSTreeItem(CSTree *parent);
    CSTreeItem(CSTreeItem *parent);
    ~CSTreeItem() override = 0;

    void setExpanded(bool flag);
    void setSelected(bool flag);
    void setExpandIcons(const QIcon &iconExpanded, const QIcon &iconUnexpanded);
    void setIndent(int n);
    void setSpace(int n);
    void addChild(CSTreeItem *child);
    void addChildren(const QList<CSTreeItem *> &listChildren);
    bool insertChild(int idx, CSTreeItem *child);
    bool insertChildren(int idx, const QList<CSTreeItem *> &listChildren);
    bool removeChild(CSTreeItem *child);
    bool removeChild(int idx);
    void removeChildren();
    void clear();

    int space() const;
    bool expanded() const;
    bool selected() const;
    bool empty() const;
    int childCount() const;
    int indexOfChild(CSTreeItem *child);
    const CSTreeItem *root() const;
    CSTreeItem *parent() const;
    CSTreeItem *child(int idx) const;
    QList<CSTreeItem *> children() const;
    QList<CSTreeItem *> selectedChildren() const;

protected:
    void resizeEvent(QResizeEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;

protected:
    virtual void updateStyle();
    void refresh();
    void updateExpandButton();

    void setOriginSize(const QSize &s);

private:
    void initMember();
    void initUI();
    void initSignalSlot();

    void initIcons();

signals:
    void selectedChanged(bool flag);
    void expandedChanged(bool flag);

protected slots:
    void btnExpandClickSlot();

protected:
    cs::CSWidget *_wgtContainer;    // You should put all owner controls into this widget
    QToolButton *_btnExpand;        // A button to determine whether expand children items
    QPair<QIcon, QIcon> _pairExpandIcons;   // Icons shown on expand button

    bool _expanded;
    bool _selected;
    QSize _sizeOrigin;
    CSTreeItem *_parent;
    QList<CSTreeItem *> _listChildren;

};

}   // `cs`

#endif // CSTREEITEM_H
