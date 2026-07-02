file(GLOB_RECURSE COMMON_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/common/*.h"
    "${CMAKE_SOURCE_DIR}/src/common/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/common/*.c"
    "${CMAKE_SOURCE_DIR}/src/common/*.cpp"
)

include_directories(
    "${CMAKE_SOURCE_DIR}/lib/libhv/include"
)

link_libraries(
    hv
)

add_library(common
    ${COMMON_SOURCE}
)