#ifndef CSUTILS_H
#define CSUTILS_H


#define UNIQUE(name)    \
    QSharedMemory sm(name);   \
    if (sm.attach()) return -1; \
    sm.create(1)

#include <QObject>
#include <QColor>
#include "csutils_global.h"


class QLayout;
class QLabel;

class CSUTILS_EXPORT CSUtils : public QObject
{
    Q_OBJECT

public:
    static void setColor(QWidget *wgt, const QColor &bgColor, const QColor &txtColor = nullptr);
    static void setStyleSheet(QWidget *wgt, const QString &filePath);
    static void enableStyleSheet(QWidget *wgt);
    static void updateStyleSheet(QWidget *wgt);
    static QString convert2Html(const QString &str);
    static void clearLayout(QLayout *layout);
    static int calcProperValue(int oldValue, const QSize &originSize, const QSize &nowSize, bool horizontal = true);
    static QSize calcProperValue(QSize oldSize, const QSize &originSize, const QSize &nowSize);
    static QRect calcProperValue(QRect oldRect, const QSize &originSize, const QSize &nowSize);
    static void setScaledPixmap(QLabel *lab, const QPixmap &pix, Qt::AspectRatioMode aspectMode = Qt::KeepAspectRatio);
    void setScaledSvg(QLabel *lab, const QString &svgPath);
    static QPixmap converSvg2Pixmap(const QString &svgPath, const QSize &pixSize);
    static QPixmap changeImageColor(const QPixmap &pixSource, const QColor &originColor, const QColor &dstColor);
    static QPixmap changeImageAlpha(const QPixmap &pixSource, int alpha);
    static bool keyIsNumber(int key);
    static bool keyIsAlphabet(int key);

};


#endif // CSUTILS_H
