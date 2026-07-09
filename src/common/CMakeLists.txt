file(GLOB_RECURSE COMMON_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/common/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/common/src/*.cc"
    "${CMAKE_SOURCE_DIR}/src/common/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/common/src/proto_gen/*.cc"
)

include_directories(
    "${Protobuf_INCLUDE_DIRS}"
    "${CMAKE_SOURCE_DIR}/src/common/include"
    "${CMAKE_SOURCE_DIR}/src/common/include/verteilen2/proto_gen"
    "${CMAKE_SOURCE_DIR}/src/common/verteilen2/proto_gen"
    "${CMAKE_SOURCE_DIR}/lib/sqlite/include"
    "${CMAKE_SOURCE_DIR}/lib/libhv/include"
    "${CMAKE_SOURCE_DIR}/lib/uuid/include"
    "${CMAKE_SOURCE_DIR}/lib/json/include"
)

add_library(common STATIC
    ${COMMON_SOURCE}
    ${PROTO_SOURCES}
)

target_link_libraries(common PUBLIC
    hv
    stduuid
    SQLiteCpp
    sqlite3
    ${Protobuf_LIBRARIES}
)