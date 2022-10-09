#ifndef CSHudArtWare_H
#define CSHudArtWare_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QFontMetrics>
#include <QtMath>
#include <QJsonValue>
#include <QDebug>


namespace cs
{

class CSHudArtWare : public QWidget
{
    Q_OBJECT

public:
    enum DataType
    {
        Yaw,
        Pitch,
        Roll,
        AirSpeed,
        Height
    };

    typedef std::function<void(CSHudArtWare *, double)> setFunc;

public:
    CSHudArtWare(QWidget *parent = nullptr);
    ~CSHudArtWare() override;

    void setData(DataType type, const QJsonValue &val);
    void setFrequency(int freq);
    inline int frequency() const;

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void initMember();
    void initUI();

private:
    inline void setYaw(double val);
    inline void setPitch(double val);
    inline void setRoll(double val);
    inline void setAirSpeed(double val);
    inline void setHeight(double val);

private:
    void drawBackground(QPainter &p);
    void drawYaw(QPainter &p);
    void drawPitch(QPainter &p);
    void drawRoll(QPainter &p);
    void drawAirSpeed(QPainter &p);
    void drawHeight(QPainter &p);

    void drawLabel(QPainter &p, const QPointF &pos, Qt::Alignment posAlign, const QString &txt, Qt::Alignment txtAlign = Qt::AlignCenter, const QColor &colorBg = Qt::transparent);
    void drawActualLabels(QPainter &p, const QPointF &pos, Qt::Alignment posAlign, const QString &tgtTxt, const QString &actualTxt, Qt::Alignment txtAlign = Qt::AlignCenter);
    void drawPointer(QPainter &p, const QPointF &pos, Qt::Alignment dirction);

private:
    void scaleCoordinate(QPainter &p);
    void flipCoordinate(QPainter &p, bool horizontal);
    void setUserPen(QPainter &p, const QColor &cl, double w = 1.0);
    void adjustAttributes();
    void adjustFontSize();
    void adjustPenWidth();

    inline int widthOfString(const QString &str) const;
    inline int heightOfFont() const;
    inline QString normString(double val) const;
    QString convertDegree2Yaw(int val) const;
    inline double convertAngle2Radian(double angle) const;
    inline bool containsAlignment(Qt::Alignment align, Qt::Alignment basicAlign) const;

    double valueInRange(double val, double minRange, double maxRange) const;
    int floorByModulus(double val, int mod) const;
    int ceilByModulus(double val, int mod) const;

private:
    int _frequency;

    double _yaw;
    double _pitch;
    double _roll;
    double _airSpeed;
    double _height;

    QColor _colorBg;
    QTimer *_timerRefresh;
    QHash<DataType, setFunc> _hashTypeFunc;

};

}   // cs

#endif // CSHudArtWare_H
