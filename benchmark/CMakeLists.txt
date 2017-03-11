#benchmark

option(ASIO OFF)
option(LOAD_TEST OFF)

add_executable(benchmark benchmark.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(benchmark pthread)

if (ASIO)
  find_package(Boost REQUIRED COMPONENTS system)
  include_directories(${Boost_INCLUDE_DIR})
  target_link_libraries(benchmark ${Boost_LIBRARIES})
else()
  add_definitions(-DWITHOUT_ASIO)
endif()

if (WITHOUT_LOAD_TEST)
  add_executable(load_test load_test.cpp)
  target_link_libraries(load_test pthread profiler tcmalloc)
endif()



