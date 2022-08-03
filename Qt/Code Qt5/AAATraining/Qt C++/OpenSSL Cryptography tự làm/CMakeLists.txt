cmake_minimum_required(VERSION 3.14)

project(Draft LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

#SET(OPENSSL_LIB_DIR C:/Qt/Tools/OpenSSL/Win_x64/bin)
#INCLUDE_DIRECTORIES(C:/Qt/Tools/OpenSSL/Win_x64/include)

set(OPENSSL_ROOT_DIR C:/Qt/Tools/OpenSSL/Win_x64)
#set(OPENSSL_USE_STATIC_LIBS TRUE)#dùng static thì thêm cái này
include(FindOpenSSL)#or dùng 2 dòng dưới
#find_package(OpenSSL REQUIRED)
#include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(Draft
  main.cpp
  crypto.h
  crypto.cpp
)
target_link_libraries(Draft Qt${QT_VERSION_MAJOR}::Core)
#TARGET_LINK_LIBRARIES(Draft ${OPENSSL_LIB_DIR}/libcrypto-1_1-x64.dll ${OPENSSL_LIB_DIR}/libssl-1_1-x64.dll)
target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)#or dùng marco dưới
#target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES})
