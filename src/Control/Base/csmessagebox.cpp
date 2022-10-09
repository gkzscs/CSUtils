#pragma execution_character_set("utf-8")
#include "csmessagebox.h"
#include <QAbstractButton>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>
#include <QTimer>

namespace cs
{

// Macros
#define EXEC_STATIC_MESSAGE_BOX(parent, title, text, buttons, defaultButton, icon, titleColor)   \
    do { \
        cs::CSMessageBox msgBox(icon, title, text, buttons, parent);    \
        msgBox.setWindowFlag(Qt::FramelessWindowHint);  \
        msgBox.setIcon(icon);    \
        msgBox.setTitleColor(titleColor);   \
        msgBox.setDefaultButton(defaultButton); \
        msgBox.exec();  \
        auto btn = msgBox.clickedButton();  \
        return msgBox.standardButton(btn);  \
    } while (0)

// Static member variables
CSMessageBox::Language CSMessageBox::_language = Chinese;


CSMessageBox::CSMessageBox(QWidget *parent)
    : QDialog(parent)
{
    initMember();
    initUI();
    initSignalSlot();

    setStandardButtons(Ok);
    setDefaultButton(Ok);
}

CSMessageBox::CSMessageBox(Icon icon, const QString &title, const QString &text, StandardButtons buttons, QWidget *parent, Qt::WindowFlags f)
    : CSMessageBox(parent)
{
    setIcon(icon);
    setTitle(title);
    setText(text);
    setStandardButtons(buttons);
    setWindowFlags(f);
}

CSMessageBox::~CSMessageBox()
{
    DELETE_Q_POINTER(_labTitle);
    DELETE_Q_POINTER(_labIcon);
    DELETE_Q_POINTER(_labText);

    qDeleteAll(_hashStandardBtns.keys());
    _hashStandardBtns.clear();

    _btnDefault = nullptr;
    _btnClicked = nullptr;
}

/********************************************** Static functions **************************************************************/
CSMessageBox::StandardButton CSMessageBox::information(QWidget *parent, const QString &title, const QString &text, StandardButtons buttons, StandardButton defaultButton )
{
    EXEC_STATIC_MESSAGE_BOX(parent, title, text, buttons, defaultButton, Information, QColor(15, 255, 255));
}

CSMessageBox::StandardButton CSMessageBox::warning(QWidget *parent, const QString &title, const QString &text, StandardButtons buttons, StandardButton defaultButton)
{
    EXEC_STATIC_MESSAGE_BOX(parent, title, text, buttons, defaultButton, Warning, QColor(247, 194, 79));
}

CSMessageBox::StandardButton CSMessageBox::critical(QWidget *parent, const QString &title, const QString &text, StandardButtons buttons, StandardButton defaultButton)
{
    EXEC_STATIC_MESSAGE_BOX(parent, title, text, buttons, defaultButton, Critical, QColor(242, 16, 16));
}

CSMessageBox::StandardButton CSMessageBox::question(QWidget *parent, const QString &title, const QString &text, StandardButtons buttons, StandardButton defaultButton)
{
    EXEC_STATIC_MESSAGE_BOX(parent, title, text, buttons, defaultButton, Question, QColor(247, 194, 79));
}

void CSMessageBox::setTitleColor(const QColor &color)
{
    _titleColor = color;

    auto strColor = convertColor2String(color);
    _labTitle->setStyleSheet("color: " + strColor);
}

void CSMessageBox::setTitle(const QString &title)
{
    _labTitle->setText(title);
}

void CSMessageBox::setText(const QString &txt)
{
    _labText->setText(txt);
}

void CSMessageBox::setIcon(Icon icon)
{
    _icon = icon;

    auto pix = _hashBtnIcon.value(icon);
    setIconPixmap(pix);
}

void CSMessageBox::setIconPixmap(const QPixmap &pix)
{
    _iconPix = pix;

    updateIcon();
}

void CSMessageBox::setButtonText(StandardButton standardBtn, const QString &txt)
{
    auto btn = button(standardBtn);
    if (!btn) return;

    btn->setText(txt);
}

void CSMessageBox::setStandardButtons(StandardButtons buttons)
{
    // Clear
    auto listOldBtns = parseStandardButtons(_standardBtns);
    for (auto btn : listOldBtns)
    {
        removeButton(btn);
    }

    // Reset
    auto listBtns = parseStandardButtons(buttons);
    for (auto btn : listBtns)
    {
        addButton(btn);
    }
}

void CSMessageBox::setDefaultButton(StandardButton standardBtn)
{
    auto btn = button(standardBtn);
    setDefaultButton(btn);
}

void CSMessageBox::setDefaultButton(QAbstractButton *btn)
{
    _btnDefault = btn;

    if (btn) btn->setFocus();
}

void CSMessageBox::reset_clicked_button()
{
    _btnClicked = nullptr;
}

QColor CSMessageBox::titleColor() const
{
    return _titleColor;
}

QString CSMessageBox::title() const
{
    return _labTitle->text();
}

QString CSMessageBox::text() const
{
    return _labText->text();
}

CSMessageBox::Icon CSMessageBox::icon() const
{
    return _icon;
}

QPixmap CSMessageBox::iconPixmap() const
{
    return _iconPix;
}

QString CSMessageBox::buttonText(StandardButton standardBtn) const
{
    auto btn = button(standardBtn);
    if (!btn) return nullptr;

    return btn->text();
}

CSMessageBox::StandardButton CSMessageBox::standardButton(QAbstractButton *btn) const
{
    return _hashStandardBtns.value(btn);
}

CSMessageBox::StandardButtons CSMessageBox::standardButtons() const
{
    return _standardBtns;
}

QAbstractButton *CSMessageBox::defaultButton() const
{
    return _btnDefault;
}

QAbstractButton *CSMessageBox::clickedButton() const
{
    return _btnClicked;
}

QAbstractButton *CSMessageBox::button(CSMessageBox::StandardButton standardBtn) const
{
    return _hashStandardBtns.key(standardBtn);
}

/**
 * @brief Return all buttons those used in the message box in order
 * @return
 */
QList<QAbstractButton *> CSMessageBox::buttons() const
{
    QList<QAbstractButton *> listBtns;
    auto listStdBtns = parseStandardButtons(_standardBtns);

    for (auto stdBtn : listStdBtns)
    {
        auto btn = _hashStandardBtns.key(stdBtn);
        listBtns.append(btn);
    }

    return listBtns;
}

/**
 * @brief Add a standard button to the message box
 * @param standardBtn
 * @return
 */
QAbstractButton *CSMessageBox::addButton(CSMessageBox::StandardButton standardBtn)
{
    // Remove the old button
    removeButton(standardBtn);

    auto btn = createPushButton(standardBtn);
    if (!btn) return nullptr;

    _hashStandardBtns.insert(btn, standardBtn);
    _standardBtns |= standardBtn;

    // Connect to the slot
    connect(btn, &QPushButton::clicked, this, &CSMessageBox::btnClickSlot);
    return btn;
}

/**
 * @brief Remove standard button in the message box
 * @param standardBtn
 * @return
 */
bool CSMessageBox::removeButton(StandardButton standardBtn)
{
    for (auto stdBtn : _hashStandardBtns)
    {
        if (stdBtn != standardBtn) continue;

        auto btn = _hashStandardBtns.key(stdBtn);
        _hashStandardBtns.remove(btn);
        _standardBtns &= ~standardBtn;

        // Destroy the old button
        btn->setParent(nullptr);
        btn->deleteLater();

        return true;
    }

    return false;
}

void CSMessageBox::set_current_language(Language lang)
{
    _language = lang;
}

CSMessageBox::Language CSMessageBox::current_language()
{
    return _language;
}

void CSMessageBox::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void CSMessageBox::resizeEvent(QResizeEvent *e)
{
    QDialog::resizeEvent(e);

    resizeUI();
}

void CSMessageBox::mousePressEvent(QMouseEvent *e)
{
    _offset = e->pos();
}

void CSMessageBox::mouseMoveEvent(QMouseEvent *e)
{
    auto pos = mapToParent(e->pos() - _offset);
    move(pos);
}

void CSMessageBox::closeEvent(QCloseEvent *e)
{
    QDialog::closeEvent(e);

    emit closed_signal();
}

/**
 * @brief Convert StandardButtons to a list of StandardButton items
 * @param standardBtns
 * @return
 */
QList<CSMessageBox::StandardButton> CSMessageBox::parseStandardButtons(const StandardButtons &standardBtns) const
{
#define CHECK_BUTTON(x)     do { if (standardBtns & x) listBtns.append(x); } while (0)
    QList<StandardButton> listBtns;

    // Here you can adjust the sequence of buttons
    CHECK_BUTTON(NoButton);
    CHECK_BUTTON(Open    );
    CHECK_BUTTON(No      );
    CHECK_BUTTON(NoToAll );
    CHECK_BUTTON(Abort   );
    CHECK_BUTTON(Retry   );
    CHECK_BUTTON(Ignore  );
    CHECK_BUTTON(Close   );
    CHECK_BUTTON(Cancel  );
    CHECK_BUTTON(Discard );
    CHECK_BUTTON(Help    );
    CHECK_BUTTON(Ok      );
    CHECK_BUTTON(Save    );
    CHECK_BUTTON(SaveAll );
    CHECK_BUTTON(Apply   );
    CHECK_BUTTON(Reset   );
    CHECK_BUTTON(Yes     );
    CHECK_BUTTON(YesToAll);
    CHECK_BUTTON(RestoreDefaults);

    return listBtns;
#undef CHECK_BUTTON
}

/**
 * @brief Create push button by `StandardButton` value
 * @param standardBtn
 * @return
 */
QPushButton *CSMessageBox::createPushButton(StandardButton standardBtn)
{
    // Validate the enumeration value
    switch (standardBtn)
    {
    case NoButton:
        return nullptr;
    default:
        break;
    }

    // Create button
    const QSize btnSize(88, 32);
    auto btn = new QPushButton(this);
    auto txt = get_text_by_button_type(standardBtn);

    btn->setFlat(true);
    btn->resize(btnSize);
//    btn->setText(_hashBtnText.value(standardBtn));
    btn->setText(txt);

    return btn;
}

/**
 * @brief Convert QColor to string expression, which is assembled with red, green, blue, and alpha
 * @param color
 * @return
 */
QString CSMessageBox::convertColor2String(const QColor &color) const
{
    QString str("rgba(%1, %2, %3, %4)");
    str = str.arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());

    return str;
}

QString CSMessageBox::get_text_by_button_type(StandardButton standardBtn)
{
    static QHash<StandardButton, QString> hashBtnTxtCN;
    static QHash<StandardButton, QString> hashBtnTxtEN;

    // Initialize hash
    if (hashBtnTxtCN.isEmpty())
    {
        QStringList listTxtCN, listTxtEN;
        QList<StandardButton> listStdBtns;
        listStdBtns << NoButton << Ok << Save << SaveAll << Open << Yes << YesToAll << No << NoToAll << Abort << Retry
                    << Ignore << Close << Cancel << Discard << Help << Apply << Reset << RestoreDefaults;
        listTxtCN << "" << "确定" << "保存" << "保存全部" << "打开" << "是" << "全部选是" << "否" << "全部选否" << "退出" << "重试"
                  << "忽略" << "关闭" << "取消" << "放弃" << "帮助" << "应用" << "重置" << "恢复默认设置";
        listTxtEN << "" << "Ok" << "Save" << "Save all" << "Open" << "Yes" << "Yes to all" << "No" << "No to all" << "Abort" << "Retry"
                  << "Ignore" << "Close" << "Cancel" << "Discard" << "Help" << "Apply" << "Reset" << "Restore default";

        for (int i = 0, n = listStdBtns.size(); i < n; ++i)
        {
            hashBtnTxtCN.insert(listStdBtns.at(i), listTxtCN.at(i));
            hashBtnTxtEN.insert(listStdBtns.at(i), listTxtEN.at(i));
        }
    }

    // Get text by button type and current language
    QString txt;
    switch (_language)
    {
    case Chinese:
        txt = hashBtnTxtCN.value(standardBtn);
        break;
    case English:
        txt = hashBtnTxtEN.value(standardBtn);
        break;
    }

    return txt;
}

void CSMessageBox::initMember()
{
    _labTitle = new QLabel(this);
    _labIcon = new QLabel(this);
    _labText = new QLabel(this);

    setTitle(tr("Untitled"));
    setText(nullptr);
    setIcon(NoIcon);

    _btnDefault = nullptr;
    _btnClicked = nullptr;
    _standardBtns = NoButton;

    // Initialize containerss
//    initButtons();
    initIcons();

    // Set object name
    _labTitle->setObjectName("lab_title");
    _labIcon->setObjectName("lab_icon");
    _labText->setObjectName("lab_text");
}

void CSMessageBox::initUI()
{
    // Set attribute
    resize(480, 256);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    _labTitle->setAlignment(Qt::AlignCenter);
    _labIcon->setAlignment(Qt::AlignCenter);
    _labText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    _labText->setWordWrap(true);

    // Set style sheet
    setStyleSheet("cs--CSMessageBox { background-color: rgba(0, 0, 0, 0.8); border-radius: 8px; }"
                  "QLabel { font-size: 16px; color: white; }"
                  "QLabel#lab_title { font-weight: bold; background-color: rgba(0, 0, 0, 1); border-top-left-radius: 8px; border-top-right-radius: 8px; }"
                  "QPushButton { font-size: 16px; color: white; background-color: transparent; border: solid; border-width: 1px; border-color: white; border-radius: 4px; }"
                  "QPushButton:focus { color: black; background-color: rgba(15, 255, 255, 0.8); border: none; } "
                  "QPushButton:hover { color: black; background-color: rgba(15, 255, 255); border: none; } "
                  "QPushButton:pressed { color: black; background-color: rgba(15, 255, 255); border: none; }");
}

void CSMessageBox::initSignalSlot()
{
    // Do nothing
}

/**
 * @brief Initialize container
 */
//void CSMessageBox::initButtons()
//{
//    // To modify
//    QStringList listTxtCN, listTxtEN;
//    QList<StandardButton> listStdBtns;
//    listStdBtns << NoButton << Ok << Save << SaveAll << Open << Yes << YesToAll << No << NoToAll << Abort << Retry
//                << Ignore << Close << Cancel << Discard << Help << Apply << Reset << RestoreDefaults;
//    listTxtCN << "" << "确定" << "保存" << "保存全部" << "打开" << "是" << "全部选是" << "否" << "全部选否" << "退出" << "重试"
//              << "忽略" << "关闭" << "取消" << "放弃" << "帮助" << "应用" << "重置" << "恢复默认设置";
//    listTxtEN << "" << "Ok" << "Save" << "Save all" << "Open" << "Yes" << "Yes to all" << "No" << "No to all" << "Abort" << "Retry"
//              << "Ignore" << "Close" << "Cancel" << "Discard" << "Help" << "Apply" << "Reset" << "Restore default";

//    for (int i = 0, n = listStdBtns.size(); i < n; ++i)
//    {
//        _hashBtnText.insert(listStdBtns.at(i), listTxtCN.at(i));
//    }
//}

void CSMessageBox::initIcons()
{
    QList<Icon> listIcons;
    QList<QByteArray> listPixmapData;
    listIcons << NoIcon << Question << Information << Warning << Critical << Delete;
    listPixmapData << QByteArray::fromHex("")
                   << QByteArray::fromHex("89504e470d0a1a0a0000000d4948445200000040000000400806000000aa6971de0000001974455874536f6674776172650041646f626520496d6167655265"
                                          "61647971c9653c000003004944415478daec5beb71a330103619174007a604ae82900ace25900edc41b80a5c024905b8039c0a7007e00a4807449ad99bf129"
                                          "1212ec4a88133ba3c13fcc6abf7db388dd6ea38d360a9922db1b0cc390b04bc6d6335b7f7f8fd195ad8ead4ffe3b8aa26e755ae5a0d93ab3d50e786a8157b2"
                                          "06e0195bf5608f38efcc47e0a965e03245a45ee4002648c12e6f067fbd417cdfe1b78c38a803e40913807f588e2896b47a6360a99cad7806ff18eed57956e3"
                                          "3c3f40acf7234295944241522d47f6eb9de506b0ca98c5138b7b271a8fc89702df5bdffca71cbd532580dbab6230f52c07653636eb15e0e3dd420489b25178"
                                          "644ab951e31b78032534541b14be8237504241e1fa76ddcb7e98a618a6b5f352435fa56acaac5f13b8ea0914db4b7a881336b41446cba8182508c18e9aeef1"
                                          "31c44ec8660967380593d252f7a8a23362bf12653c184090581fdc5e66f90a2a4c41ddd0280c789ec2a0a58a7d491995561185975484b9a0c5682f4708d298"
                                          "f292785e4f1c76c9dc1b638420ffd0d4ca83ac385a43ee25f73e8b939c288abe1095e965c27fc9ba4b2e33037c13264b1cdbbb4e0189644c8d1164cafdbf25"
                                          "63340c5d0505fc088127c94d62e6bdbbeae2d84574d10f24dbbb069b3e666d8f9a20562b1b0f5c263965bf70efce955b4962bf63eb15997b8ce86941f04776"
                                          "a925e02f6cfd62e06f2ee4d82f049e83165beb2fb0fac5a52c4b85c051b03c07ffe2caea3e8480588e2e4b803755808be98fad529bce0981ab502f0f1604eb"
                                          "8406abb3a480c3e4a64ef22cddec564a9207b1d224043e4537f269023cb1d2a41a6c52055c15597b6d7434c466772032d2fe9630b4286d78d8ec8108f548cc"
                                          "50b88a183c7a24463a143578e01a881550a20d483d16d7845863d9faf51c46e42f461e78a70f4a68295fb591bd181961967b5cfa7252a305ff72141887fb7a"
                                          "7ca4a50ce78084c6bd7c3e2293506f16ee21294d960de3989c8112feff8392423884795456106af587a57d382ecf27c2f1c30c6f1dc7e5251979951f4cd8c8"
                                          "0de17d32a3c80fabf8686afb6c6ea38d360a9abe051800f254aafc3cd00f220000000049454e44ae426082")
                   << QByteArray::fromHex("89504e470d0a1a0a0000000d4948445200000040000000400806000000aa6971de0000001974455874536f6674776172650041646f626520496d6167655265"
                                          "61647971c9653c000002c44944415478daec5beb7183300c0626a013846ec00675376083324237289d8011d24d4827a01b844c4037a0e64ebd4b1d1b3b5832"
                                          "76b1ee7cc98f446f7d36b24892489122ed99526a01d33415fc83f1f5c4d7eff7253af135f0f5397f4fd37408ceabb3d17cb57c9d277b3a03af2204c3195fdd"
                                          "4447336fe6a3e125b1e13247945e600057a4e11f6f063ffd82fabec07719cd461d00274c0c7ce718d16c19f5de2052355ff90afe39fc579759bd737c805a1f"
                                          "17943a622a05a07a5c90373ac30688ca52c40b42d9852623eaad8c1fc985dfea313a7502a4bdaa064bcf308851081b15c6e7c9460440d92b32b2c414d4fb66"
                                          "bc81137a2c010d95f1006acc365a0b4e6830529f24bd388f0a13bc16cab4b461da51a1ac84778fc053b64b7598a8df21d66e4751b38aa0312c4698a7bb1ab5"
                                          "5effe28a5de0144c8e44678b067bdf561c9b8b7b18b494d177d49011a9bd87c199aaf61d3a412ce1b38df76a070ae7c8fcea5559acf8634e64f4bc77bfc221"
                                          "a6c376e8aa404a00a44756ac82f41ca9cb4c723abc01f24cf23f314d4ec87ae5d0ee72f11c71d2d8267580b8255d30354ad3f483af87b99fe7c001178d6d52"
                                          "07c89a992ea243415addb3643b1a7cd82e3773802f575e59b2738a0e880ed05319b07de51a0788dbd32160071c745b6f66b03db1801dc0745bafcc019f621a"
                                          "513c0c51b7d4817fa9b1cda80466aab6a84f4baa4c6ccb14071431555e1ca42b7646883a0fc6872fca9618f4002ac545460b7dc2c25286754b8cac296a384a"
                                          "d358ca306e8aa64b8a4a50f4d1f60c0f3735ba741fd6ca0143c5fedf3c6ef77c2f23d28b1142f4efd0aecb29afc6888caf51834679394a603cfee528306e7c"
                                          "9d0db83ef4905c8f5f09d8ef808426bd7c1e9129b085ed77484a83b2fb18933370c2ff1f9414ca619fa3b28252c10f4bfb302eff7df56c10ceb8bc0491837c"
                                          "6182021bf6f7ca8c021f8278692abe36172952a45dd38f000300ba6f44b950bb7a480000000049454e44ae426082")
                   << QByteArray::fromHex("89504e470d0a1a0a0000000d4948445200000040000000400806000000aa6971de0000001974455874536f6674776172650041646f626520496d6167655265"
                                          "61647971c9653c000003a74944415478daec5add91da3010361a5ef2e612a082380d644c05211dd815802be054014705d04148053869e048054709bce53159"
                                          "cdeccd38cbda926cc93f177d331e668490bd3ffaf4ed9a280a0808080808f86f311be2a6bf7f7e59c0470ad702876e70951f3e7fbfbd6b07a0e147349e4309"
                                          "57dea723663d1a9fc0c705ae5833f50ed70a9c707d370eb030be7727889e1260cf18af8c93703d23075411e36fa69f0110fd0cf77d1512a2fb44e6a9391999"
                                          "a7f8e034590780512a92af24fa8aed5735f35f2b27c3db5658c2fcfb54b70097fa79c3fcbcefad203c463f65525a361d71f09d3a06cf6438c3b52697013472"
                                          "37243c1d724cfda6b5c6ed0088d8163e12325c98ec659c23c970826b8e9f046d89af619d17e2442f84e823038e96c457878221c4e3a8b70092d5da86f83484"
                                          "483963ed9a10e71ea26f447c60c81ac96d81cc2f19e92bf12489c93d96a3cb0030e88988985ae2c3aaf05b65be72c605f9831222dd0a0bbcd7781c80066dc8"
                                          "f0190c38d7fc2463c662e6e488500a97647883f71c4d0650c5c745ae0b0a5f0a513888fe9a21be83cba60672034788eb411d807bf641f1d14acf11245336ef"
                                          "296ff49d015b86f84ccefcb2e1e86b52880f8488cfd0bf039084760cf195be743b922a5d7fd78510bb64003df35d139f69c91c755188a265f415f9a41d88ef"
                                          "6638c665c18d2996d2b684285a18cf69722be2ab7194cda9c1f5118f6d08b14d06ec1c153b5db8e05ed33dda797500b6b729eb9e7c129f65f7688bcfe82d03"
                                          "f60e898f3aed474b85d8a97b242ca29f31c4277d766c0db9e4c01062e6d401358aef0a0ff01c0d0c24dfd60a5158a47eac29506c71ed700ae8b48171b1240c"
                                          "a29f32e5ab0be23b548cbe3284664b88275a729b748fe686d177aef870ff2e1dee8602abd2983cfba7d61950d3de1e94f834dac0ba9d3ed3105fe7f676dfb0"
                                          "6da70b4db1e39af8fa80553b7dd6407c17aabfc18b85c348ed2baa5291e057575d24b2f61b561c710b8b52573a343e230f98446e5f7a4846211e8db6003e1c"
                                          "6d30148e898f6b60a4ae166f68a767261940dbdba5877f69dc0d845157279c987a6363e280844927d7383106fbb88fd4d8f6488290267f8827bdfd8d06bb38"
                                          "6a3b9c7dfd375067cf3c1a100d6f8e7a83d0ed4f9bd27284a228d3718f306854ec6dbb2c23313e61ea98d2a4183a44ffbeea524aea051654e9fa6b22f67f8c"
                                          "1e5fd7454cf3a45609724a6aea60956c5331c4fd7373aa50fd8bdcaa18c21f1435a2652ab8a38acdadcb61a6384a27667c3944bb3e20202020206042f82bc0"
                                          "0087f380aa76a943de0000000049454e44ae426082")
                   << QByteArray::fromHex("89504e470d0a1a0a0000000d4948445200000040000000400806000000aa6971de0000001974455874536f6674776172650041646f626520496d6167655265"
                                          "61647971c9653c0000038e4944415478daec5aed8da3301005eb7e9f28215bc1e53a201da404a820a1822c1524a9003ad87410ae82e42a484a40d7c0de589a"
                                          "93d0640c36d87cecf9495624e218e6c3cf6f2604818787878787c77f8b708a9bfe89a2157cc4305678e909a3fa5ed7cf2fed0034bc40e3395430d2311d118e"
                                          "68fc1a3eae30a28ea9358c0d38e1fe651c6060fce84e102325c091315e1a97c33821073411e16f960f887e02e3938c77665ec1cc4b16bd05c00019c90789be"
                                          "64fb8d62fea37132fcdb0a6f30bf5eea16e0523f6d999f8ebd1584c3e8cba38ea670de76c4c177f218bc90cb09aeb5b80ca0917b22e17521c5d46f5b6bde0e"
                                          "8088ede1634d2e673a7b19e7e4e4f21ad79c3f099a125fcb3a37e2442784e822030a43e253216308b198f51640b2da9a105f072152ced8da2644e120fa5ac4"
                                          "078648631e28783e502e53e40c2116b37400aabb950ef16155f8d1982fb3e68afc4109916e8515a7242775001ab423972f60c045f1134ee246ccc9219d5062"
                                          "99dcc40eef399b0ca08a8f8bdc1064ae14a2b010fd2d437c679b4d0d2c8b3942dc4eea00dcb32f8a0f1ef83db08f9c299b8f9437c6ce803d437c3a677ed572"
                                          "f4b529c41742c46718df0148420786f82a57ba1d4995ae7f1842884332809ec7b6894fb7641ea40d44cfe84bf2890710df53f31a97054fa6588afb1262d8c3"
                                          "78aed891c4f766b8ce27e505dd82099fe166a37bd427030e968a9d215c502bba4707a75b00f53a65ddd225f119768ff68a9ac25a061c2d121f75daaf9e0a71"
                                          "50f74818443f61882f77d9b1d524c43343888955072814df1d1ee0144c0c549dbd15a23048fda8a34031c5bdcf31a8a90db48b25a111fd98295f6d10dfb961"
                                          "f49d213453422c69c9add33d0a351c304a73d24255cae913b94d7ff6ce00457b3b9f9bf10d6d60dc4e0f0d3d6adcde9e20138c325674143bb6896f0c18b5d3"
                                          "450bf1d1e2e264f38505b8c7b1f137f8cd568fcfb49d1e2a1ecee9dfd428548abec590cd824d281e8e4623b34c7c5cb4635b8bb7b4d3139d2db06322535ade"
                                          "a7b586301aea8492a937763a0e7839f61c1055c918ece23e79876daf1c401b15e04967afd16017476e878bab7703bbecf936b178b904134374edcf31ded472"
                                          "98614917f7088d46c5d1b4cb3213e3d74c4558e970803c8eaecc9a325d7f2fc4fe1f8c9093d8d02a562584a4e7f6c1d78254b29949315404fcdfd84b84ec5f"
                                          "a446c510fe20538896a5a046159bf66e883478215e98f1d514ed7a0f0f0f0f0f8f05e1af000300f095a629367881040000000049454e44ae426082")
                   << QByteArray::fromHex("89504e470d0a1a0a0000000d4948445200000038000000380806000000a8863b1e00000265494441546881ed9ac14a1c3118c77fabf6507ae82e2dba474fed"
                                          "a587d6d7f0507a28425f40ba82e051e8d573c14bf105bcf7450a3dd60790aeb86dad78d29a12f906c67cd94966765c264b7e10dc49fe937cff9d24df8e3360"
                                          "ccac6580310718738231371863662c37d2d781f45d195f68287542cdf206634e55afed955319636a5ca1a17a77c266ac01dfe5ef43f213780d8c7d6384a25f"
                                          "5235f17c9a8339cb50c66a44d32bd803ce80e7a5baafc01ef05ba9eb31003e036f4b679d03abbe0ba62a54a0cd0caec9d429b8059e017f94b2197d60e2ccb0"
                                          "a16f9a3ed4147dec1c5fb6680ee9eb32306614b3acc124b053f43df045a6d82261a7f8476bf07c01cd154c9664475c547ad6e0a885adbd8b584fa3224dd8ab"
                                          "f8d413a46b7c1db850aaf9e3c635f04470617fcc85f2a0db3868391d34e55e5ca662992d7c9ac80653271b8ce09ddc59d81f0c5b15f258dd9668cee49c19f1"
                                          "dc25978a7b8bdcf768c6a5f65f18d9997589d1f5a4add08d3d1a15970e33fe8e3e264dc4a692185ddf93e37c2920a789826c3075b2c1d4c90653271b4c9d6c"
                                          "3075b2c1d4c90653271b4c9d6c3075b2c1d4c90653a70d8393d2e7bf527cc4e8dcfa8952d4a40d833ba5c046f2ce8c8f18ddadb415ba1da5a8495b0f408b67"
                                          "fdff544b33ddb28cedfb12545c55ffd95e5135cd9816884bac2ef405449337990e32753afa0819bc768e874a317f5e0662bc47680dfe005e958e8f806de74d"
                                          "c379329418dc182bd00f17cb655f3d51ec5ed9af0a2994269e00df8017aaa51b9c001b06aea645135a83f6c44de9a88be636abcc5962dff8b5577217f8208b"
                                          "fc516b61d6c36e2876cd1d0387f60254460ffc07e885c7967334f1a70000000049454e44ae426082");

    for (int i = 0, n = listIcons.size(); i < n; ++i)
    {
        // 利用`QByteArray`生成`QImage`对象，再间接构造`QIcon`对象
        auto pix = QPixmap::fromImage(QImage::fromData(listPixmapData.at(i)));
        _hashBtnIcon.insert(listIcons.at(i), pix);
    }
}

void CSMessageBox::resizeUI()
{
    const QSize iconSize(64, 64);
    int titleH = 56;
    int iconX = 20;
    int iconY = 98;
    int txtX = 104;
    int txtY = 60;
    int txtW = 356;
    int txtH = 140;


    _labTitle->setGeometry(0, 0, width(), titleH);
    _labIcon->setGeometry(iconX, iconY, iconSize.width(), iconSize.width());
    _labText->setGeometry(txtX, txtY, txtW, txtH);

    // Other operations
    updateIcon();
    resizeButtons();
}

void CSMessageBox::resizeButtons()
{
    auto listBtns = buttons();
    const QSize btnSize(88, 32);
    const int space = 24;
    const int bottom = 14;
    int len = listBtns.size();
    int totalBtnW = (btnSize.width() + space) * len - space;
    int btnX = (width() - totalBtnW) / 2;
    int btnY = height() - bottom - btnSize.height();

    // Let the buttons aligned in the center of horizontal layout
    for (auto btn : listBtns)
    {
        if (!btn) continue;

        btn->setGeometry(btnX, btnY, btnSize.width(), btnSize.height());
        btnX += btnSize.width() + space;
    }
}

/**
 * @brief Update icon
 */
void CSMessageBox::updateIcon()
{
    if (!_iconPix.isNull()) _labIcon->setPixmap(_iconPix);
}

void CSMessageBox::btnClickSlot()
{
    _btnClicked = dynamic_cast<QPushButton *>(sender());
    if (!_btnClicked) return;

    close();
}

}   // `cs`

