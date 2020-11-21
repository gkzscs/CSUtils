#include "csformcard.h"
#include "Layout/csvboxlayout.h"


namespace cs
{

CSFormCard::CSFormCard(QWidget *parent)
    : CSWidget(parent)
{
    init();
}

CSFormCard::~CSFormCard()
{
    _labTitle->deleteLater();
    _vl = nullptr;
}

void CSFormCard::setTitle(const QString &title)
{
    _labTitle->setText(title);
}

QString CSFormCard::title() const
{
    return _labTitle->text();
}

void CSFormCard::initMember()
{
    _labTitle = new QLabel(this);
    _vl = new CSVBoxLayout(this);
    _layout = _vl;

    // Set object name
    _labTitle->setObjectName("card_title");
}

void CSFormCard::initUI()
{
    resize(330, 300);
    setHidden(false);

    // Set attribute
    _labTitle->setContentsMargins(20, 20, 10, 10);
    _labTitle->setGeometry(0, 0, width(), 40);
    _labTitle->setScaledContents(true);
    _vl->setMargins(10, 10, 10, 10);
}

void CSFormCard::initSignalSlot()
{

}

}
