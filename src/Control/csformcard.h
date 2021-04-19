#ifndef CSFORMCARD_H
#define CSFORMCARD_H

#include "Control/cswidget.h"


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
    void initMember();
    void initUI();

protected:
    QLabel *_labTitle;

};

}   // End of namespace `cs`


#endif // CSFORMCARD_H
