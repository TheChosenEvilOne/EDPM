cmake_minimum_required (VERSION 3.6)
set(CMAKE_CXX_STANDARD 17)

project(server)

add_executable(server
    main.cpp
    server/server.cpp
)

target_include_directories(server PRIVATE . common server client)