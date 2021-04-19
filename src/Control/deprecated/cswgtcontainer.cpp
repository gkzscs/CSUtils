#include "cswgtcontainer.h"


namespace cs
{   // Start of namespace `cs`

template <typename T>
CSWgtContainer<T>::CSWgtContainer(QWidget *parent)
    : CSWidget(parent)
{
    init();
}

template <typename T>
CSWgtContainer<T>::~CSWgtContainer()
{
    for (auto item : _listItems) dealAdd(item);

    qDeleteAll(_listItems);
    _listItems.clear();
}

template <typename T>
bool CSWgtContainer<T>::add(T *item)
{
    if (!item) return false;
    if (_listItems.contains(item)) _listItems.removeAll(item);

    _listItems.append(item);
    dealAdd(item);
    refresh();

    return true;
}

template <typename T>
bool CSWgtContainer<T>::insert(int idx, T *item)
{
    if (!item) return false;
    if (_listItems.contains(item)) _listItems.removeAll(item);

    if (idx <= 0) _listItems.prepend(item);
    else if (idx >= _listItems.size()) _listItems.append(item);
    else _listItems.insert(idx, item);

    dealAdd(item);
    refresh();
    return true;
}

template <typename T>
bool CSWgtContainer<T>::remove(T *item)
{
    if (!item) return false;
    int res = _listItems.removeAll(item);

    dealRemove(item);
    refresh();
    return res;
}

template <typename T>
bool CSWgtContainer<T>::remove(int idx)
{
    if (idx < 0 || idx >= _listItems.size()) return false;
    auto item = _listItems.at(idx);

    return remove(item);
}

template <typename T>
bool CSWgtContainer<T>::replace(T *oldItem, T *newItem)
{
    if (!oldItem || !newItem || !_listItems.contains(oldItem)) return false;

    int idx = _listItems.indexOf(oldItem);
    _listItems.insert(idx, newItem);
    _listItems.removeAll(oldItem);

    dealRemove(oldItem);
    dealAdd(newItem);
    refresh();
    return true;
}

template <typename T>
bool CSWgtContainer<T>::replace(int idx, T *item)
{
    if (idx < 0 || idx >= _listItems.size() || !item) return false;
    _listItems.removeAt(idx);
    _listItems.insert(idx, item);

    dealRemove(_listItems.at(idx));
    dealAdd(item);
    refresh();
    return true;
}

template <typename T>
bool CSWgtContainer<T>::move(int oldIdx, int newIdx)
{
    if (oldIdx < 0 || oldIdx >= _listItems.size()) return false;
    if (newIdx < 0 || newIdx >= _listItems.size()) return false;
    _listItems.move(oldIdx, newIdx);

    refresh();
    return true;
}

template <typename T>
bool CSWgtContainer<T>::swap(int idx1, int idx2)
{
    if (idx1 < 0 || idx1 >= _listItems.size()) return false;
    if (idx2 < 0 || idx2 >= _listItems.size()) return false;
    _listItems.swap(idx1, idx2);

    refresh();
    return true;
}

template <typename T>
T *CSWgtContainer<T>::find(int idx) const
{
    if (idx < 0 || idx >= _listItems.size()) return nullptr;
    return _listItems.at(idx);
}

template <typename T>
int CSWgtContainer<T>::indexOf(T *item) const
{
    return _listItems.indexOf(item);
}

template <typename T>
void CSWgtContainer<T>::clear()
{
    for (auto item : _listItems) dealRemove(item);

    _listItems.clear();
    refresh();
}

template <typename T>
int CSWgtContainer<T>::count() const
{
    return _listItems.count();
}

template <typename T>
bool CSWgtContainer<T>::isEmpty() const
{
    return _listItems.empty();
}

template <typename T>
QList<T *> CSWgtContainer<T>::allItems() const
{
    return _listItems;
}

template <typename T>
void CSWgtContainer<T>::init()
{
    _flag = false;
}

template <typename T>
void CSWgtContainer<T>::refresh()
{
    const int duration = 20;

    // Control the fps of refresh
    if (!_flag)
    {
        _flag = true;
        _lastRefresh.restart();

        QTimer::singleShot(duration, this, &CSWgtContainer<T>::refresh);
        return;
    }

    if (_lastRefresh.elapsed() < duration) return;

    // Call actual refresh function
    actualRefresh();

    // Reset variables
    _flag = false;
}

template <typename T>
void CSWgtContainer<T>::actualRefresh()
{
    // To do
}

template <typename T>
void CSWgtContainer<T>::dealAdd(T *item)
{
    Q_UNUSED(item)
}

template <typename T>
void CSWgtContainer<T>::dealRemove(T *item)
{
    Q_UNUSED(item)
}

template <typename T>
void CSWgtContainer<T>::clearLayout(QWidget *wgt)
{
    if (!wgt) return;

    // Clear layout
    for (auto kid : wgt->children())
    {
        auto item = qobject_cast<T *>(kid);
        if (!item) continue;
        item->setParent(nullptr);
        item->setHidden(true);
    }
}



/********************************* Explicit instantiate **************************************/
template class CSWgtContainer<QWidget>;


}   // End of namespace `cs`



