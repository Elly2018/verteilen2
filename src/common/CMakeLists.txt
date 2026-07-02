file(GLOB_RECURSE COMMON_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/common/*.h"
    "${CMAKE_SOURCE_DIR}/src/common/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/common/*.c"
    "${CMAKE_SOURCE_DIR}/src/common/*.cpp"
)

include_directories(
    "${CMAKE_SOURCE_DIR}/lib/asio/include"
    "${CMAKE_SOURCE_DIR}/lib/beast/include"
)

link_libraries(
    Threads::Threads
    local_boost
    local_asio
    local_beast
)

add_library(common
    ${COMMON_SOURCE}
)

if(WIN32)
    target_link_libraries(common PRIVATE ws2_32 mswsock)
endif()