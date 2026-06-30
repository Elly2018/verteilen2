include_directories("${CMAKE_SOURCE_DIR}/src/common")

file(GLOB_RECURSE COMMON_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/common/*.h"
    "${CMAKE_SOURCE_DIR}/src/common/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/common/*.c"
    "${CMAKE_SOURCE_DIR}/src/common/*.cpp"
)

add_executable(project_task_count_with_args ${COMMON_SOURCE} project_task_count_with_args.cpp)
add_executable(project_task_count ${COMMON_SOURCE} project_task_count.cpp)
add_executable(task_job_count_with_args ${COMMON_SOURCE} task_job_count_with_args.cpp)
add_executable(task_job_count ${COMMON_SOURCE} task_job_count.cpp)

set_target_properties(project_task_count_with_args PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tests")
set_target_properties(project_task_count PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tests")
set_target_properties(task_job_count_with_args PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tests")
set_target_properties(task_job_count PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tests")

add_test(NAME test_project_task_count_with_args COMMAND project_task_count_with_args)
add_test(NAME test_project_task_count COMMAND project_task_count)
add_test(NAME test_task_job_count_with_args COMMAND task_job_count_with_args)
add_test(NAME test_task_job_count COMMAND task_job_count)