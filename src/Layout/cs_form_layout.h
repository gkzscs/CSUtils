#ifndef CSFormLayout_H
#define CSFormLayout_H

#include "Layout/cslayout.h"


namespace cs
{

class CSUTILS_EXPORT CSFormLayout : public cs::CSLayout
{
    Q_OBJECT

public:
    CSFormLayout(CSWidget *wgt = nullptr);

    void set_spaces(int hSpace, int vSpace);
    void set_horizontal_space(int space);
    void set_vertical_space(int space);
    int horizontal_space() const;
    int vertical_space() const;

    void set_column_count(int n);
    int column_count() const;

private:
    void init_member();

private:
    void resetLayout() override;

    void recalc_all_properties();
    void reset_all_geometries();

private slots:
    void resizeSlot(QObject *s, QResizeEvent *e) override;

private:
    int _space_h;
    int _space_v;
    int _col_count;

private:
    // Assist variables
    int _col_w;
    int _row_h;

};

}   // cs

#endif // CSFormLayout_H
