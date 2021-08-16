#ifndef CSTitleBar_H
#define CSTitleBar_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>

namespace cs
{

class CSUTILS_EXPORT CSTitleBar : public QWidget
{
    Q_OBJECT
    friend class CSMainWnd;

public:
    CSTitleBar(QWidget *parent = nullptr);
    ~CSTitleBar() override;

    void setTitle(const QString &title);
    void setLogo(const QPixmap &pix);

    QString title() const;
    QPixmap logo() const;

protected:
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    void initMember();
    void initUI();
    void initSignalSlot();

    void initIcons();

private:
    QToolButton *createToolButton(const QIcon &icon, QWidget *parent = nullptr);
    void updateMaximizeStatus();

signals:
    void logoClickSignal();

private slots:
    void btnMinimizeClickSlot();
    void btnMaximizeClickSlot();
    void btnCloseClickSlot();

private:
    QLabel *_labLogo;
    QLabel *_labTitle;
    QToolButton *_btnMinimize;
    QToolButton *_btnMaximize;
    QToolButton *_btnClose;

//    bool _flagClick;
    QPoint _offset;
    QPixmap _logo;
    QIcon _iconMinimize;
    QIcon _iconMaximize;
    QIcon _iconRestore;
    QIcon _iconClose;

};

}   // `cs`

#endif // CSTitleBar_H
