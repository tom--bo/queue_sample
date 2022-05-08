cmake_minimum_required(VERSION 3.21)
project(queue)

set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(queue main.cpp lock_queue.h boost_queue.h)
target_link_libraries(queue PUBLIC "-pthread")
