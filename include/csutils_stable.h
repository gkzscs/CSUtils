#ifndef CSUTILS_STABLE_H
#define CSUTILS_STABLE_H


// Add C++ includes here
#ifdef __cplusplus

/**************************************** Qt Includes ************************************/
// Widgets
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QToolBar>

// View
#include <QListView>
#include <QTableView>
#include <QTreeView>

// Layout
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>

// Shape
#include <QPoint>
#include <QLine>
#include <QSize>
#include <QRect>
#include <QMargins>

// Paint
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QBrush>
#include <QStyleOption>

#include <QBitmap>
#include <QIcon>
#include <QPixmap>
#include <QImage>
#include <QMovie>

#include <QFont>
#include <QToolTip>

// Container
#include <QVector>
#include <QList>

// Qt events
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QCloseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>

// Drag
#include <QMimeData>
#include <QDrag>

#include <QDebug>
#include <QFile>
#include <QSharedMemory>
#include <QApplication>

#include <QThread>
#include <QTimer>
#include <QIntValidator>
#include <QRegExp>

// Animation
#include <QPropertyAnimation>

// Json
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonDocument>




/**************************************** CS Utils Library ************************************/
// Core
#include <Core/csutils.h>
#include <Core/csappevent.h>
#include <Core/cscontainer.h>

// Layout
#include <Layout/cslayout.h>
#include <Layout/cshboxlayout.h>
#include <Layout/csvboxlayout.h>

// Control
#include <Control/cswidget.h>
#include <Control/csline.h>
#include <Control/csscrollarea.h>
#include <Control/csformcard.h>

// Own utilities
//#include "controlcontainer.h"
//#include "foldingbox.h"
//#include "formcard.h"
//#include "labelcontrol.h"
//#include "splitline.h"
//#include "appevent.h"



#endif  // __cplusplus
#endif  // CSUTILS_STABLE_H



