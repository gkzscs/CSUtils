<<<<<<< HEAD
#ifndef CSFormCard_H
#define CSFormCard_H

#include "cswgtcontainer.h"



namespace cs
{   // Start of namespace `cs`

class CSVBoxLayout;

class CSUTILS_EXPORT CSFormCard : public CSWidget
=======
#ifndef CSFORMCARD_H
#define CSFORMCARD_H

#include "Control/cswidget.h"


namespace cs
{

class CSFormCard : public CSWidget
>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013
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
<<<<<<< HEAD

protected:
    CSVBoxLayout *_vl;
    QLabel *_labTitle;

};

}   // End of namespace `cs`

#endif // CSFormCard_H
=======
    virtual void initSignalSlot() override;

protected:
    QLabel *_labTitle;
    CSVBoxLayout *_vl;

};

}

#endif // CSFORMCARD_H
>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013
