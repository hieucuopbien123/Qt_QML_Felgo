#ifndef LIBDLL_GLOBAL_H
#define LIBDLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBDLL_LIBRARY)//định nghĩa bằng biến DEFINED trong pro rằng nó là 1 lib r thì cho nó quyền export
#  define LIBDLL_EXPORT Q_DECL_EXPORT
//định nghĩa ra LIBDLL_EXPORT để dùng cho dll, t có thể dùng Q_DECL_EXPORT trực tiếp nhưng làm v để specific
#else
#  define LIBDLL_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBDLL_GLOBAL_H
