include_directories(
    "${CMAKE_SOURCE_DIR}/src/common/include"
    "${CMAKE_SOURCE_DIR}/src/common/include/verteilen2/proto_gen"
)

add_executable(project_task_count_with_args project_task_count_with_args.cpp)
add_executable(project_task_count project_task_count.cpp)
add_executable(task_job_count_with_args task_job_count_with_args.cpp)
add_executable(task_job_count task_job_count.cpp)

target_link_libraries(project_task_count_with_args PRIVATE common)
target_link_libraries(project_task_count PRIVATE common)
target_link_libraries(task_job_count_with_args PRIVATE common)
target_link_libraries(task_job_count PRIVATE common)

set_target_properties(project_task_count_with_args PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tests")
set_target_properties(project_task_count PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tests")
set_target_properties(task_job_count_with_args PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tests")
set_target_properties(task_job_count PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tests")

add_test(NAME test_project_task_count_with_args COMMAND project_task_count_with_args)
add_test(NAME test_project_task_count COMMAND project_task_count)
add_test(NAME test_task_job_count_with_args COMMAND task_job_count_with_args)
add_test(NAME test_task_job_count COMMAND task_job_count)