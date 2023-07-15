cmake_minimum_required(VERSION 3.24)
#cmake_minimum_required(VERSION 3.22.1)
project(testSkyLineInGroup)

set(CMAKE_CXX_STANDARD 17)

add_executable(testSkyLineInGroup main.cpp cmake-build-debug/skyLine.h cmake-build-debug/threadPool02.h cmake-build-debug/ctlp.h cmake-build-debug/threadPool.h ../skyLine/cmake-build-debug/SkyLine.h ../skyLine/cmake-build-debug/SkyLine.h ../skyLine/cmake-build-debug/SkyLine.h cmake-build-debug/listMutex.h cmake-build-debug/getRealData.h ../skyLine/cmake-build-debug/SkyLine.h ../skyLine/cmake-build-debug/SkyLine.h)
