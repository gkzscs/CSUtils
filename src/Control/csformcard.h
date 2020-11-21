#ifndef CSFORMCARD_H
#define CSFORMCARD_H

#include "Control/cswidget.h"


namespace cs
{

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
    virtual void initSignalSlot() override;

protected:
    QLabel *_labTitle;
    CSVBoxLayout *_vl;

};

}

#endif // CSFORMCARD_H
