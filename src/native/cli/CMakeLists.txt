file(GLOB_RECURSE CLI_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/native/cli/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/native/cli/src/*.cc"
)

include_directories(
    "${CMAKE_SOURCE_DIR}/src/native/cli/include"
    "${CMAKE_SOURCE_DIR}/src/native/common/include"
    "${CMAKE_SOURCE_DIR}/src/native/common/include/verteilen2/proto_gen"
    "${CMAKE_SOURCE_DIR}/lib/argh"
    "${CMAKE_SOURCE_DIR}/lib/json/include"
    "${CMAKE_SOURCE_DIR}/lib/spdlog/include"
    "${CMAKE_SOURCE_DIR}/lib/ftxui/include"
)

add_executable(cli
    ${CLI_SOURCE}
)

link_libraries(
    common 
    pthread
    dl
    spdlog
    ftxui::ftxui
    ${Protobuf_LIBRARIES}
)