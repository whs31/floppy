#pragma once

#include <rll/global/definitions.h>

#if defined(RLL_QT_CORE) || defined(RLL_DOC)
#  include <qobject.h>

namespace rll::qt {
  struct qobject_async_deleter {
    void operator()(QObject* ptr) const { ptr->deleteLater(); }
  };
}  // namespace rll::qt

#endif
