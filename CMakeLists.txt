cmake_minimum_required(VERSION 2.6)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

#set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.. )

project (s-rlbwt)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/internal)
include_directories(~/include) #SDSL headers are here

LINK_DIRECTORIES(~/lib) #SDSL lib are here

message("Building in ${CMAKE_BUILD_TYPE} mode")

set(CMAKE_CXX_FLAGS "--std=c++11")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb -g")
set(CMAKE_CXX_FLAGS_RELEASE "-g -ggdb -Ofast -fstrict-aliasing -DNDEBUG -march=native")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -ggdb -Ofast -fstrict-aliasing -march=native")

add_executable(s-rlbwt-build s-rlbwt-build.cpp)
TARGET_LINK_LIBRARIES(s-rlbwt-build sdsl)
TARGET_LINK_LIBRARIES(s-rlbwt-build divsufsort)
TARGET_LINK_LIBRARIES(s-rlbwt-build divsufsort64)

add_executable(s-rlbwt-locate s-rlbwt-locate.cpp)
TARGET_LINK_LIBRARIES(s-rlbwt-locate sdsl)
TARGET_LINK_LIBRARIES(s-rlbwt-locate divsufsort)
TARGET_LINK_LIBRARIES(s-rlbwt-locate divsufsort64)

add_executable(s-rlbwt-count s-rlbwt-count.cpp)
TARGET_LINK_LIBRARIES(s-rlbwt-count sdsl)
TARGET_LINK_LIBRARIES(s-rlbwt-count divsufsort)
TARGET_LINK_LIBRARIES(s-rlbwt-count divsufsort64)

add_executable(s-rlbwt-space s-rlbwt-space.cpp)
TARGET_LINK_LIBRARIES(s-rlbwt-space sdsl)
TARGET_LINK_LIBRARIES(s-rlbwt-space divsufsort)
TARGET_LINK_LIBRARIES(s-rlbwt-space divsufsort64)
