file(GLOB_RECURSE MASTER_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/master/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/master/src/*.cc"
    "${CMAKE_SOURCE_DIR}/src/master/src/*.cpp"
)

include_directories(
    "${CMAKE_SOURCE_DIR}/src/master/include"
    "${CMAKE_SOURCE_DIR}/src/common/include"
    "${CMAKE_SOURCE_DIR}/src/common/include/verteilen2/proto_gen"
    "${CMAKE_SOURCE_DIR}/lib/argh"
    "${CMAKE_SOURCE_DIR}/lib/json/include"
    "${CMAKE_SOURCE_DIR}/lib/crow/include"
    "${CMAKE_SOURCE_DIR}/lib/sqlite/include"
    "${CMAKE_SOURCE_DIR}/lib/spdlog/include"
    "${CMAKE_SOURCE_DIR}/lib/libhv/include"
)

link_libraries(
    common 
    Crow::Crow
    SQLiteCpp
    sqlite3
    pthread
    dl
    spdlog
    hv
    ${Protobuf_LIBRARIES}
)

add_executable(master
    ${MASTER_SOURCE}
)