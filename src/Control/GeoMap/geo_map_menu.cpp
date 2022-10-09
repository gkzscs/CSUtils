#include "geo_map_menu.h"


namespace cs
{

GeoMapMenu::GeoMapMenu(QWidget *parent)
    : cs::CSWidget(parent)
{
    init_member();
    init_ui();
}

void GeoMapMenu::add_action(const QPixmap &pix, const QString &txt)
{
    auto act = new cs::GeoMapAction(pix, txt, this);
    add_action(act);
}

void GeoMapMenu::add_action(GeoMapAction *act)
{
    if (!_layout->isEmpty())
    {
        add_seperator();
    }
    _layout->add(act);

    add_connection(act);
}

void GeoMapMenu::add_actions(const QList<GeoMapAction *> &listActs)
{
    for(auto act: listActs){
        add_action(act);
    }
}

void GeoMapMenu::insert_action(int idx, GeoMapAction *act)
{
    auto globalIdx = action_index_2_global(idx);
    if (!_layout->isEmpty())
    {
        _layout->insert(globalIdx-1, new cs::CSLine(this));
    }
    _layout->insert(globalIdx, act);

    add_connection(act);
}

void GeoMapMenu::remove_action(GeoMapAction *act)
{
    int idx = index_of_action(act);
    remove_action(idx);
}

void GeoMapMenu::remove_action(int idx)
{
    auto act = find_action(idx);
    if (!act) return;

    remove_connection(act);

    auto globalIdx = action_index_2_global(idx);
    _layout->remove(globalIdx+1);
    _layout->remove(globalIdx);
}

void GeoMapMenu::clear()
{
//    _layout->deepClear();
    _layout->clear();
}

void GeoMapMenu::deepclear()
{
    _layout->deepClear();
}

int GeoMapMenu::index_of_action(GeoMapAction *ctrl) const
{
    auto listCtrls = all_actions();
    return listCtrls.indexOf(ctrl);
}

GeoMapAction *GeoMapMenu::find_action(int idx) const
{
    auto globalIdx = action_index_2_global(idx);
    return dynamic_cast<GeoMapAction *>(_layout->at(globalIdx));
}

GeoMapAction *GeoMapMenu::find_action(const QString &txt) const
{
    for (auto item : _layout->allItems())
    {
        auto ctrl = dynamic_cast<GeoMapAction *>(item);
        if (!ctrl || ctrl->text() != txt) continue;

        return ctrl;
    }

    return nullptr;
}

QList<GeoMapAction *> GeoMapMenu::all_actions() const
{
    QList<GeoMapAction *> listCtrls;
    for (auto item : _layout->allItems())
    {
        auto ctrl = dynamic_cast<GeoMapAction *>(item);
        if (!ctrl) continue;

        listCtrls.append(ctrl);
    }

    return listCtrls;
}

void GeoMapMenu::show(const QPoint &pos)
{
    move(pos);
    cs::CSWidget::show();
}

void GeoMapMenu::init_member()
{
    _layout = new cs::CSVBoxLayout(this);
}

void GeoMapMenu::init_ui()
{
    resize(260, 196);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground);

    _layout->setMargins(4, 4, 4, 4);
    dynamic_cast<cs::CSVBoxLayout *>(_layout)->setSpace(4);
}

void GeoMapMenu::add_connection(GeoMapAction *act)
{
    if (!act) return;
    connect(act, &GeoMapAction::triggered, this, &GeoMapMenu::action_triggered_slot);
}

void GeoMapMenu::remove_connection(GeoMapAction *act)
{
    if (!act) return;
    disconnect(act, &GeoMapAction::triggered, this, &GeoMapMenu::action_triggered_slot);
}

void GeoMapMenu::add_seperator()
{
    _layout->add(new cs::CSLine(this));
}

int GeoMapMenu::action_index_2_global(int idx) const
{
    return (idx * 2);
}

void GeoMapMenu::action_triggered_slot()
{
    auto act = dynamic_cast<GeoMapAction *>(sender());
    if (!act) return;

    emit action_triggered_signal(act);
    hide();
}


}   // cs
