#ifndef CSContainer_H
#define CSContainer_H

#include <QObject>
#include <QTime>


namespace cs
{   // Start of namespace `cs`

template <typename T>
class CSContainer : public QObject
{
public:
    CSContainer();
    virtual ~CSContainer() override;

    bool add(T *item);
    bool insert(int idx, T *item);
    bool remove(T *item);
    bool remove(int idx);
    bool replace(T *oldItem, T *newItem);
    bool replace(int idx, T *item);
    bool move(int oldIdx, int newIdx);
    bool swap(int idx1, int idx2);
    T *at(int idx) const;
    int indexOf(T *item) const;
    void clear();

    int count() const;
    bool contains(T *item) const;
    bool isEmpty() const;
    QList<T *> allItems() const;

protected:
    virtual void refresh();
    virtual void actualRefresh();
    virtual void dealAdd(T *item);
    virtual void dealRemove(T *item);

protected:
    QList<T *> _listItems;
    QTime _lastRefresh;
    bool _flag;

};

}   // End of namespace `cs`


// Include cpp
#define CSCONTAINER_IMPL_HPP
#include "Core/cscontainer_impl.hpp"

#endif // CSContainer_H
