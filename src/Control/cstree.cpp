#include "cstree.h"
#include "cstreeitem.h"


namespace cs
{

CSTree::CSTree(QWidget *parent)
    : cs::CSWidget(parent)
{
    initMember();
    initUI();
}

CSTree::~CSTree()
{
    DELETE_Q_CONTAINER(_listTopLevelItems);
}

/**
 * @brief CSTree::setSpace
 * @param n
 */
void CSTree::setSpace(int n)
{
    dynamic_cast<cs::CSVBoxLayout *>(_layout)->setSpace(n);
}

void CSTree::addTopLevelItem(CSTreeItem *item)
{
    if (!item) return;
    if (_listTopLevelItems.contains(item)) _listTopLevelItems.removeAll(item);

    item->_parent = nullptr;
    _listTopLevelItems.append(item);
    refresh();
}

bool CSTree::insertTopLevelItem(int idx, CSTreeItem *item)
{
    if (!item) return false;
    if (_listTopLevelItems.contains(item)) _listTopLevelItems.removeAll(item);

    if (idx <= 0) _listTopLevelItems.prepend(item);
    if (idx >= _listTopLevelItems.size()) _listTopLevelItems.append(item);

    item->_parent = nullptr;
    _listTopLevelItems.insert(idx, item);
    refresh();
    return true;
}

bool CSTree::removeTopLevelItem(CSTreeItem *item)
{
    if (!item) return false;

    bool res = _listTopLevelItems.removeAll(item);
    refresh();

    return res;
}

bool CSTree::removeTopLevelItem(int idx)
{
    auto item = topLevelItem(idx);
    return removeTopLevelItem(item);
}

void CSTree::clear()
{
    _layout->clear();

    DELETE_Q_CONTAINER(_listTopLevelItems);
}

/**
 * @brief CSTree::space
 * @return
 */
int CSTree::space() const
{
    return dynamic_cast<cs::CSVBoxLayout *>(_layout)->space();
}

bool CSTree::empty() const
{
    return (_listTopLevelItems.size() == 0);
}

int CSTree::indexOfTopLevelItem(CSTreeItem *item) const
{
    if (!item) return -1;
    return _listTopLevelItems.indexOf(item);
}

int CSTree::topLevelItemCount() const
{
    return _listTopLevelItems.size();
}

CSTreeItem *CSTree::itemAt(const QPoint &pos) const
{
    auto kid = childAt(pos);
    while (kid)
    {
        auto item = dynamic_cast<CSTreeItem *>(kid);
        if (item) return item;

        kid = kid->parentWidget();
    }

    return nullptr;
}

CSTreeItem *CSTree::topLevelItem(int idx) const
{
    if (idx < 0 || idx >= _listTopLevelItems.size()) return nullptr;
    return _listTopLevelItems.at(idx);
}

/**
 * @brief Return all top level items
 * @return
 */
QList<CSTreeItem *> CSTree::topLevelItems() const
{
    return _listTopLevelItems;
}

/**
 * @brief Get selected top level items
 * @return
 */
QList<CSTreeItem *> CSTree::selectedTopLevelItems() const
{
    QList<CSTreeItem *> listItems;

    for (auto item : _listTopLevelItems)
    {
        if (!item || !item->selected()) continue;
        listItems.append(item);
    }

    return listItems;
}

/**
 * @brief Get all items those are selected in this tree
 * @return
 */
QList<CSTreeItem *> CSTree::selectedItems() const
{
    QList<CSTreeItem *> listItems;

    for (auto item : _listTopLevelItems)
    {
        if (!item) continue;

        auto listSubItems = item->selectedChildren();
        listItems.append(listSubItems);
    }

    return listItems;
}

/**
 * @brief Refresh ui, adjust the layouot
 */
void CSTree::refresh()
{
    // Clear
    _layout->clear();

    // Reset
    for (auto item : _listTopLevelItems)
    {
        _layout->add(item);
    }
}

void CSTree::initMember()
{
    _layout = new CSVBoxLayout(this);
}

void CSTree::initUI()
{
    // Set attributes
    resize(200, 200);

    // Set layout
    setSpace(0);
}

}   // `cs`
