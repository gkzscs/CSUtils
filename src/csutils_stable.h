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

// Menu
#include <QMenu>
#include <QAction>
#include <QWidgetAction>
#include <QSystemTrayIcon>

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
#include <QFontDatabase>
#include <QFontMetrics>
#include <QToolTip>

// Container
#include <QVector>
#include <QList>

// Application
#include <QSharedMemory>
#include <QApplication>
#include <QProcess>
#include <QThread>
#include <QTimer>

// Sockets
#include <QLocalSocket>
#include <QLocalServer>

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
#include <Layout/csgridlayout.h>

// Control
#include <Control/cswidget.h>
#include <Control/csline.h>
#include <Control/csscrollarea.h>
#include <Control/csformcard.h>
#include <Control/csfoldbox.h>
#include <Control/cspairctrl.h>
#include <Control/csswitchbutton.h>

// Animation
#include <Animation/csanimation.h>
#include <Animation/cswaitanimation.h>

// Communication
#include <Communication/csappconnector.h>
#include <Communication/csipchelper.h>
#include <Communication/cslocalclient.h>
#include <Communication/cslocalserver.h>


#endif  // __cplusplus
#endif  // CSUTILS_STABLE_H



