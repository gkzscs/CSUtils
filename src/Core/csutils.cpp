#include "csutils.h"
#include <QWidget>
#include <QLabel>
#include <QFile>
#include <QStyleOption>
#include <QPainter>
#include <QLayout>
#include <QStyle>
#include <QSvgRenderer>
#include <QDebug>


namespace cs
{   // Start of namespace `cs`

void CSUtils::setColor(QWidget *wgt, const QColor &bgColor, const QColor &txtColor)
{
    if (!wgt) return;
    wgt->setAutoFillBackground(true);

    QPalette pal = wgt->palette();
    pal.setColor(QPalette::Window, bgColor);
    pal.setColor(QPalette::WindowText, txtColor);
    pal.setColor(QPalette::Background, bgColor);
    pal.setColor(QPalette::Base, bgColor);
    wgt->setPalette(pal);
}

void CSUtils::setStyleSheet(QWidget *wgt, const QString &filePath)
{
    if (!wgt) return;

    QFile file(filePath);
    bool res = file.open(QIODevice::ReadOnly);
    if (!res)
    {
//        qDebug() << "Error to open file:" << filePath;
        return;
    }

    const QString style = file.readAll();
    wgt->setStyleSheet(style);

    file.close();
}

void CSUtils::enableStyleSheet(QWidget *wgt)
{
    if (!wgt) return;

    QStyleOption opt;
    opt.init(wgt);
    QPainter p(wgt);
    wgt->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, wgt);
}

void CSUtils::updateStyleSheet(QWidget *wgt)
{
    // To make style sheet updates, must do these by hands
    wgt->style()->unpolish(wgt);
    wgt->style()->polish(wgt);
}

QString CSUtils::convert2Html(const QString &str)
{
    QString html = "<p style='line-height: %1px'>" + str + "</p>";
    html = html.replace("\n", "<br>");
    return html;
}

void CSUtils::clearLayout(QLayout *layout)
{
    QLayoutItem *item = nullptr;
    while ((item = layout->itemAt(0)) != nullptr)
    {
        if (item->widget()) item->widget()->setParent(nullptr);
        layout->removeItem(item);
    }
}

int CSUtils::calcProperValue(int oldValue, const QSize &originSize, const QSize &nowSize, bool horizontal)
{
    int newValue = oldValue;
    double f = 1.0;

    if (horizontal)
    {
        f = static_cast<double>(nowSize.width()) / originSize.width();
    }
    else
    {
        f = static_cast<double>(nowSize.height()) / originSize.height();
    }
    newValue = static_cast<int>(oldValue * f);

    return newValue;
}

QSize CSUtils::calcProperValue(QSize oldSize, const QSize &originSize, const QSize &nowSize)
{
    QSize newSize = oldSize;
    double fw = static_cast<double>(nowSize.width()) / originSize.width();
    double fh = static_cast<double>(nowSize.height()) / originSize.height();

    newSize.setWidth(static_cast<int>(oldSize.width() * fw));
    newSize.setHeight(static_cast<int>(oldSize.height() * fh));

    return newSize;
}

QRect CSUtils::calcProperValue(QRect oldRect, const QSize &originSize, const QSize &nowSize)
{
    QRect newRect = oldRect;
    double fw = static_cast<double>(nowSize.width()) / originSize.width();
    double fh = static_cast<double>(nowSize.height()) / originSize.height();

    newRect.setX(static_cast<int>(oldRect.x() * fw));
    newRect.setY(static_cast<int>(oldRect.y() * fh));
    newRect.setWidth(static_cast<int>(oldRect.width() * fw));
    newRect.setHeight(static_cast<int>(oldRect.height() * fh));

    return newRect;
}

void CSUtils::setScaledPixmap(QLabel *lab, const QPixmap &pix, Qt::AspectRatioMode aspectMode)
{
    if (!lab || pix.isNull()) return;
    lab->setPixmap(pix.scaled(lab->size(), aspectMode, Qt::SmoothTransformation));
}

void CSUtils::setScaledSvg(QLabel *lab, const QString &svgPath)
{
    // Create svg renderer
    QSvgRenderer *svg = new QSvgRenderer();
    svg->load(svgPath);
    if (!lab || !svg->isValid()) return;

    // Calculate the maximum factor to scale
    QSize sizeLab = lab->size();
    QSize sizeSvg = svg->defaultSize();
    double fw = static_cast<double>(sizeLab.width()) / sizeSvg.width();
    double fh = static_cast<double>(sizeLab.height()) / sizeSvg.height();
    double f = (fw < fh ? fw : fh);

    sizeSvg *= f;
    QRect rect = QRect(sizeLab.width()/2-sizeSvg.width()/2, sizeLab.height()/2-sizeSvg.height()/2,
                       sizeSvg.width(), sizeSvg.height());

    // Set pixmap
    QPixmap pix(sizeLab);
    QPainter p(&pix);
    pix.fill(Qt::transparent);
    svg->render(&p, rect);

    lab->setPixmap(pix);
}

// Used for load svg picture
QPixmap CSUtils::converSvg2Pixmap(const QString &svgPath, const QSize &pixSize)
{
    QSvgRenderer* svgRender = new QSvgRenderer();
    svgRender->load(svgPath);

    QPixmap pixmap(pixSize);
    // Set transparent background
    pixmap.fill(Qt::transparent);
    QPainter p(&pixmap);
    svgRender->render(&p);

    return pixmap;
}

QPixmap CSUtils::changeImageColor(const QPixmap &pixSource, const QColor &srcColor, const QColor &dstColor)
{
    QImage img = pixSource.toImage();

    for (int row = 0; row < img.width(); ++row)
    {
        for (int col = 0; col < img.height(); ++col)
        {
            if (img.pixelColor(row, col) != srcColor) continue;
            img.setPixelColor(row, col, dstColor);
        }
    }

    return QPixmap::fromImage(img);
}

QPixmap CSUtils::changeImageAlpha(const QPixmap &pixSource, int alpha)
{
    QImage img = pixSource.toImage();

    for (int row = 0; row < img.width(); ++row)
    {
        for (int col = 0; col < img.height(); ++col)
        {
            QColor color = img.pixelColor(row, col);
            if (color.alpha() != 0) color.setAlpha(alpha);
            img.setPixelColor(row, col, color);
        }
    }

    return QPixmap::fromImage(img);
}

bool CSUtils::keyIsNumber(int key)
{
    bool res = (key >= 0x30 && key <= 0x39);
    return res;
}

bool CSUtils::keyIsAlphabet(int key)
{
    bool res = (key >= 0x41 && key <= 0x5a);
    return res;
}

}   // End of namespace `cs`

