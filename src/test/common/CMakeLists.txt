include_directories("${CMAKE_SOURCE_DIR}/src/common")
link_directories("${CMAKE_SOURCE_DIR}/src/common")

add_executable(unittest_thread unittest_thread.cc)
target_link_libraries(unittest_thread gtest)
target_link_libraries(unittest_thread common)

add_executable(multi_producer_consumer multi_producer_consumer.cc)
target_link_libraries(multi_producer_consumer common)
