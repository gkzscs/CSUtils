#ifndef CSTREE_H
#define CSTREE_H

#include "Control/Base/cswidget.h"


namespace cs
{

class CSTreeItem;

class CSUTILS_EXPORT CSTree : public cs::CSWidget
{
    Q_OBJECT

public:
    CSTree(QWidget *parent = nullptr);
    ~CSTree() override;

    void setSpace(int n);
    void addTopLevelItem(CSTreeItem *item);
    void addTopLevelItems(const QList<CSTreeItem *> &listItems);
    bool insertTopLevelItem(int idx, CSTreeItem *item);
    bool insertTopLevelItems(int idx, const QList<CSTreeItem *> &listItems);
    bool removeTopLevelItem(CSTreeItem *item);
    bool removeTopLevelItem(int idx);
    void clear();

    int space() const;
    bool empty() const;
    int indexOfTopLevelItem(CSTreeItem *item) const;
    int topLevelItemCount() const;
    CSTreeItem *itemAt(const QPoint &pos) const;
    CSTreeItem *topLevelItem(int idx) const;
    QList<CSTreeItem *> topLevelItems() const;
    QList<CSTreeItem *> selectedTopLevelItems() const;
    QList<CSTreeItem *> selectedItems() const;

protected:
    void refresh();

private:
    void initMember();
    void initUI();

protected:
    QList<CSTreeItem *> _listTopLevelItems;

};

}   // `cs`

#endif // CSTREE_H
