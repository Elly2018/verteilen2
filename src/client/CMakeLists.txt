file(GLOB_RECURSE CLIENT_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/client/*.h"
    "${CMAKE_SOURCE_DIR}/src/client/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/client/*.c"
    "${CMAKE_SOURCE_DIR}/src/client/*.cpp"
)

include_directories(
    "${CMAKE_SOURCE_DIR}/src/common"
    "${CMAKE_SOURCE_DIR}/lib/crow/include"
)

link_libraries(
    common 
    Crow::Crow
)

add_executable(client
    ${CLIENT_SOURCE}
)