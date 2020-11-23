#include "csformcard.h"
#include "Layout/csvboxlayout.h"


namespace cs
{   // Start of namespace `cs`

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
    _labTitle->setObjectName("form_card_title");
}

void CSFormCard::initUI()
{
    setHidden(false);
    resize(330, 300);
    setContentsMargins(30, 10, 10, 10);

    const auto margins = contentsMargins();
    const int w = width() - margins.left() - margins.right();
    const int h = 20;

    _labTitle->setGeometry(margins.left(), margins.top(), w, h );
    _vl->setMargins(margins.left(), 50, margins.right(), margins.bottom());
}

}   // End of namespace `cs`


