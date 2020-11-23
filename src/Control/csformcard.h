#ifndef CSFORMCARD_H
#define CSFORMCARD_H

#include "Control/cswidget.h"

namespace cs
{   // Start of namespace `cs`

class CSVBoxLayout;

class CSFormCard : public CSWidget
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


#endif // CSFORMCARD_H
