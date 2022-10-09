#include "cshudartware.h"


namespace cs
{

// Static variables
static int sFontH = 0;
static double sRatio = 1.0;
static double sPenW = 0.5;
static int scMinFontSize = 7;
static int scMaxFontSize = 20;
static double scMinPenW = 0.5;
static double scMaxPenW = 1.0;
static QFontMetrics sFontMetrics = QFontMetrics(QFont());

static const QSize scOriSize(400, 400);
static const QColor scBgColor(0, 0, 0, 128);
static const QColor scTgtBgColor(188, 188, 188, 128);
static const QColor scTgtForeColor(Qt::gray);
static const QColor scForeColor(Qt::green);
static const QColor scCriticalColor(Qt::red);


CSHudArtWare::CSHudArtWare(QWidget *parent)
    : QWidget(parent)
{
    initMember();
    initUI();
}

CSHudArtWare::~CSHudArtWare()
{
    _timerRefresh->deleteLater();
    _hashTypeFunc.clear();
}

/**
 * @brief CSHudArtWare::setData
 * @param type
 * @param val
 */
void CSHudArtWare::setData(DataType type, const QJsonValue &val)
{
    auto func = _hashTypeFunc.value(type);
    func(this, val.toDouble());
}

/**
 * @brief CSHudArtWare::setFrequency
 * @param freq
 */
void CSHudArtWare::setFrequency(int freq)
{
    _frequency = freq;
    _timerRefresh->setInterval(1000/freq);
}

inline int CSHudArtWare::frequency() const
{
    return _frequency;
}

void CSHudArtWare::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    adjustAttributes();
}

void CSHudArtWare::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    // Use a new way to draw graph
    QPainter sp(this);
    QPixmap pix(size());
    QPainter p(&pix);

    // Draw graph on the pixmap firstly
    {
        scaleCoordinate(p);
        p.setFont(font());

        drawBackground(p);
        drawYaw(p);
        drawPitch(p);
        drawRoll(p);
        drawAirSpeed(p);
        drawHeight(p);
    }

    // Draw graph on current widget
    sp.drawPixmap(0, 0, pix);
}

/*************************************** Initialize *******************************************/
void CSHudArtWare::initMember()
{
    _frequency      = 60;

    _yaw            =   0;
    _pitch          =   0;
    _roll           =   0;
    _airSpeed       =   0;
    _height         =   0;

    _colorBg        =   scBgColor;
    _timerRefresh   =   new QTimer(this);

    // Initialize hash container
    {
        _hashTypeFunc.insert(Yaw, &CSHudArtWare::setYaw);
        _hashTypeFunc.insert(Pitch, &CSHudArtWare::setPitch);
        _hashTypeFunc.insert(Roll, &CSHudArtWare::setRoll);
        _hashTypeFunc.insert(AirSpeed, &CSHudArtWare::setAirSpeed);
        _hashTypeFunc.insert(Height, &CSHudArtWare::setHeight);
    }
}

void CSHudArtWare::initUI()
{
    // Set attribute
    resize(scOriSize);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(false);

    // Timer
    setFrequency(60);
    connect(_timerRefresh, &QTimer::timeout, [&]()
    {
        update();
    });
    _timerRefresh->start();
}

/****************************************** Set Data *********************************************/
inline void CSHudArtWare::setYaw(double val)
{
    _yaw = val;
}

inline void CSHudArtWare::setPitch(double val)
{
    _pitch = val;
}

inline void CSHudArtWare::setRoll(double val)
{
    _roll = val;
}

inline void CSHudArtWare::setAirSpeed(double val)
{
    _airSpeed = val;
}

inline void CSHudArtWare::setHeight(double val)
{
    _height = val;
}

/************************************************ Draw Graph ************************************************/
void CSHudArtWare::drawBackground(QPainter &p)
{
    static QRect r(0, 0, scOriSize.width(), scOriSize.height());

    p.save();
    p.fillRect(r, _colorBg);
    p.restore();
}

/**
 * @brief The total range is from 0 degree to 360 degree, but only show a range of 120 degrees
 * @param p
 */
void CSHudArtWare::drawYaw(QPainter &p)
{
    static const int smallDegree = 5;
    static const int bigDegree = 15;
    static const double totalDegree = 360;
    static const double viewDegree = 120;
    static const double viewLen = 300;
    static const double offsetX = (scOriSize.width() - viewLen) / 2;
    static const double shortLineLen = 6;
    static const double longLineLen = shortLineLen * 2;
    static const QPointF posPointer(viewLen/2, 0);
    static const QRectF clipRect((scOriSize.width()-viewLen)/2, 0, viewLen, 30);
    double startDegree = valueInRange(_yaw-viewDegree/2, 0, totalDegree);
    double x = 0;
    double y = 0;
    QString txtYaw = normString(valueInRange(_yaw, 0, totalDegree));

    p.save();
    p.setClipRect(clipRect);
    p.translate(offsetX, 0);
    setUserPen(p, scForeColor, sPenW);

    // Draw scales
    for (int i = floorByModulus(startDegree, smallDegree), n = ceilByModulus(startDegree+viewDegree, smallDegree); i <= n; i += smallDegree)
    {
        x = (i-startDegree) * viewLen / viewDegree;

        if (i%bigDegree == 0)
        {
            p.drawLine(QLineF(x, y, x, y+longLineLen));
            drawLabel(p, QPointF(x, y+longLineLen), Qt::AlignHCenter | Qt::AlignTop, convertDegree2Yaw(i));
        }
        else if (i%smallDegree == 0)
        {
            p.drawLine(QLineF(x, y, x, y+shortLineLen));
        }
    }

    // Draw pointer
    drawPointer(p, posPointer, Qt::AlignTop);

    // Draw actual yaw
    p.setClipRect(rect());
    drawActualLabels(p, QPointF(viewLen/2, clipRect.height()), Qt::AlignHCenter | Qt::AlignTop, normString(12), txtYaw);

    p.restore();
}

void CSHudArtWare::drawPitch(QPainter &p)
{
    static const int smallScale = 5;
    static const int bigScale = 10;
    static const double viewScale = 20;
    static const double viewWidth = 120;
    static const double viewLen = 100;
    static const double shortLineLen = 20;
    static const double longLineLen = shortLineLen * 2;
//    static const QPointF posOffset(scOriSize.width()/2, 120);
    static const QRectF rectClip(-viewWidth/2, -4, viewWidth, viewLen+8);

    double startScale = _pitch - viewScale/2;
    double x1 = 0;
    double x2 = 0;
    double y = 0;
    QString txtPitch = normString(valueInRange(_pitch, -90, 90));

    // Prepare data
    static const int grooveW = 4;
    static const int grooveH = 6;
    static const int lineW = 8;
    QVector<QPointF> vecPoints;
    vecPoints.push_back(QPointF(0, 0));
    vecPoints.push_back(QPointF(grooveW/2, grooveH));
    vecPoints.push_back(QPointF(grooveW, 0));
    vecPoints.push_back(QPointF(grooveW+lineW, 0));

    // Define lambda function to draw half graph
    auto drawRightHalf = [&]()
    {
        p.save();
        p.translate(0, viewLen/2);
        setUserPen(p, scCriticalColor, sPenW);
        p.drawLine(vecPoints.at(0), vecPoints.at(1));
        p.drawLine(vecPoints.at(1), vecPoints.at(2));
        p.drawLine(vecPoints.at(2), vecPoints.at(3));
        p.restore();
    };

    p.save();
    p.translate(scOriSize.width()/2, 180);
    p.rotate(_roll);

    p.translate(0, -60);
    p.setClipRect(rectClip);
    setUserPen(p, scForeColor, sPenW);

    // Draw scales
    for (int i = floorByModulus(startScale, smallScale), n = ceilByModulus(startScale+viewScale, smallScale); i <= n; i += smallScale)
    {
        y = (i-startScale) * viewLen / viewScale;

        if (i%bigScale == 0)
        {
            x1 = -longLineLen;
            x2 = -x1;

            drawLabel(p, QPointF(x1-1, y), Qt::AlignRight | Qt::AlignVCenter, QString::number(i));
            drawLabel(p, QPointF(x2+1, y), Qt::AlignLeft | Qt::AlignVCenter, QString::number(i));
        }
        else if (i%smallScale == 0)
        {
            x1 = -shortLineLen;
            x2 = -x1;
        }
        else
        {
            continue;
        }

        p.drawLine(QLineF(x1, y, x2, y));
    }

    // Draw center mark
    p.save();
    drawRightHalf();
    flipCoordinate(p, true);
    drawRightHalf();
    p.restore();

    // Draw actual scale
    p.setClipRect(rect());
    drawActualLabels(p, QPointF(rectClip.width()/2+1, viewLen/2), Qt::AlignLeft | Qt::AlignVCenter, normString(12), txtPitch, Qt::AlignLeft | Qt::AlignVCenter);

    p.restore();
}

void CSHudArtWare::drawRoll(QPainter &p)
{
    static const int smallDegree = 5;
    static const int bigDegree = 10;
    static const double totalDegree = 360;
    static const double viewDegree = 60;
//    static const double totalAngle = totalDegree;
    static const double viewAngle = viewDegree;
    static const double innerRadius = 120;
    static const double shortLineLen = 6;
    static const double longLineLen = shortLineLen * 2;
    static const QPointF posPointer(0, -innerRadius);
    static QRectF rectInner(-innerRadius, -innerRadius, innerRadius*2, innerRadius*2);

    double startAngle = valueInRange(_roll, -totalDegree/2, totalDegree/2) - viewAngle/2;
    QString txtRoll = normString(valueInRange(_roll, 0, totalDegree));

    p.save();
    p.translate(scOriSize.width()/2, innerRadius+60);
    p.rotate(_roll);
    p.setRenderHint(QPainter::Antialiasing);

    // Draw curve
    p.setBrush(Qt::transparent);
    setUserPen(p, scForeColor, sPenW);
    p.drawArc(rectInner, static_cast<int>(90*16-viewAngle*16/2), static_cast<int>(viewAngle*16));

    // Draw scale lines
    p.save();
    p.rotate(-viewAngle/2);
    for (int i = ceilByModulus(startAngle, smallDegree), n = ceilByModulus(startAngle+viewAngle, smallDegree); i <= n; i += smallDegree)
    {
        double tmpAngle = 0;
        double tmpLen = (i%bigDegree == 0 ? longLineLen : shortLineLen);
        double x1 = (innerRadius-tmpLen) * qSin(tmpAngle);
        double y1 = -(innerRadius-tmpLen) * qCos(tmpAngle);
        double x2 = innerRadius * qSin(tmpAngle);
        double y2 = -innerRadius * qCos(tmpAngle);

        p.drawLine(QLineF(x1, y1, x2, y2));
        if (i%bigDegree == 0) drawLabel(p, QPointF(x1, y1), Qt::AlignHCenter | Qt::AlignTop, QString::number(i));
        p.rotate(smallDegree);
    }
    p.restore();

    // Draw pointer
    drawPointer(p, posPointer, Qt::AlignTop);

    // Draw actual scale
    drawLabel(p, QPointF(0, longLineLen+1-innerRadius), Qt::AlignHCenter | Qt::AlignTop, txtRoll, Qt::AlignCenter, scBgColor);

    p.restore();
}

void CSHudArtWare::drawAirSpeed(QPainter &p)
{
    static const int smallScale = 5;
    static const double viewScale = 30;
    static const double viewWidth = 30;
    static const double viewLen = 200;
    static const double shortLineLen = 6;
    static const double longLineLen = shortLineLen * 2;
    static const double x = viewWidth - sPenW;
    static const double spareLen = 4;
    static const QPointF posOffset(20, 60);
    static const QPointF posPointer(x, viewLen/2);
    static const QRectF rectClip(0, -spareLen, viewWidth, viewLen+spareLen*2);

    double startScale = _airSpeed - viewScale/2;
    double y = 0;

    p.save();
    p.translate(posOffset);
    p.setClipRect(rectClip);
    setUserPen(p, scForeColor, sPenW);

    // Draw base line
    p.drawLine(QLineF(x, rectClip.y(), x, rectClip.y()+rectClip.height()));
    for (int i = floorByModulus(startScale, smallScale), n = ceilByModulus(startScale+viewScale, smallScale); i <= n; i += smallScale)
    {
        if (i%smallScale != 0) continue;

        y = (i-startScale) * viewLen / viewScale;
        p.drawLine(QLineF(x, y, x-longLineLen, y));
        drawLabel(p, QPointF(x-longLineLen-1, y), Qt::AlignRight | Qt::AlignVCenter, QString::number(i));
    }

    // Draw pointer
    drawPointer(p, posPointer, Qt::AlignRight);

    // Draw actual scale
    p.setClipRect(QRectF(-posOffset.x(), -posOffset.y(), scOriSize.width(), scOriSize.height()));
    drawActualLabels(p, QPointF(0, viewLen/2), Qt::AlignRight | Qt::AlignVCenter, normString(34), normString(_airSpeed));

    p.restore();
}

void CSHudArtWare::drawHeight(QPainter &p)
{
    static const int smallScale = 1;
    static const int bigScale = 5;
    static const double viewScale = 30;
    static const double viewWidth = 30;
    static const double viewLen = 200;
    static const double shortLineLen = 6;
    static const double longLineLen = shortLineLen * 2;
    static const double x = sPenW;
    static const double spareLen = 4;
    static const QPointF posOffset(scOriSize.width()-50, 60);
    static const QPointF posPointer(x, viewLen/2);
    static const QRectF rectClip(0, -spareLen, viewWidth, viewLen+spareLen*2);

    double startScale = _height - viewScale/2;
    double y = 0;
    double x2 = 0;

    p.save();
    p.translate(posOffset);
    p.setClipRect(rectClip);
    setUserPen(p, scForeColor, sPenW);

    // Draw base line
    p.drawLine(QLineF(x, rectClip.y(), x, rectClip.y()+rectClip.height()));

    // Draw scales
    for (int i = floorByModulus(startScale, smallScale), n = ceilByModulus(startScale+viewScale, smallScale); i < n; i += smallScale)
    {
        y = (i-startScale) * viewLen / viewScale;

        if (i%bigScale == 0)
        {
            x2 = x + longLineLen;
            drawLabel(p, QPointF(x2+1, y), Qt::AlignLeft | Qt::AlignVCenter, QString::number(i));
        }
        else if (i%smallScale == 0)
        {
            x2 = x + shortLineLen;
        }
        else
        {
            continue;
        }

        p.drawLine(QLineF(x, y, x2, y));
    }

    // Draw pointer
    drawPointer(p, posPointer, Qt::AlignLeft);

    // Draw actual scale
    p.setClipRect(rect());
    drawActualLabels(p, QPointF(x+rectClip.width(), viewLen/2), Qt::AlignLeft | Qt::AlignVCenter, normString(67), normString(_height), Qt::AlignLeft | Qt::AlignVCenter);

    p.restore();
}

/*********************************************** Draw Part Graph *****************************************/
void CSHudArtWare::drawLabel(QPainter &p, const QPointF &pos, Qt::Alignment posAlign, const QString &txt, Qt::Alignment txtAlign, const QColor &colorBg)
{
    double x = pos.x();
    double y = pos.y();
    double w = widthOfString(txt);
    double h = sFontH;

    // Construct the rectangle inner which we draw the text
    if (containsAlignment(posAlign, Qt::AlignLeft)) NULL;
    else if (containsAlignment(posAlign, Qt::AlignHCenter)) x -= w/2;
    else if (containsAlignment(posAlign, Qt::AlignRight)) x -= w;

    if (containsAlignment(posAlign, Qt::AlignTop)) NULL;
    else if (containsAlignment(posAlign, Qt::AlignVCenter)) y -= h/2;
    else if (containsAlignment(posAlign, Qt::AlignBottom)) y -= h;

    QRectF r(x, y, w, h);

    // Draw text
    p.fillRect(r, colorBg);
    p.drawText(r, txtAlign, txt);
}

/**
 * @brief CSHudArtWare::drawActualLabels
 * @param p
 * @param pos
 * @param posAlign
 * @param tgtTxt
 * @param actualTxt
 * @param txtAlign
 */
void CSHudArtWare::drawActualLabels(QPainter &p, const QPointF &pos, Qt::Alignment posAlign, const QString &tgtTxt, const QString &actualTxt, Qt::Alignment txtAlign)
{
    double x = pos.x();
    double y = pos.y();
    double w = widthOfString(actualTxt);
    double h = sFontH;
    double tgtW = widthOfString(tgtTxt);

    // Construct the rectangle inner which we draw the text
    if (containsAlignment(posAlign, Qt::AlignLeft)) y -= (h*3/2 + 1);
    else if (containsAlignment(posAlign, Qt::AlignHCenter)) x -= (w/2 + tgtW + 1);
    else if (containsAlignment(posAlign, Qt::AlignRight))
    {
        x -= tgtW;
        y -= (h*3/2 + 1);
    }

    QRectF rectTgt(x, y, tgtW, h);

    // Draw text
    p.save();
    p.fillRect(rectTgt, scTgtBgColor);
    p.drawText(rectTgt, txtAlign, tgtTxt);
    drawLabel(p, pos, posAlign, actualTxt, txtAlign, scBgColor);
    p.restore();
}

/**
 * @brief CSHudArtWare::drawPointer
 * @param p
 * @param pos
 * @param posAlign
 */
void CSHudArtWare::drawPointer(QPainter &p, const QPointF &pos, Qt::Alignment dirction)
{
    static const double shortSideLen = 6.5;
    static const double longSideLen = shortSideLen * 2;

    double x = pos.x();
    double y = pos.y();
    QPointF pos1st, pos2nd, pos3rd;
    QPolygonF polygon;

    // Construct the triangle
    pos1st = pos;
    switch (dirction)
    {
    case Qt::AlignTop:
    {
        pos2nd = QPointF(x-shortSideLen/2, y+longSideLen);
        pos3rd = QPointF(x+shortSideLen/2, y+longSideLen);
        break;
    }
    case Qt::AlignBottom:
    {
        pos2nd = QPointF(x-shortSideLen/2, y-longSideLen/2);
        pos3rd = QPointF(x+shortSideLen/2, y-longSideLen/2);
        break;
    }
    case Qt::AlignLeft:
    {
        pos2nd = QPointF(x+longSideLen, y-shortSideLen/2);
        pos3rd = QPointF(x+longSideLen, y+shortSideLen/2);
        break;
    }
    case Qt::AlignRight:
    {
        pos2nd = QPointF(x-longSideLen, y-shortSideLen/2);
        pos3rd = QPointF(x-longSideLen, y+shortSideLen/2);
        break;
    }
    default:
        return;
    }

    polygon.append(pos1st);
    polygon.append(pos2nd);
    polygon.append(pos3rd);

    // Draw graph
    p.save();
    p.setRenderHint(QPainter::Antialiasing);
    setUserPen(p, Qt::transparent, sPenW);
    p.setBrush(scCriticalColor);

    p.drawPolygon(polygon);

    p.restore();
}

/*********************************************** Assist Functions ***************************************/
void CSHudArtWare::scaleCoordinate(QPainter &p)
{
    double fw = static_cast<double>(width()) / scOriSize.width();
    double fh = static_cast<double>(height()) / scOriSize.height();
    p.scale(fw, fh);
}

void CSHudArtWare::flipCoordinate(QPainter &p, bool horizontal)
{
    p.shear(2, 2);
    if (horizontal) p.rotate(-90);
    else p.rotate(90);

    p.shear(0.5, 0.5);
    p.scale(2.0/3, 2.0/3);
}

/**
 * @brief CSHudArtWare::setUserPen
 * @param p
 * @param cl
 * @param w
 */
void CSHudArtWare::setUserPen(QPainter &p, const QColor &cl, double w)
{
    auto pen = p.pen();
    pen.setWidthF(w);
    pen.setColor(cl);
    p.setPen(pen);
}

/**
 * @brief CSHudArtWare::adjustAttributes
 */
void CSHudArtWare::adjustAttributes()
{
    double fw = static_cast<double>(width()) / scOriSize.width();
    double fh = static_cast<double>(height()) / scOriSize.height();
    sRatio = (abs(fw-1) < abs(fh-1) ? fw : fh);
//    sRatio = qMin(fw, fh);

    adjustFontSize();
    adjustPenWidth();
}

/**
 * @brief CSHudArtWare::adjustFontSize
 */
void CSHudArtWare::adjustFontSize()
{
    int px = static_cast<int>(scMinFontSize * sRatio);

    // Compare with the minimum size of font
    if (px < scMinFontSize) px = static_cast<int>(scMinFontSize / sRatio);
    else if (px > scMaxFontSize) px = static_cast<int>(scMaxFontSize / sRatio);
    else px = scMinFontSize;

    auto f = font();
    f.setFamily("Microsoft YaHei");
    f.setPointSize(px);
    setFont(f);

    sFontMetrics = QFontMetrics(f);
    sFontH = heightOfFont();
}

/**
 * @brief CSHudArtWare::adjustPenWidth
 */
void CSHudArtWare::adjustPenWidth()
{
    double w = scMinPenW * sRatio;

    if (w < scMinPenW) sPenW = scMinPenW / sRatio;
    else if (w > scMaxPenW) sPenW = scMaxPenW / sRatio;
    else sPenW = scMinPenW;
}

inline int CSHudArtWare::widthOfString(const QString &str) const
{
    return sFontMetrics.width(str);
}

inline int CSHudArtWare::heightOfFont() const
{
    return sFontMetrics.height();
}

/**
 * @brief CSHudArtWare::normString
 * @param val
 * @return
 */
inline QString CSHudArtWare::normString(double val) const
{
    return QString::number(val, 'f', 1);
}

/**
 * @brief CSHudArtWare::convertDegree2Yaw
 * @param val
 * @return
 */
QString CSHudArtWare::convertDegree2Yaw(int val) const
{
    int tmpVal = static_cast<int>(valueInRange(val, 0, 360));
    QString res = QString::number(tmpVal);

    switch (tmpVal)
    {
    case 0:     res = "N";  break;
    case 45:    res = "NE"; break;
    case 90:    res = "E";  break;
    case 135:   res = "SE"; break;
    case 180:   res = "S";  break;
    case 225:   res = "SW"; break;
    case 270:   res = "E";  break;
    case 315:   res = "NW"; break;
    default:                break;
    }

    return res;
}

/**
 * @brief CSHudArtWare::convertAngle2Radian
 * @param angle
 * @return
 */
inline double CSHudArtWare::convertAngle2Radian(double angle) const
{
    static const double PI = 3.1425926;
    return (angle * PI / 180.0);
}

/**
 * @brief CSHudArtWare::containesAlignment
 * @param align
 * @param basicAlign
 * @return
 */
inline bool CSHudArtWare::containsAlignment(Qt::Alignment align, Qt::Alignment basicAlign) const
{
    return !(align & basicAlign ^ basicAlign);
}

/**
 * @brief CSHudArtWare::valueInRange
 * @param val
 * @param minRange
 * @param maxRange
 * @return
 */
double CSHudArtWare::valueInRange(double val, double minRange, double maxRange) const
{
    const double range = maxRange - minRange;

    do
    {
        if (val < minRange) val += range;
        else if (val >= maxRange) val -= range;
        else break;
    }
    while (1);

    return val;
}

/**
 * @brief CSHudArtWare::floorByModulus
 * @param val
 * @param mod
 * @return
 */
int CSHudArtWare::floorByModulus(double val, int mod) const
{
    int tmpVal = qFloor(val);
    if (mod == 0) return 0xffffff;

    return (tmpVal - tmpVal%mod);
}

/**
 * @brief CSHudArtWare::ceilByModulus
 * @param mod
 * @return
 */
int CSHudArtWare::ceilByModulus(double val, int mod) const
{
    int tmpVal = qCeil(val);
    if (mod == 0) return 0xffffff;
    if (tmpVal%mod == 0) return tmpVal;

    return (tmpVal + mod - tmpVal%mod);
}


}   // cs
