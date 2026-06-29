file(GLOB_RECURSE COMMON_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/common/*.h"
    "${CMAKE_SOURCE_DIR}/src/common/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/common/*.c"
    "${CMAKE_SOURCE_DIR}/src/common/*.cpp"
)

add_library(common
    ${COMMON_SOURCE}
)