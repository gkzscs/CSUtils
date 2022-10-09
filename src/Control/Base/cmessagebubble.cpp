#include "cmessagebubble.h"
#include <QMouseEvent>
#include <QAbstractButton>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QStyleOption>
#include <QPainter>
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>
namespace cs{
#define EXEC_STATIC_BUBBLE_MESSAGE_BOX(parent, text)   \
    do { \
    cs::CMessageBubble msgBox( text, parent);    \
    msgBox.setWindowFlag(Qt::FramelessWindowHint);  \
    msgBox.exec(); \
} while (0)
//        return
CMessageBubbleManager* CMessageBubbleManager::m_pInstance = nullptr;

CMessageBubble::CMessageBubble(QWidget *parent)
    : QDialog(parent)
{
//    _parentSize = parent->size();
    initMember();
    initUI();
    initSignalSlot();
}

CMessageBubble::CMessageBubble(const QString &text, QWidget *parent, Qt::WindowFlags f,const int &number,const QString &title)
    : CMessageBubble(parent)
{
    setText(text);
    setTitle(title);
    setWindowFlags(f);
    resizeUI(text,number,parent,title);
}

CMessageBubble::~CMessageBubble()
{

}


void CMessageBubble::bubbleInformation(QWidget *parent, const QString &text)
{
    EXEC_STATIC_BUBBLE_MESSAGE_BOX(parent,text);
}

void CMessageBubble::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void CMessageBubble::resizeEvent(QResizeEvent *e)
{
    QDialog::resizeEvent(e);
}

void CMessageBubble::mousePressEvent(QMouseEvent *e)
{
    _offset = e->pos();
}

void CMessageBubble::mouseMoveEvent(QMouseEvent *e)
{
    auto pos = mapToParent(e->pos() - _offset);
    move(pos);
}

void CMessageBubble::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    _bIsEnter = true;
}

void CMessageBubble::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    _bIsEnter = false;
}

QString CMessageBubble::convertColor2String(const QColor &color) const
{
    QString str("rgba(%1, %2, %3, %4)");
    str = str.arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());

    return str;
}

void CMessageBubble::initMember()
{
    _labIcon = new QLabel(this);
    _labText = new QLabel(this);
    _labTitle = new QLabel(this);
    _toolBtnClose = new QToolButton(this);
    _timer = new QTimer(this);
    setText(nullptr);
    setTitle(nullptr);
    // Initialize containerss

    // Set object name
    _labIcon->setObjectName("lab_icon");
    _labText->setObjectName("lab_text");
    _labTitle->setObjectName("lab_title");
    _toolBtnClose->setObjectName("tool_btn_close");
}

void CMessageBubble::initUI()
{
    resize(240, 128);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    _labIcon->setAlignment(Qt::AlignCenter);
    _labIcon->setStyleSheet("border-image: url(:/icons/warning_16x16.png);");
    _labText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    _labText->setWordWrap(true);
    _toolBtnClose->setStyleSheet("border-image: url(:/icons/close_24x24.png);");
    _labText->setStyleSheet("color:rgb(200,200,200)");
    _labTitle->setStyleSheet("color:rgb(200,200,200);background-color:rgba(0,0,0,20);");
    _labTitle->setAlignment(Qt::AlignHCenter);

    this->setStyleSheet("cs--CMessageBubble { background-color:rgba(0,0,0,100);}");

    bool ret = connect(_toolBtnClose,&QToolButton::clicked,this,&cs::CMessageBubble::onCloseBtnClick);
}

void CMessageBubble::initSignalSlot()
{
    connect(_timer,SIGNAL(timeout()),this,SLOT(slotTimerCountDown()));
    _nCountDown = 100;
    _timer->start(50);
}

void CMessageBubble::resizeUI(const QString& text, const int &number, QWidget *parent, const QString &title)
{
    int nTitleHigh = 0;
    int nTitleWidth = 0;
    if(!title.isEmpty())
    {
        QFont titleFont;
        titleFont.setFamily("msyh");
        titleFont.setPixelSize(20);
        nTitleHigh = int(QFontMetricsF(titleFont).tightBoundingRect(title).height()) + 15;
        nTitleWidth = int(QFontMetricsF(titleFont).tightBoundingRect(title).width()) + title.size();
        _labTitle->setFont(titleFont);
    }
    int nInterval = 8;
    QFont MyFont;
    MyFont.setFamily("msyh");
    MyFont.setPixelSize(15);

    _labText->setFont(MyFont);

    QRectF FontRect = QFontMetricsF(MyFont).tightBoundingRect(text);//获取字体的像素高度和宽度

    int nFontHight = int(FontRect.height()) + 5;
    int nTextWidth = int(FontRect.width()) + text.size();
    int nFontWidth = nTextWidth > nTitleWidth ? nTextWidth : nTitleWidth;

    resize(nInterval*2 + nFontHight *2 + nFontWidth, nFontHight + 2*nInterval + nTitleHigh);

    _labIcon->setGeometry(nInterval, nInterval +nTitleHigh, nFontHight, nFontHight);
    _labText->setGeometry(nInterval*2 + nFontHight, nInterval + nTitleHigh, nFontWidth, nFontHight);
    _labTitle->setGeometry(0,0, nInterval*2 + nFontHight *2 + nFontWidth, nTitleHigh);
    _toolBtnClose->setGeometry(nInterval*4 + nFontWidth,nInterval,nFontHight,nFontHight);

    if(parent)
        this->setGeometry(parent->pos().x() + parent->width() / 2 - (nInterval*4 + nFontHight *2 + nFontWidth)/2,
                          parent->pos().y() +parent->height() / 5 + 80*number, nInterval*4 + nFontHight *2 + nFontWidth,nFontHight + 2*nInterval + nTitleHigh);
    else
    {
         //获取可用桌面大小
         QRect deskRect = QApplication::desktop()->availableGeometry();
        this->setGeometry(deskRect.x() + deskRect.width() / 2 - (nInterval*4 + nFontHight *2 + nFontWidth)/2,
                          deskRect.y() +deskRect.height() / 5 + 80*number, nInterval*4 + nFontHight *2 + nFontWidth,nFontHight + 2*nInterval + nTitleHigh);
    }

}


void CMessageBubble::slotTimerCountDown()
{
    _nCountDown--;
    if(_nCountDown <= 0)
    {
        _timer->stop();
        reject();
        emit signalBubbleEnd();
        return;
    }

    if(_bIsEnter)
        _nCountDown = 100;
    double realOpacity = _nCountDown / 100.0;
    setWindowOpacity(realOpacity);
}

void CMessageBubble::onCloseBtnClick()
{
    _nCountDown = 0;
    _bIsEnter = false;
}

void CMessageBubble::setText(const QString &txt)
{
    _labText->setText(txt);
}

void CMessageBubble::setTitle(const QString &title)
{
    if(title.isEmpty())
    {
        _labTitle->hide();
        return;
    }
    _labTitle->show();
    _labTitle->setText(title);
}

void CMessageBubble::setIconPixmap(const QPixmap &pix)
{
    _iconPix = pix;
}

QString CMessageBubble::text() const
{
    return _labText->text();
}

QPixmap CMessageBubble::iconPixmap() const
{
    return _iconPix;
}

CMessageBubbleManager *CMessageBubbleManager::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new CMessageBubbleManager();
    }
    return m_pInstance;
}

void CMessageBubbleManager::release()
{
    if(m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
}

void CMessageBubbleManager::createNonModalBubble(const QString &text, QWidget *parent, const QString &title)
{
    CMessageBubble *pCmessageBubble = new CMessageBubble(text,parent,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint,m_lstCMessageBubble.size(),title);

    pCmessageBubble->setWindowFlag(Qt::FramelessWindowHint);
    pCmessageBubble->show();
    m_lstCMessageBubble<<pCmessageBubble;
    connect(pCmessageBubble,SIGNAL(signalBubbleEnd()),this,SLOT(onBubbleEnd()));
}

void CMessageBubbleManager::onBubbleEnd()
{
    CMessageBubble *pBubble = (CMessageBubble*)sender();
    if(pBubble)
    {
        if(m_lstCMessageBubble.contains(pBubble))
        {
            m_lstCMessageBubble.removeOne(pBubble);
        }

        delete pBubble;
        pBubble = nullptr;
    }
}

CMessageBubbleManager::CMessageBubbleManager()
{

}


}
