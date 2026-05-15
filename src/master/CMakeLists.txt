file(GLOB_RECURSE MASTER_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/master/*.h"
    "${CMAKE_SOURCE_DIR}/src/master/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/master/*.c"
    "${CMAKE_SOURCE_DIR}/src/master/*.cpp"
)

add_executable(master
    ${MASTER_SOURCE}
)