file(GLOB_RECURSE COMMON_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/common/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/common/src/*.cpp"
)

include_directories(
    "${CMAKE_SOURCE_DIR}/src/common/include"
    "${CMAKE_SOURCE_DIR}/src/common/include/verteilen2/proto_gen"
    "${CMAKE_SOURCE_DIR}/src/common/verteilen2/proto_gen"
    "${CMAKE_SOURCE_DIR}/lib/libhv/include"
)

add_library(common STATIC
    ${COMMON_SOURCE}
)

target_link_libraries(common PUBLIC
    hv
    ${PROTOBUF_C_LIBRARIES}
)