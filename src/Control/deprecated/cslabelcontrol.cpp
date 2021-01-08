#include "cslabelcontrol.h"


namespace cs
{   // Start of namespace `cs`

template <typename T>
CSLabelControl<T>::CSLabelControl(QWidget *parent)
    : CSWidget(parent)
{
    init();
}

template <typename T>
CSLabelControl<T>::~CSLabelControl()
{
    if (_lab) _lab->deleteLater();
    if (_control) _control->deleteLater();
}

template <typename T>
void CSLabelControl<T>::setWidthFactor(double f)
{
    if (f < 0) f = 0;
    else if (f > 1) f = 1;

    _factor = f;
    resizeEvent(nullptr);
}

template <typename T>
void CSLabelControl<T>::setSpacing(int n)
{
    _space = n;
}

template <typename T>
double CSLabelControl<T>::getWidthFactor() const
{
    return _factor;
}

template <typename T>
int CSLabelControl<T>::getSpacing() const
{
    return _space;
}

template <typename T>
QLabel *CSLabelControl<T>::label() const
{
    return _lab;
}

template <typename T>
T *CSLabelControl<T>::control() const
{
    return _control;
}

template <typename T>
void CSLabelControl<T>::initMember()
{
    _lab = new QLabel(this);
    _control = new T(this);
    _space = 5;
    _factor = 0.5;
}

template <typename T>
void CSLabelControl<T>::initUI()
{
    resize(100, 30);

    _lab->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
}

template <typename T>
void CSLabelControl<T>::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    int labW = static_cast<int>((width() - _space) *_factor);

    _lab->setGeometry(0, 0, labW, height());
    _control->setGeometry(labW+_space, 0, width()-labW-_space, height());
}


/********************************* Explicit instantiate **************************************/
template class CSLabelControl<QComboBox>;
template class CSLabelControl<QLabel>;
template class CSLabelControl<QLineEdit>;


}   // End of namespace `cs`

