cmake_minimum_required(VERSION 3.20)
project(BinaryRecorder)

set(CMAKE_CXX_STANDARD 20)

find_package(ZLIB REQUIRED)

#[[add_executable(tests
    Tests.cpp
    message.cpp
)

add_executable(message
    message.cpp
)
]]
add_executable(fileReader
    fileReader.cpp
)

add_executable(receiver
    receiver.cpp
    processor.cpp
    record.cpp
)

target_link_libraries(fileReader PRIVATE ZLIB::ZLIB)
target_link_libraries(receiver PRIVATE ZLIB::ZLIB)

