file(GLOB_RECURSE MASTER_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/master/*.h"
    "${CMAKE_SOURCE_DIR}/src/master/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/master/*.c"
    "${CMAKE_SOURCE_DIR}/src/master/*.cpp"
)

include_directories(
    "${CMAKE_SOURCE_DIR}/src/common"
    "${CMAKE_SOURCE_DIR}/lib/crow/include"
)

link_libraries(
    common 
    Crow::Crow
)

add_executable(master
    ${MASTER_SOURCE}
)