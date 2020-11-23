#ifndef FORMCARD_H
#define FORMCARD_H

#include "wgtcontainer.h"



namespace cs
{   // Start of namespace `cs`

class VBoxLayout;

class CSUTILS_EXPORT FormCard : public CSWidget
{
    Q_OBJECT

public:
    FormCard(QWidget *parent = nullptr);
    virtual ~FormCard() override;

    void setTitle(const QString &title);
    QString title() const;

protected:
    virtual void initMember() override;
    virtual void initUI() override;

protected:
    VBoxLayout *_vl;
    QLabel *_labTitle;

};

}   // End of namespace `cs`

#endif // FORMCARD_H
