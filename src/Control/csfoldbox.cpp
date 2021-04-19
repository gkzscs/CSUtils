#include "csfoldbox.h"
#include "Layout/csvboxlayout.h"


namespace cs
{

CSFoldBox::CSFoldBox(QWidget *parent)
    : cs::CSWidget(parent)
{
    initMember();
    initUI();
}

void CSFoldBox::setFold(bool flag)
{
    if (flag) _vl->remove(_body);
    else _vl->add(_body);

    _fold = flag;
    emit foldChangeSignal(flag);
//    emit CSAppEvent::instance()->foldChangeSignal(this, this, flag);
}

void CSFoldBox::setHead(QWidget *head)
{
    _vl->remove(_head);
    _head = head;
    if(head) head->setObjectName("head");
    _vl->add(head);
}

void CSFoldBox::setBody(QWidget *body)
{
    _vl->remove(_body);
    _body = body;
    if (body) body->setObjectName("body");
    _vl->add(body);
}

bool CSFoldBox::isFold() const
{
    return _fold;
}

QWidget *CSFoldBox::head() const
{
    return _head;
}

QWidget *CSFoldBox::body() const
{
    return _body;
}

void CSFoldBox::initMember()
{
    _fold = false;
    _head = nullptr;
    _body = nullptr;
    _vl = new cs::CSVBoxLayout(this);
    _layout = _vl;
}

void CSFoldBox::initUI()
{
    resize(300, 200);

    // Set layout
    _vl->setSpace(0);
}

void CSFoldBox::mousePressEvent(QMouseEvent *e)
{
    auto pos = e->pos();

    if (_head->geometry().contains(pos))
    {
        setFold(!_fold);
    }
}

}   // End of `cs`


