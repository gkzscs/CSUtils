#include "csgcsbattery.h"


namespace cs
{

CSGcsBattery::CSGcsBattery(QWidget *parent)
    : cs::CSArtWare(parent)
{
    initMember();
}

void CSGcsBattery::setChargeStatus(bool charge)
{
    _charge = charge;
    update();
}

void CSGcsBattery::setQuantity(double val)
{
    if (val < 0) val = 0;
    if (val > 100) val = 100;

    _quantity = val;
    updateColor();
}

bool CSGcsBattery::chargeStatus() const
{
    return _charge;
}

double CSGcsBattery::quantity() const
{
    return _quantity;
}

void CSGcsBattery::initMember()
{
    _charge = true;
    setQuantity(0);
    _pixFlash = QPixmap::fromImage(QImage::fromData(QByteArray::fromHex(
        "89504e470d0a1a0a0000000d49484452000000280000002808060000008cfeb86d0000001974455874536f6674776172650041646f626520496d6167655"
        "26561647971c9653c0000013c4944415478daec56316e83500c85a8126b8e8098104be90de0065c008923d013941b30336567899819124e9030208118d2"
        "01c198dec0fda6c990aa9de2084bf1932c3e42f85beffb7d3f4d130804020129002050b1e65adc5ac59932e70b65b261183e0cc3387265cf4dd3543d20a"
        "1ccbba24ad475dda6aa2a5ceed91db1622df67ddff53c0f5f8fec8491e7390a038aa238b0ebbd711c37a669c24fad907263cf4b92642e4e1d2f161850ef"
        "a1dff373dbb607dbb65d5c2b16b5288a6ebe8761f86559d69baeeb9f4bb017236bb8fc2b2e8cc68b0be3bf407697ec3d132fe45fb1bb8a05fb12fb93956"
        "0eabade627158242a9bdd759365d97ce465599ed9b9199cc34ac11004e8b420e268146645374db3a3ce4d6216a6697ac539ec38ce3b4babd5f7fd89da66"
        "515f3927ce36df7dc40c1608040281e049f02dc000ae71cdfdfe4d32080000000049454e44ae426082")));
    _pixBattery = QPixmap::fromImage(QImage::fromData(QByteArray::fromHex(
        "89504e470d0a1a0a0000000d49484452000000280000002808060000008cfeb86d0000001974455874536f6674776172650041646f626520496d6167655"
        "26561647971c9653c0000011b4944415478daec57d10d823010a5867f19413770049c40dd800d0c13e806e804b20171039c806e204e201bd4475292c648"
        "d342da34e65ef27221e472afefaee4882202814020040d36f642089121ecc0c4617d0e5e1963ad5516c435c21fdee0664c4bfc43dc196148a8c18723f79"
        "660263b54816b5bf72ad7f3851aa9e2646a9a6497305fa4b6de22a00b5be8663104077b3c4376b0c72a74811109fc778175c8022fe0216481772c0d9d8d"
        "c024d419e4321ef1e1742a52ae74033aa37d5026dde4632be90289ba35a1bd5b9b93151ef7c146d729dd46dd9f6e6fe1c849c6127c19e6b470aef432cca"
        "e960c36514c22e7546d4daa5cb261e0391ccabd5ffdaf4d588bb9b5e249b63356a3766ef0ade4f4e34c201008f3f0116000e7a59ca15ab9ae7000000000"
        "49454e44ae426082")));
}

void CSGcsBattery::drawAll(QPainter &p)
{
    drawElectricQuantity(p);
    drawImage(p);
}

void CSGcsBattery::drawImage(QPainter &p)
{
    p.save();
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.drawPixmap(rect(), _pixBattery);
    if (_charge) p.drawPixmap(rect(), _pixFlash);
    p.restore();
}

void CSGcsBattery::drawElectricQuantity(QPainter &p)
{
    auto r = calcElectricQuantityRect();

    p.save();
    scalePainter(p);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::transparent);
    p.setBrush(_bgColor);
    p.drawRoundedRect(r, 2, 2);
    p.restore();
}

QRectF CSGcsBattery::calcElectricQuantityRect() const
{
    static const QRectF borderRect(7, 12, 24, 12);
    double x = borderRect.x();
    double y = borderRect.y();
    double w = borderRect.width() * _quantity / 100;
    double h = borderRect.height();

    return QRectF(x, y, w, h);
}

/**
 * @brief Reset color by current electric quantity
 */
void CSGcsBattery::updateColor()
{
    QColor cl = _bgColor;

    if (_quantity <= 10) cl = Qt::red;
    else if (_quantity <= 20) cl = Qt::yellow;
    else cl = Qt::white;

    setBgColor(cl);
}

}   // cs
