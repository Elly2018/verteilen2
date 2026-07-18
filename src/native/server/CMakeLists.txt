file(GLOB_RECURSE SERVER_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/server/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/server/src/*.cc"
)

include_directories(
    "${CMAKE_SOURCE_DIR}/src/server/include"
    "${CMAKE_SOURCE_DIR}/src/common/include"
    "${CMAKE_SOURCE_DIR}/src/common/include/verteilen2/proto_gen"
    "${CMAKE_SOURCE_DIR}/lib/argh"
    "${CMAKE_SOURCE_DIR}/lib/json/include"
    "${CMAKE_SOURCE_DIR}/lib/crow/include"
    "${CMAKE_SOURCE_DIR}/lib/mdns/include"
    "${CMAKE_SOURCE_DIR}/lib/sqlite/include"
    "${CMAKE_SOURCE_DIR}/lib/spdlog/include"
    "${CMAKE_SOURCE_DIR}/lib/libhv/include"
    "${CMAKE_SOURCE_DIR}/lib/kcp"
)

link_libraries(
    common 
    Crow::Crow
    mdns_cpp::mdns_cpp
    SQLiteCpp
    sqlite3
    pthread
    dl
    spdlog
    hv
    ${Protobuf_LIBRARIES}
)

add_executable(server
    ${SERVER_SOURCE}
    "${CMAKE_SOURCE_DIR}/lib/kcp/ikcp.c"
)

list(REMOVE_ITEM SERVER_SOURCE "${CMAKE_SOURCE_DIR}/src/native/server/src/verteilen2server/main.cc")

add_library(server_share SHARED
    ${SERVER_SOURCE}
    "${CMAKE_SOURCE_DIR}/lib/kcp/ikcp.c"
)