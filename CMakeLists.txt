cmake_minimum_required(VERSION 3.26)
project(salamander_popsicle C)

set(CMAKE_C_STANDARD 99)

#find pkg-config
find_package(PkgConfig REQUIRED)

#find GTK+3 package
pkg_check_modules(GTK REQUIRED gtk+-3.0)

#include GTK headers
include_directories(${GTK_INCLUDE_DIRS})

#add other compiler flags
add_compile_options(${GTK_CFLAGS_OTHER})

#create the executable
add_executable(salamander_popsicle main.c)

#link GTK libraries
target_link_libraries(salamander_popsicle ${GTK_LIBRARIES})

#find and link libcurl
find_package(CURL REQUIRED)
if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries(salamander_popsicle ${CURL_LIBRARIES})
else()
    message(FATAL_ERROR "libcurl not found!")
endif()

# explicitly add the GTK+3 libraries and include directories
target_include_directories(salamander_popsicle PRIVATE ${GTK_INCLUDE_DIRS})
target_link_directories(salamander_popsicle PRIVATE ${GTK_LIBRARY_DIRS})
