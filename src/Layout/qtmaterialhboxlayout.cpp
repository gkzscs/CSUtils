#include "qtmaterialhboxlayout.h"
#include "qtmaterialhboxlayout_p.h"

QtMaterialHBoxLayoutPrivate::QtMaterialHBoxLayoutPrivate(QtMaterialHBoxLayout *q)
    : q_ptr(q)
{

}

QtMaterialHBoxLayoutPrivate::~QtMaterialHBoxLayoutPrivate()
{

}

void QtMaterialHBoxLayoutPrivate::init()
{
    Q_Q(QtMaterialHBoxLayout);

    q_ptr->setSpacing(0);
    q_ptr->setMargin(0);
}

QtMaterialHBoxLayout::QtMaterialHBoxLayout(QWidget *parent)
    : QHBoxLayout(parent)
    , d_ptr(new QtMaterialHBoxLayoutPrivate(this))
{
    d_func()->init();
}

QtMaterialHBoxLayout::~QtMaterialHBoxLayout()
{

}

void QtMaterialHBoxLayout::setSpace(int space)
{
    Q_D(QtMaterialHBoxLayout);

    d_ptr->space = space;

    QHBoxLayout::setSpacing(space);
}

int QtMaterialHBoxLayout::space()
{
    Q_D(QtMaterialHBoxLayout);

    return d_ptr->space;
}
