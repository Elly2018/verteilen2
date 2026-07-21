file(GLOB_RECURSE CLIENT_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/native/client/src/*.cc"
)

include_directories(
    "${CMAKE_SOURCE_DIR}/src/native/client/include"
    "${CMAKE_SOURCE_DIR}/src/native/common/include"
    "${CMAKE_SOURCE_DIR}/src/native/common/include/verteilen2/proto_gen"
    "${CMAKE_SOURCE_DIR}/lib/argh"
    "${CMAKE_SOURCE_DIR}/lib/json/include"
    "${CMAKE_SOURCE_DIR}/lib/efsw/include"
    "${CMAKE_SOURCE_DIR}/lib/crow/include"
    "${CMAKE_SOURCE_DIR}/lib/mdns/include"
    "${CMAKE_SOURCE_DIR}/lib/sqlite/include"
    "${CMAKE_SOURCE_DIR}/lib/spdlog/include"
    "${CMAKE_SOURCE_DIR}/lib/libhv/include"
    "${CMAKE_SOURCE_DIR}/lib/grpc/include"
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
    efsw
    ${Protobuf_LIBRARIES}
)

add_executable(client
    ${CLIENT_SOURCE}
)

list(REMOVE_ITEM CLIENT_SOURCE "${CMAKE_SOURCE_DIR}/src/native/client/src/verteilen2client/main.cc")

add_library(client_share SHARED
    ${CLIENT_SOURCE}
    "${CMAKE_SOURCE_DIR}/lib/kcp/ikcp.c"
)