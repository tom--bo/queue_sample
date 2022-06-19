cmake_minimum_required(VERSION 3.21)
project(queue)

set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(queue main.cpp lock_queue.cpp boost_queue.cpp cas_queue.cpp)
target_link_libraries(queue PUBLIC "-pthread")
