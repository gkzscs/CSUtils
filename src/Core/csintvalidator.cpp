#include "csintvalidator.h"


namespace cs
{

CSIntValidator::CSIntValidator(QObject *parent)
    : QIntValidator(parent)
{
    // Do nothing
}

CSIntValidator::CSIntValidator(int bottom, int top, QObject *parent)
    : QIntValidator(bottom, top, parent)
{
    // Do nothing
}

QValidator::State CSIntValidator::validate(QString &input, int &) const
{
    bool ok = false;
    const auto b = bottom();
    const auto t = top();
    const int num = input.toInt(&ok);
    const QRegExp empty(QString::fromLatin1("-?\\.?"));

    if (empty.exactMatch(input)) return Intermediate;
    if (!ok) return Invalid;
    if (num < b || num > t) return Invalid;
    if (input.contains(' ')) return Invalid;

    return Acceptable;
}


}   // cs
