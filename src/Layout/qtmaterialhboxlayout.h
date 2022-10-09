#ifndef QTMATERIALHBOXLAYOUT_H
#define QTMATERIALHBOXLAYOUT_H

#include "csutils_global.h"

#include <QHBoxLayout>

class QtMaterialHBoxLayoutPrivate;

class CSUTILS_EXPORT QtMaterialHBoxLayout : public QHBoxLayout
{
    Q_OBJECT

    Q_PROPERTY(int space WRITE setSpace READ space)

public:
    explicit QtMaterialHBoxLayout(QWidget *parent = nullptr);
    ~QtMaterialHBoxLayout();

    void setSpace(int space);
    int space();

protected:
    const QScopedPointer<QtMaterialHBoxLayoutPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialHBoxLayout)
    Q_DECLARE_PRIVATE(QtMaterialHBoxLayout)
};

#endif // QTMATERIALHBOXLAYOUT_H
