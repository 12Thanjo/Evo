#pragma once

#include <limits>
#include <cstdint>
#include <cstring>
#include <string.h>
#include <initializer_list>
#include <array>
#include <span>
#include <vector>
#include <string>
#include <optional>
#include <format>
#include <utility>
#include <cmath>


#include "./defines.h"


#include "./utils/platform_detection.h"
#include "./utils/asserts.h"
#include "./utils/misc.h"
#include "./utils/numeric_types.h"
#include "./utils/select_size_type.h"
#include "./utils/strings.h"


#include "./tools/logging.h"


#include "./containers/Defer.h"
#include "./containers/Result.h"
#include "./containers/Expected.h"
#include "./containers/iterators.h"
#include "./containers/ArrayProxy.h"
#include "./containers/Flags.h"
#include "./containers/StaticVector.h"
#include "./containers/SmallVector.h"
#include "./containers/StaticString.h"
#include "./containers/CStrProxy.h"
#include "./containers/Bimap.h"
#include "./containers/Variant.h"


#include "./tools/fs.h"
#include "./tools/time.h"
#include "./tools/random.h"
