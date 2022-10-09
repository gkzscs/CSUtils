#ifndef CSMESSAGEBOX_H
#define CSMESSAGEBOX_H
#include <QDialog>
#include "csutils_global.h"

class QAbstractButton;
class QLabel;

namespace cs
{

class CSUTILS_EXPORT CSMessageBox : public QDialog
{
    Q_OBJECT

public:
    enum StandardButton
    {
        NoButton           = 0x00000000,
        Ok                 = 0x00000400,
        Save               = 0x00000800,
        SaveAll            = 0x00001000,
        Open               = 0x00002000,
        Yes                = 0x00004000,
        YesToAll           = 0x00008000,
        No                 = 0x00010000,
        NoToAll            = 0x00020000,
        Abort              = 0x00040000,
        Retry              = 0x00080000,
        Ignore             = 0x00100000,
        Close              = 0x00200000,
        Cancel             = 0x00400000,
        Discard            = 0x00800000,
        Help               = 0x01000000,
        Apply              = 0x02000000,
        Reset              = 0x04000000,
        RestoreDefaults    = 0x08000000
    };

    enum Icon
    {
        NoIcon,
        Question,
        Information,
        Warning,
        Critical,
        Delete
    };

    enum Language
    {
        Chinese,
        English
    };

    Q_DECLARE_FLAGS(StandardButtons, StandardButton)

public:
    CSMessageBox(QWidget *parent = nullptr);
    CSMessageBox(Icon icon, const QString &title, const QString &text, StandardButtons buttons, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    ~CSMessageBox() override;

public:
    static StandardButton information(QWidget *parent, const QString &title, const QString &text, StandardButtons buttons = Ok, StandardButton defaultButton = Ok);
    static StandardButton warning(QWidget *parent, const QString &title, const QString &text, StandardButtons buttons = Ok, StandardButton defaultButton = Ok);
    static StandardButton critical(QWidget *parent, const QString &title, const QString &text, StandardButtons buttons = Ok, StandardButton defaultButton = Ok);
    static StandardButton question(QWidget *parent, const QString &title, const QString &text, StandardButtons buttons = StandardButtons(Yes | No), StandardButton defaultButton = Yes);

    void setTitleColor(const QColor &color);
    void setTitle(const QString &title);
    void setText(const QString &txt);
    void setIcon(Icon icon);
    void setIconPixmap(const QPixmap &pix);
    void setButtonText(StandardButton standardBtn, const QString &txt);
    void setStandardButtons(StandardButtons buttons);
    void setDefaultButton(StandardButton standardBtn);
    void setDefaultButton(QAbstractButton *btn);
    void reset_clicked_button();

    QColor titleColor() const;
    QString title() const;
    QString text() const;
    Icon icon() const;
    QPixmap iconPixmap() const;
    QString buttonText(StandardButton standardBtn) const;
    StandardButton standardButton(QAbstractButton *btn) const;
    StandardButtons standardButtons() const;
    QAbstractButton *defaultButton() const;
    QAbstractButton *clickedButton() const;
    QAbstractButton *button(StandardButton standardBtn) const;
    QList<QAbstractButton *> buttons() const;

    QAbstractButton *addButton(StandardButton standardBtn);
    bool removeButton(StandardButton standardBtn);

    static void set_current_language(Language lang);
    static Language current_language();

protected:
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void closeEvent(QCloseEvent *) override;

protected:
    QList<StandardButton> parseStandardButtons(const StandardButtons &standardBtns) const;

    QPushButton *createPushButton(StandardButton standardBtn);
    QString convertColor2String(const QColor &color) const;

    static QString get_text_by_button_type(StandardButton standardBtn);

private:
    void initMember();
    void initUI();
    void initSignalSlot();

//    void initButtons();
    void initIcons();

private:
    void resizeUI();
    void resizeButtons();

    void updateIcon();

signals:
    void closed_signal();

private slots:
    void btnClickSlot();

protected:
    QLabel          *_labTitle;
    QLabel          *_labIcon;
    QLabel          *_labText;

    QPoint          _offset;
    QColor          _titleColor;
    Icon            _icon;
    QPixmap         _iconPix;
    QAbstractButton *_btnDefault;
    QAbstractButton *_btnClicked;
    StandardButtons _standardBtns;
    QHash<QAbstractButton *, StandardButton> _hashStandardBtns;
//    QHash<StandardButton, QString> _hashBtnText;
    QHash<Icon, QPixmap>                    _hashBtnIcon;
//    QHash<StandardButton, QString>          _hash_btn_txt_zh;
//    QHash<StandardButton, QString>          _hash_btn_txt_en;

protected:
    static Language    _language;

};

// Declare operators for enum flags
Q_DECLARE_OPERATORS_FOR_FLAGS(CSMessageBox::StandardButtons)

}   // `cs`

#endif // CSMESSAGEBOX_H
