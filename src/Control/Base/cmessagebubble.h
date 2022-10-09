#ifndef CMESSAGEBUBBLE_H
#define CMESSAGEBUBBLE_H
#include <QDialog>
#include "csutils_global.h"

class QAbstractButton;
class QLabel;
class QToolButton;
class QTimer;
namespace cs
{
class CMessageBubble;
class CSUTILS_EXPORT CMessageBubbleManager : public QObject
{
    Q_OBJECT
public:
    static CMessageBubbleManager *getInstance();
    static void release();

    void createNonModalBubble(const QString &text, QWidget *parent = nullptr, const QString &title = "");
private slots:
    void onBubbleEnd();
private:
    CMessageBubbleManager();
    QList<CMessageBubble*> m_lstCMessageBubble;
    static CMessageBubbleManager* m_pInstance;
};

class CMessageBubble: public QDialog
{
    Q_OBJECT
public:
    CMessageBubble(QWidget *parent = nullptr);
    CMessageBubble(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint,const int &number = 0,const QString &title = "");
    ~CMessageBubble() override;

    static void bubbleInformation(QWidget *parent, const QString &text);
public:

    void setText(const QString &txt);
    void setTitle(const QString &title);
    void setIconPixmap(const QPixmap &pix);

    QString text() const;
    QPixmap iconPixmap() const;
protected:
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
protected:
    QString convertColor2String(const QColor &color) const;
private:
    void initMember();
    void initUI();
    void initSignalSlot();
private:
    void resizeUI(const QString& text, const int &number, QWidget *parent = nullptr,const QString &title = "");

signals:
    void signalBubbleEnd();
private slots:
    void slotTimerCountDown();
    void onCloseBtnClick();
protected:
    bool _bIsEnter = false;
    QLabel *_labIcon;
    QLabel *_labText;
    QLabel *_labTitle;
    QToolButton *_toolBtnClose;
    QPoint _offset;
    QColor _titleColor;
    QPixmap _iconPix;
    QTimer *_timer;
    int _nCountDown;
    QSize _parentSize;
};
}   // `cs`
#endif // CMESSAGEBUBBLE_H
