file(GLOB_RECURSE CLIENT_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/client/*.h"
    "${CMAKE_SOURCE_DIR}/src/client/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/client/*.c"
    "${CMAKE_SOURCE_DIR}/src/client/*.cpp"
)

include_directories(
    "${CMAKE_SOURCE_DIR}/src/common"
    "${CMAKE_SOURCE_DIR}/lib/crow/include"
    "${CMAKE_SOURCE_DIR}/lib/mdns/include"
    "${CMAKE_SOURCE_DIR}/lib/sqlite/include"
    "${CMAKE_SOURCE_DIR}/lib/spdlog/include"
    "${CMAKE_SOURCE_DIR}/lib/asio/include"
    "${CMAKE_SOURCE_DIR}/lib/beast/include"
)

link_libraries(
    Threads::Threads
    common 
    Crow::Crow
    mdns_cpp::mdns_cpp
    SQLiteCpp
    sqlite3
    pthread
    dl
    spdlog
    local_asio
    local_beast
)

add_executable(client
    ${CLIENT_SOURCE}
)

if(WIN32)
    target_link_libraries(client PRIVATE ws2_32 mswsock)
endif()