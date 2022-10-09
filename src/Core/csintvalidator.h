#ifndef CSINTVALIDATOR_H
#define CSINTVALIDATOR_H

#include <QIntValidator>


namespace cs
{

class CSUTILS_EXPORT CSIntValidator : public QIntValidator
{
public:
    CSIntValidator(QObject *parent = nullptr);
    CSIntValidator(int bottom, int top, QObject *parent = nullptr);

    QValidator::State validate(QString &input, int &) const override;

};

}   // cs

#endif // CSINTVALIDATOR_H
