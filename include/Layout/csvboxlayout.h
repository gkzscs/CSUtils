#ifndef CSVBOXLAYOUT_H
#define CSVBOXLAYOUT_H

#include "Layout/cslayout.h"


namespace cs
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

protected:
    int _space;

};

}

#endif // CSVBOXLAYOUT_H
