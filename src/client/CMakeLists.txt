file(GLOB_RECURSE CLIENT_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/client/*.h"
    "${CMAKE_SOURCE_DIR}/src/client/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/client/*.c"
    "${CMAKE_SOURCE_DIR}/src/client/*.cpp"
)

include_directories(
    "${CMAKE_SOURCE_DIR}/src/common"
    "${CMAKE_SOURCE_DIR}/src/common/verteilen2/proto_gen"
    "${CMAKE_SOURCE_DIR}/lib/crow/include"
    "${CMAKE_SOURCE_DIR}/lib/mdns/include"
    "${CMAKE_SOURCE_DIR}/lib/sqlite/include"
    "${CMAKE_SOURCE_DIR}/lib/spdlog/include"
    "${CMAKE_SOURCE_DIR}/lib/libhv/include"
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
    ${PROTOBUF_C_LIBRARIES}
)

add_executable(client
    ${CLIENT_SOURCE}
)