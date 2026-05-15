file(GLOB_RECURSE PROXY_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/proxy/*.h"
    "${CMAKE_SOURCE_DIR}/src/proxy/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/proxy/*.c"
    "${CMAKE_SOURCE_DIR}/src/proxy/*.cpp"
)

add_executable(proxy
    ${PROXY_SOURCE}
)