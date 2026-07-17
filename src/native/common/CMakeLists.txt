file(GLOB_RECURSE COMMON_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/native/common/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/native/common/src/*.cc"
)

include_directories(
    "${Protobuf_INCLUDE_DIRS}"
    "${CMAKE_SOURCE_DIR}/src/native/common/include"
    "${CMAKE_SOURCE_DIR}/src/native/common/include/verteilen2/proto_gen"
    "${CMAKE_SOURCE_DIR}/src/native/common/verteilen2/proto_gen"
    "${CMAKE_SOURCE_DIR}/lib/sqlite/include"
    "${CMAKE_SOURCE_DIR}/lib/libhv/include"
    "${CMAKE_SOURCE_DIR}/lib/uuid/include"
    "${CMAKE_SOURCE_DIR}/lib/json/include"
    "${CMAKE_SOURCE_DIR}/lib/efsw/include"
    "${CMAKE_SOURCE_DIR}/lib/kcp"
)

add_library(common STATIC
    ${COMMON_SOURCE}
    ${PROTO_SOURCES}
    "${CMAKE_SOURCE_DIR}/lib/kcp/ikcp.c"
)

target_link_libraries(common PUBLIC
    hv
    stduuid
    SQLiteCpp
    sqlite3
    efsw
    ${Protobuf_LIBRARIES}
)