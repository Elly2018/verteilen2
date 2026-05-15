file(GLOB_RECURSE CLI_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/cli/*.h"
    "${CMAKE_SOURCE_DIR}/src/cli/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/cli/*.c"
    "${CMAKE_SOURCE_DIR}/src/cli/*.cpp"
)

add_executable(cli
    ${CLI_SOURCE}
)