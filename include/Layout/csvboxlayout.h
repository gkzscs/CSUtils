<<<<<<< HEAD
#ifndef CSVBoxLayout_H
#define CSVBoxLayout_H
=======
#ifndef CSVBOXLAYOUT_H
#define CSVBOXLAYOUT_H
>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013

#include "Layout/cslayout.h"


namespace cs
<<<<<<< HEAD
{   // Start of namespace `cs`

class CSUTILS_EXPORT CSVBoxLayout : public CSLayout
{
public:
    CSVBoxLayout(CSWidget *wgt = nullptr);

    void setSpace(int n);
    int space() const;

    virtual void changeSize(const QSize &newSize, const QSize &oldSize) override;

protected:
    virtual void init() override;

    virtual void resetLayout() override;
=======
{

class CSUTILS_EXPORT CSVBoxLayout : public CSLayout
{
    Q_OBJECT

public:
    CSVBoxLayout(CSWidget *wgt = nullptr);

    void setSpace(int space);
    int space() const;

protected:
    virtual void resetLayout() override;

protected:
    virtual void initMember() override;

protected slots:
    virtual void resizeSlot(QObject *s, QResizeEvent *e) override;
>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013

protected:
    int _space;

};

<<<<<<< HEAD
}   // End of namespace `cs`

#endif // CSVBoxLayout_H
=======
}

#endif // CSVBOXLAYOUT_H
>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013
