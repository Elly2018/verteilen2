file(GLOB_RECURSE CLIENT_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/client/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/client/src/*.cc"
    "${CMAKE_SOURCE_DIR}/src/client/src/*.cpp"
)

include_directories(
    "${CMAKE_SOURCE_DIR}/src/client/include"
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
    kcp
    ${Protobuf_LIBRARIES}
)

add_executable(client
    ${CLIENT_SOURCE}
)