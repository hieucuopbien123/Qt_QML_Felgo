#ifndef LIBDLL_GLOBAL_H
#define LIBDLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBDLL_LIBRARY)
#  define LIBDLL_EXPORT Q_DECL_EXPORT
#else
#  define LIBDLL_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBDLL_GLOBAL_H
