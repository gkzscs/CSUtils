#ifndef QTMATERIALHBOXLAYOUT_P_H
#define QTMATERIALHBOXLAYOUT_P_H

class QtMaterialHBoxLayoutPrivate
{
    Q_DISABLE_COPY(QtMaterialHBoxLayoutPrivate)
    Q_DECLARE_PUBLIC(QtMaterialHBoxLayout)

public:
    explicit QtMaterialHBoxLayoutPrivate(QtMaterialHBoxLayout *q);
    ~QtMaterialHBoxLayoutPrivate();

    void init();

    QtMaterialHBoxLayout *q_ptr;
    int space;
};

#endif // QTMATERIALHBOXLAYOUT_P_H
