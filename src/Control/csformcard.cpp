#include "csformcard.h"
#include "Layout/csvboxlayout.h"


namespace cs
{   // Start of namespace `cs`

CSFormCard::CSFormCard(QWidget *parent)
    : CSWidget(parent)
{
    initMember();
    initUI();
}

CSFormCard::~CSFormCard()
{
    _labTitle->deleteLater();
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
    _layout = new CSVBoxLayout(this);

    // Set object name
    _labTitle->setObjectName("card_title");
}

void CSFormCard::initUI()
{
    resize(330, 300);
    setContentsMargins(20, 10, 10, 10);

    const auto margins = contentsMargins();
    const int w = width() - margins.left() - margins.right();
    const int h = 20;

    _labTitle->setGeometry(margins.left(), margins.top(), w, h );
    _layout->setMargins(margins.left(), 50, margins.right(), margins.bottom());
}

}   // End of namespace `cs`



