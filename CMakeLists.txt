cmake_minimum_required(VERSION 2.8.3)

# AUTHER: Tsinghua University IRM-LAB

project(ELMO)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -fPIC")
set(CMAKE_CXX_FLAGS   "-no-pie")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(Eigen3 REQUIRED)
find_package(Threads)

include_directories(
    LINUX64/Headers/MMC_APP/Src/OsCommon/includes
    LINUX64/Headers/MMC_APP/Src/OsPlatform/includes
    LINUX64/Headers/MMCPP/Src/OsCommon/includes
    LINUX64/Headers/MMCPP/Src/OsPlatform/includes
    example
    ${EIGEN3_INCLUDE_DIRS}
)


LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/LINUX64/Libs/Release)
link_libraries(${PROJECT_SOURCE_DIR}/LINUX64/Libs/Release)


add_executable(${PROJECT_NAME}_example example/CPP_CyclicPosHome.cpp)
target_link_libraries(${PROJECT_NAME}_example pthread)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}_example libhello.a) # For test, success.
TARGET_LINK_LIBRARIES(${PROJECT_NAME}_example libMMCPP_LinuxRpc64.a)
TARGET_LINK_LIBRARIES(${PROJECT_NAME}_example libMMCPP_LinuxRpc64.so)
TARGET_LINK_LIBRARIES(${PROJECT_NAME}_example libMMC_APP_LinuxRpc64.so)
TARGET_LINK_LIBRARIES(${PROJECT_NAME}_example libMMC_APP_LinuxRpc64.a)





