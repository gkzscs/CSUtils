#ifndef CSContainer_H
#define CSContainer_H

#include <QObject>
#include <QTime>


namespace cs
{   // Start of namespace `cs`

template <typename T>
class CSUTILS_EXPORT CSContainer : public QObject
{
public:
    CSContainer();
    virtual ~CSContainer() override;

    virtual bool add(T *item);
    virtual bool insert(int idx, T *item);
    virtual bool remove(T *item);
    virtual bool remove(int idx);
    virtual bool replace(T *oldItem, T *newItem);
    virtual bool replace(int idx, T *item);
    virtual bool move(int oldIdx, int newIdx);
    virtual bool swap(int idx1, int idx2);
    virtual T *at(int idx) const;
    virtual int indexOf(T *item) const;
    virtual void clear();

    virtual int count() const;
    virtual bool isEmpty() const;
    virtual QList<T *> allItems() const;

protected:
    virtual void init();

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


#endif // CSContainer_H
