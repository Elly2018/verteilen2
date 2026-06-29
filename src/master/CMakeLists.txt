file(GLOB_RECURSE MASTER_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/master/*.h"
    "${CMAKE_SOURCE_DIR}/src/master/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/master/*.c"
    "${CMAKE_SOURCE_DIR}/src/master/*.cpp"
)

add_executable(master
    ${MASTER_SOURCE}
)

target_include_directories(master PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../common")
target_link_libraries(master PRIVATE common)