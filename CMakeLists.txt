cmake_minimum_required(VERSION 3.26)
project(salamander_popsicle C)

set(CMAKE_C_STANDARD 99)

find_package(CURL REQUIRED)
add_executable(salamander_popsicle main.c
)

if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries(salamander_popsicle ${CURL_LIBRARIES})
else()
    message(FATAL_ERROR "libcurl not found!")
endif()
