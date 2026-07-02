file(GLOB_RECURSE COMMON_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/common/*.h"
    "${CMAKE_SOURCE_DIR}/src/common/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/common/*.c"
    "${CMAKE_SOURCE_DIR}/src/common/*.cpp"
)

include_directories(
    "${CMAKE_SOURCE_DIR}/src/common"
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