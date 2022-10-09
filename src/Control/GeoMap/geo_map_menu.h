#ifndef GEO_MAP_MENU_H
#define GEO_MAP_MENU_H

#include "Control/Base/cswidget.h"
#include "geo_map_action.h"


namespace cs
{

class CSUTILS_EXPORT GeoMapMenu : public cs::CSWidget
{
    Q_OBJECT

public:
    GeoMapMenu(QWidget *parent = nullptr);

    void add_action(const QPixmap &pix, const QString &txt);
    void add_action(GeoMapAction *act);
    void add_actions(const QList<GeoMapAction *> &listActs);
    void insert_action(int idx, GeoMapAction *act);
    void remove_action(GeoMapAction *act);
    void remove_action(int idx);
    void clear();
    void deepclear();
    int index_of_action(GeoMapAction *ctrl) const;
    GeoMapAction *find_action(int idx) const;
    GeoMapAction *find_action(const QString &txt) const;
    QList<GeoMapAction *> all_actions() const;

    void show(const QPoint &pos = QPoint());

private:
    void init_member();
    void init_ui();

private:
    void add_connection(GeoMapAction *act);
    void remove_connection(GeoMapAction *act);

    void add_seperator();

    int action_index_2_global(int idx) const;

signals:
    void action_triggered_signal(GeoMapAction *act);

private slots:
    void action_triggered_slot();

};

}   // cs

#endif // GEO_MAP_MENU_H
