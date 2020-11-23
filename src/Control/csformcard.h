#ifndef CSFormCard_H
#define CSFormCard_H

#include "cswgtcontainer.h"



namespace cs
{   // Start of namespace `cs`

class CSVBoxLayout;

class CSUTILS_EXPORT CSFormCard : public CSWidget
{
    Q_OBJECT

public:
    CSFormCard(QWidget *parent = nullptr);
    virtual ~CSFormCard() override;

    void setTitle(const QString &title);
    QString title() const;

protected:
    virtual void initMember() override;
    virtual void initUI() override;

protected:
    CSVBoxLayout *_vl;
    QLabel *_labTitle;

};

}   // End of namespace `cs`

#endif // CSFormCard_H
