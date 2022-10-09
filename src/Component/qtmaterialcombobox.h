#ifndef QTMATERIALCOMBOBOX_H
#define QTMATERIALCOMBOBOX_H

#include "csutils_global.h"

#include <QComboBox>

class QtMaterialComboBoxPrivate;

class CSUTILS_EXPORT QtMaterialComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit QtMaterialComboBox(QWidget *parent = nullptr);
    virtual ~QtMaterialComboBox();

    void initUI();

protected:
    const QScopedPointer<QtMaterialComboBoxPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QtMaterialComboBox)
    Q_DECLARE_PRIVATE(QtMaterialComboBox)
};

#endif // QTMATERIALCOMBOBOX_H
