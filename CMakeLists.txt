cmake_minimum_required(VERSION 2.8.12)
project(chatroomcxx)

add_definitions("-std=c++17")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(chatroomcxx chatroom.cpp)
target_link_libraries(chatroomcxx ${CONAN_LIBS})
