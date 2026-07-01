file(GLOB_RECURSE SERVER_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/server/*.h"
    "${CMAKE_SOURCE_DIR}/src/server/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/server/*.c"
    "${CMAKE_SOURCE_DIR}/src/server/*.cpp"
)

add_executable(server
    ${SERVER_SOURCE}
)