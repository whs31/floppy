#pragma once

#if defined(QT_VERSION) && defined(QT_VERSION_CHECK)
#  ifndef RLL_SELECT_QT
#    if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#      define RLL_SELECT_QT(LHS, RHS) LHS
#    else
#      define RLL_SELECT_QT(LHS, RHS) RHS
#    endif
#  endif
#endif
