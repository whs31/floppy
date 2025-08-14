#pragma once

#include <oslayer/base.h>

#ifdef RLL_OS_WINDOWS
#  include <oslayer/win/app_path.h>
#else
#  include <oslayer/linux/app_path.h>
#endif
