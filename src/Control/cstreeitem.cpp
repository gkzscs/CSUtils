#include "cstreeitem.h"
#include "cstree.h"


namespace cs
{

CSTreeItem::CSTreeItem()
    : cs::CSWidget(nullptr), _parent(nullptr)
{
    initMember();
    initUI();
    initSignalSlot();
}

CSTreeItem::CSTreeItem(CSTree *parent)
    : cs::CSWidget(parent)
{
    initMember();
    initUI();

    parent->addTopLevelItem(this);
}

CSTreeItem::CSTreeItem(CSTreeItem *parent)
    : cs::CSWidget(parent)
{
    initMember();
    initUI();

    parent->addChild(this);
}

CSTreeItem::~CSTreeItem()
{
    _parent = nullptr;
    DELETE_Q_POINTER(_btnExpand);
    DELETE_Q_CONTAINER(_listChildren);
}

void CSTreeItem::setExpanded(bool flag)
{
    _expanded = flag;
    refresh();
}

void CSTreeItem::setSelected(bool flag)
{
    if (_selected != flag) emit selectedChanged(flag);

    _selected = flag;
    updateStyle();
}

void CSTreeItem::setExpandIcons(const QIcon &iconExpanded, const QIcon &iconUnexpanded)
{
    _pairExpandIcons.first = iconExpanded;
    _pairExpandIcons.second = iconUnexpanded;

    updateExpandButton();
}

/**
 * @brief Set the indent of children items
 * @param n
 */
void CSTreeItem::setIndent(int n)
{
    auto margins = _layout->margins();
    margins.setLeft(n);

    _layout->setMargins(margins);
}

/**
 * @brief CSTreeItem::setSpace
 * @param n
 */
void CSTreeItem::setSpace(int n)
{
    // Modify the margins at the same time
    auto margins = _layout->margins();
    margins.setTop(margins.top() + n);
    _layout->setMargins(margins);

    dynamic_cast<cs::CSVBoxLayout *>(_layout)->setSpace(n);
}

void CSTreeItem::addChild(CSTreeItem *child)
{
    if (!child) return;
    if (_listChildren.contains(child)) _listChildren.removeAll(child);

    child->_parent = this;
    _listChildren.append(child);
    refresh();
}

bool CSTreeItem::insertChild(int idx, CSTreeItem *child)
{
    if (!child) return false;
    if (_listChildren.contains(child)) _listChildren.removeAll(child);
    if (idx <= 0) _listChildren.prepend(child);
    if (idx >= _listChildren.size()) _listChildren.append(child);

    child->_parent = this;
    _listChildren.insert(idx, child);
    refresh();
    return true;
}

bool CSTreeItem::removeChild(CSTreeItem *child)
{
    if (!child) return false;

    child->_parent = nullptr;
    bool res = _listChildren.removeAll(child);
    refresh();

    return res;
}

bool CSTreeItem::removeChild(int idx)
{
    auto kid = child(idx);
    return removeChild(kid);
}

void CSTreeItem::removeChildren()
{
    for (auto child : _listChildren)
    {
        child->_parent = nullptr;
    }

    _listChildren.clear();
    refresh();
}

void CSTreeItem::clear()
{
    _layout->clear();

    DELETE_Q_CONTAINER(_listChildren);
}

/**
 * @brief CSTreeItem::space
 * @return
 */
int CSTreeItem::space() const
{
    return dynamic_cast<cs::CSVBoxLayout *>(_layout)->space();
}

bool CSTreeItem::expanded() const
{
    return _expanded;
}

bool CSTreeItem::selected() const
{
    return _selected;
}

bool CSTreeItem::empty() const
{
    return (_listChildren.size() == 0);
}

int CSTreeItem::childCount() const
{
    return _listChildren.size();
}

int CSTreeItem::indexOfChild(CSTreeItem *child)
{
    if (!child) return -1;
    return _listChildren.indexOf(child);
}

/**
 * @brief Get the root of the tree
 * @return
 */
const CSTreeItem *CSTreeItem::root() const
{
    const CSTreeItem *ancestor = this;

    while (ancestor->parent())
    {
        ancestor = ancestor->parent();
    }

    return ancestor;
}

CSTreeItem *CSTreeItem::parent() const
{
    return _parent;
}

CSTreeItem *CSTreeItem::child(int idx) const
{
    if (idx < 0 || idx >= _listChildren.size()) return nullptr;
    return _listChildren.at(idx);
}

QList<CSTreeItem *> CSTreeItem::children() const
{
    return _listChildren;
}

/**
 * @brief Get all selected children
 * @return
 */
QList<CSTreeItem *> CSTreeItem::selectedChildren() const
{
    QList<CSTreeItem *> listItems;

    for (auto child : children())
    {
        if (!child->selected()) continue;
        listItems.append(child);
    }

    return listItems;
}

void CSTreeItem::resizeEvent(QResizeEvent *e)
{
    cs::CSWidget::resizeEvent(e);

    // Set geometry
    int x = 0;
    int y = (_sizeOrigin.height() - _btnExpand->height()) / 2;

    _wgtContainer->setGeometry(0, 0, width(), _sizeOrigin.height());
    _btnExpand->move(x, y);
}

void CSTreeItem::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)

    if (_wgtContainer->geometry().contains(e->pos())) setSelected(true);
}

/**
 * @brief Unpolish and polish the style sheet
 */
void CSTreeItem::updateStyle()
{
    cs::CSUtils::updateStyleSheet(this);
    cs::CSUtils::updateStyleSheet(_wgtContainer);
}

/**
 * @brief Refresh ui, adjust the layouot
 */
void CSTreeItem::refresh()
{
    // Clear layout
    _layout->clear();

    // Reset layout
    if (_expanded)
    {
        for (auto item : _listChildren)
        {
            _layout->add(item);
        }
    }

    // Update expand button
    updateExpandButton();
}

/**
 * @brief Set current icon shown on expand button
 */
void CSTreeItem::updateExpandButton()
{
    if (_expanded)
    {
        _btnExpand->setIcon(_pairExpandIcons.first);
    }
    else
    {
        _btnExpand->setIcon(_pairExpandIcons.second);
    }

    // Set the hidden attribute of expand button
    _btnExpand->setHidden(_listChildren.isEmpty());
}

/**
 * @brief Set the original size of this item control
 * @param s
 */
void CSTreeItem::setOriginSize(const QSize &s)
{
    // Resize
    _sizeOrigin = s;
    resize(s);

    // Set layout
    auto margins = _layout->margins();
    margins.setTop(s.height());
    _layout->setMargins(margins);
}

void CSTreeItem::initMember()
{
    _wgtContainer = new cs::CSWidget(this);
    _btnExpand = cs::CSUtils::createToolButton(QSize(24, 24), _wgtContainer);
    _layout = new CSVBoxLayout(this);

    setExpanded(true);
    setSelected(false);

    // Initialize icons
    initIcons();

    // Set object name
    _wgtContainer->setObjectName("wgt_container");
    _btnExpand->setObjectName("btn_expand");
}

void CSTreeItem::initUI()
{
    // Set attributes
    setOriginSize(QSize(100, 30));

    // Set layout
    setIndent(20);
    setSpace(0);
}

void CSTreeItem::initSignalSlot()
{
    connect(_btnExpand, &QToolButton::clicked, this, &CSTreeItem::btnExpandClickSlot);
}

void CSTreeItem::initIcons()
{
    auto iconExpanded = QIcon(QPixmap::fromImage(QImage::fromData(QByteArray::fromHex(
         "3c3f786d6c2076657273696f6e3d22312e302220656e636f64696e673d227574662d38223f3e0a3c212d2d2047656e657261746f723a2041646f626520496c6c"
         "7573747261746f722032332e312e312c20535647204578706f727420506c75672d496e202e205356472056657273696f6e3a20362e3030204275696c64203029"
         "20202d2d3e0a3c7376672076657273696f6e3d22312e31222069643d22e59bbee5b1825f312220786d6c6e733d22687474703a2f2f7777772e77332e6f72672f"
         "323030302f7376672220786d6c6e733a786c696e6b3d22687474703a2f2f7777772e77332e6f72672f313939392f786c696e6b2220783d223070782220793d22"
         "307078220a092076696577426f783d2230203020323420323422207374796c653d22656e61626c652d6261636b67726f756e643a6e6577203020302032342032"
         "343b2220786d6c3a73706163653d227072657365727665223e0a3c7374796c6520747970653d22746578742f637373223e0a092e7374307b66696c6c3a236666"
         "666666663b7d0a3c2f7374796c653e0a3c673e0a093c7061746820636c6173733d227374302220643d224d31322e372c31362e326c372e312d372e3163302e34"
         "2d302e342c302e342d312c302d312e34632d302e342d302e342d312d302e342d312e342c304c31322c31342e314c352e362c372e38632d302e342d302e342d31"
         "2d302e342d312e342c30632d302e342c302e342d302e342c312c302c312e340a09096c372e312c372e314331312e372c31362e362c31322e332c31362e362c31"
         "322e372c31362e327a222f3e0a3c2f673e0a3c2f7376673e0a"))));
    auto iconUnexpanded = QIcon(QPixmap::fromImage(QImage::fromData(QByteArray::fromHex(
         "3c3f786d6c2076657273696f6e3d22312e302220656e636f64696e673d227574662d38223f3e0a3c212d2d2047656e657261746f723a2041646f626520496c6c"
         "7573747261746f722032332e312e312c20535647204578706f727420506c75672d496e202e205356472056657273696f6e3a20362e3030204275696c64203029"
         "20202d2d3e0a3c7376672076657273696f6e3d22312e31222069643d22e59bbee5b1825f312220786d6c6e733d22687474703a2f2f7777772e77332e6f72672f"
         "323030302f7376672220786d6c6e733a786c696e6b3d22687474703a2f2f7777772e77332e6f72672f313939392f786c696e6b2220783d223070782220793d22"
         "307078220a092076696577426f783d2230203020323420323422207374796c653d22656e61626c652d6261636b67726f756e643a6e6577203020302032342032"
         "343b2220786d6c3a73706163653d227072657365727665223e0a3c7374796c6520747970653d22746578742f637373223e0a092e7374307b66696c6c3a236666"
         "666666663b7d0a3c2f7374796c653e0a3c673e0a093c7061746820636c6173733d227374302220643d224d31362e322c31312e334c392e322c342e32632d302e"
         "342d302e342d312d302e342d312e342c30632d302e342c302e342d302e342c312c302c312e346c362e342c362e346c2d362e342c362e34632d302e342c302e34"
         "2d302e342c312c302c312e3463302e342c302e342c312c302e342c312e342c300a09096c372e312d372e314331362e362c31322e332c31362e362c31312e372c"
         "31362e322c31312e337a222f3e0a3c2f673e0a3c2f7376673e0a"))));

    setExpandIcons(iconExpanded, iconUnexpanded);
}

void CSTreeItem::btnExpandClickSlot()
{
    setExpanded(!_expanded);

    emit expandedChanged(_expanded);
}

}   // `cs`
