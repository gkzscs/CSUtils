#ifndef CSUTILS_GLOBAL_H
#define CSUTILS_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef CSUTILS_LIB
#   define CSUTILS_EXPORT  Q_DECL_EXPORT
#else
#   define CSUTILS_EXPORT  Q_DECL_IMPORT
#endif


#endif // CSUTILS_GLOBAL_H
