#include "cstitlebar.h"
#include <QMouseEvent>
#include <QDebug>


namespace cs
{

CSTitleBar::CSTitleBar(QWidget *parent)
    : QWidget(parent)
{
    initMember();
    initUI();
    initSignalSlot();
}

CSTitleBar::~CSTitleBar()
{
    _labLogo->deleteLater();
    _labTitle->deleteLater();
    _btnMinimize->deleteLater();
    _btnMaximize->deleteLater();
    _btnClose->deleteLater();
}

void CSTitleBar::setTitle(const QString &title)
{
    _labTitle->setText(title);
}

void CSTitleBar::setLogo(const QPixmap &pix)
{
    _logo = pix;

    _labLogo->setPixmap(_logo.scaled(_labLogo->size(), Qt::AspectRatioMode::KeepAspectRatio, Qt::SmoothTransformation));
}

QString CSTitleBar::title() const
{
    return _labTitle->text();
}

QPixmap CSTitleBar::logo() const
{
    return _logo;
}

void CSTitleBar::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    const int h = 40;
    const QSize logoSize(h, h);
    const QSize btnSize(h, h);
    int titleW = width() - 240;
    int titleX = (width() - titleW) / 2;

    _labLogo->setGeometry(0, 0, logoSize.width(), logoSize.height());
    _labTitle->setGeometry(titleX, 0, titleW, h);
    _btnClose->move(width()-btnSize.width(), 0);
    _btnMaximize->move(width()-btnSize.width()*2, 0);
    _btnMinimize->move(width()-btnSize.width()*3, 0);

    // Set pixmap
    _labLogo->setPixmap(_logo.scaled(_labLogo->size(), Qt::AspectRatioMode::KeepAspectRatio, Qt::SmoothTransformation));
}

void CSTitleBar::mousePressEvent(QMouseEvent *event)
{
    _offset = event->pos();
}

void CSTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    // Move parent widget
    auto wnd = parentWidget();
    if (!wnd) return;

    auto pos = mapToGlobal(event->pos() - _offset);
    wnd->move(pos);
}

void CSTitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

//    emit _btnMaximize->clicked();
}

void CSTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if (_labLogo->rect().contains(event->pos()))
    {
        qDebug() << "clicked logo";
        emit logoClickSignal();
    }
}

void CSTitleBar::initMember()
{
    // Initialize icons
    initIcons();

    // Initialize member widgets
    _labLogo = new QLabel(this);
    _labTitle = new QLabel(this);
    _btnMinimize = createToolButton(_iconMinimize, this);
    _btnMaximize = createToolButton(_iconMaximize, this);
    _btnClose = createToolButton(_iconClose, this);

    // Set object name
    _labLogo->setObjectName("lab_logo");
    _labTitle->setObjectName("lab_title");
    _btnMinimize->setObjectName("btn_minimize");
    _btnMaximize->setObjectName("btn_maximize");
    _btnClose->setObjectName("btn_close");
}

void CSTitleBar::initUI()
{
    // Set attribute
    resize(1000, 40);
    setAttribute(Qt::WA_StyledBackground);

    _labLogo->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    _labTitle->setAlignment(Qt::AlignCenter);

    // Set style sheet
    setStyleSheet("CSTitleBar { background-color: rgba(0, 0, 0, 0.5); }");
}

void CSTitleBar::initSignalSlot()
{
    connect(_btnMinimize, &QToolButton::clicked, this, &CSTitleBar::btnMinimizeClickSlot);
    connect(_btnMaximize, &QToolButton::clicked, this, &CSTitleBar::btnMaximizeClickSlot);
    connect(_btnClose, &QToolButton::clicked, this, &CSTitleBar::btnCloseClickSlot);
}

void CSTitleBar::initIcons()
{
    const auto dataMinimize = QByteArray::fromHex("89504e470d0a1a0a0000000d4948445200000018000000180806000000e0773df80000001974455874536f66747761726500"
            "41646f626520496d616765526561647971c9653c000000334944415478da62601805a360148c028280119be0ffffffdf03290112cdfac0c8c82"
            "8882ec8341ac6a360148c82410000020c0012250504851a61d40000000049454e44ae426082");
    const auto dataMaximize = QByteArray::fromHex("89504e470d0a1a0a0000000d4948445200000018000000180806000000e0773df80000001974455874536f66747761726500"
            "41646f626520496d616765526561647971c9653c000000544944415478da626018052313fcffffbfe13fe9a0019b598c580c170052efc971182"
            "310a08b31d13a34187104d17f6af98085540da43a88e641346ac1a80594031672d337a53e6824c3ac46865130320140800100602547e58323d6"
            "a00000000049454e44ae426082");
    const auto dataClose = QByteArray::fromHex("89504e470d0a1a0a0000000d4948445200000018000000180806000000e0773df80000001974455874536f66747761726500416"
            "46f626520496d616765526561647971c9653c000000674944415478da626018052313fcffff3f0188f703b101116a0da06a1348b100a40104de"
            "e3b3046af87ba8dafda45880ac11ab25c4a821db128a0dc76710d50cc76309f50cc761094986330d863c41bb20a26924d33499d23ca3d1a3a8a"
            "06d61370a861700083000d1dc90c468b3874e0000000049454e44ae426082");

    _iconMinimize = QIcon(QPixmap::fromImage(QImage::fromData(dataMinimize)));
    _iconMaximize = QIcon(QPixmap::fromImage(QImage::fromData(dataMaximize)));
    // To do
    _iconClose = QIcon(QPixmap::fromImage(QImage::fromData(dataClose)));
}

QToolButton *CSTitleBar::createToolButton(const QIcon &icon, QWidget *parent)
{
    const QSize btnSize(40, 40);
    auto btn = new QToolButton(parent);

    btn->resize(btnSize);
    btn->setIconSize(btnSize);
    btn->setAutoRaise(true);
    btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    btn->setIcon(icon);

    return btn;
}

void CSTitleBar::updateMaximizeStatus()
{
    const char *proName = "icon-name";
    const QString strMaximize = "maximize";
    const QString strRestore = "restore";

    auto wnd = parentWidget();
    if (!wnd) return;

    auto maximized = wnd->isMaximized();
    if (maximized)
    {
        _btnMaximize->setIcon(_iconRestore);
        _btnMaximize->setProperty(proName, strRestore);
    }
    else
    {
        _btnMaximize->setIcon(_iconMaximize);
        _btnMaximize->setProperty(proName, strMaximize);
    }
}

void CSTitleBar::btnMinimizeClickSlot()
{
    auto wnd = parentWidget();
    if (!wnd) return;

    wnd->showMinimized();
}

void CSTitleBar::btnMaximizeClickSlot()
{
    auto wnd = parentWidget();
    if (!wnd) return;

    if (wnd->isMaximized()) wnd->showNormal();
    else wnd->showMaximized();

    updateMaximizeStatus();
}

void CSTitleBar::btnCloseClickSlot()
{
    auto wnd = parentWidget();
    if (!wnd) return;

    wnd->close();
}

}   // `cs`
