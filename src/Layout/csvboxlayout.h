#ifndef CSVBOXLAYOUT_H
#define CSVBOXLAYOUT_H

#include "Layout/cslayout.h"


namespace cs
{   // Start of namespace `cs`

class CSUTILS_EXPORT CSVBoxLayout : public CSLayout
{
    Q_OBJECT

public:
    CSVBoxLayout(CSWidget *wgt = nullptr);

    void setSpace(int space);
    int space() const;

protected:
    void resetLayout() override;

protected:
    void initMember();

protected slots:
    void resizeSlot(QObject *s, QResizeEvent *e) override;

protected:
    int _space;

};

}   // End of namespace `cs`


#endif // CSVBOXLAYOUT_H
