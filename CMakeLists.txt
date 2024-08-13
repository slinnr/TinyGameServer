# CMakeList.txt: slinnrserver 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.22)
project ("slinnrserver")
include (cmake/utils.cmake)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Wno-unused-function")
include_directories(.)
include_directories(/home/slinnr/cppenvironment)
include_directories(/home/slinnr/cppenvironment/lib)
set(LIB_SRC
    slinnr/log.cpp
    slinnr/config.cpp
    slinnr/thread.cpp
    slinnr/util.cpp
    slinnr/fiber.cpp
    slinnr/schedule.cpp
    slinnr/iomanager.cpp
    slinnr/timer.cpp
    slinnr/hook.cpp
    )
add_library(slinnrserver SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(slinnrserver)

set(LIB_LIB
    slinnrserver
    pthread
    yaml-cpp
    dl
)

add_executable(test tests/test.cpp)
add_dependencies(test slinnrserver)
target_link_libraries(test ${LIB_LIB})
force_redefine_file_macro_for_sources(test)

add_executable(test_config tests/test_config.cpp)
add_dependencies(test_config slinnrserver)
target_link_libraries(test_config ${LIB_LIB})
force_redefine_file_macro_for_sources(test_config)

add_executable(test_thread tests/test_thread.cpp)
add_dependencies(test_thread slinnrserver)
target_link_libraries(test_thread ${LIB_LIB})
force_redefine_file_macro_for_sources(test_thread)

add_executable(test_util tests/test_util.cpp)
add_dependencies(test_util slinnrserver)
target_link_libraries(test_util ${LIB_LIB})
force_redefine_file_macro_for_sources(test_util)

add_executable(test_fiber tests/test_fiber.cpp)
add_dependencies(test_fiber slinnrserver)
target_link_libraries(test_fiber ${LIB_LIB})
force_redefine_file_macro_for_sources(test_fiber)

add_executable(test_scheduler tests/test_scheduler.cpp)
add_dependencies(test_scheduler slinnrserver)
target_link_libraries(test_scheduler ${LIB_LIB})
force_redefine_file_macro_for_sources(test_scheduler)

add_executable(test_iomanager tests/test_iomanager.cpp)
add_dependencies(test_iomanager slinnrserver)
target_link_libraries(test_iomanager ${LIB_LIB})
force_redefine_file_macro_for_sources(test_iomanager)

add_executable(test_hook tests/test_hook.cpp)
add_dependencies(test_hook slinnrserver)
target_link_libraries(test_hook ${LIB_LIB})
force_redefine_file_macro_for_sources(test_hook)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 将源代码添加到此项目的可执行文件。
# add_executable (slinnrserver "slinnrserver.cpp" "slinnrserver.h" "slinnr/log.cpp" "slinnr/log.h" "slinnr/util.h" "slinnr/config.h" "slinnr/singleton.h" "tests/test_config.cpp" "slinnr/config.cpp")

# #Boost
# set(Boost_DEBUG ON)
# set(Boost_USE_STATIC_LIBS ON)
# set(Boost_INCLUDE_DIR "F:/cppenvironment/boost_1_80_0")
# set(Boost_LIBRARY_DIR "F:/cppenvironment/boost_1_80_0/libs")
# find_package(boost REQUIRED COMPONENTS filesystem)
# MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
# MESSAGE( STATUS "Boost_LIBRARY_DIRS = ${Boost_LIBRARY_DIRS}.")
# MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
# MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
# include_directories(${Boost_INCLUDE_DIRS})

# #yacml-cpp

# # 添加include文件夹与lib文件夹，避免找不到yaml-cpp的头文件与库文件
# target_link_libraries(slinnrserver "F:/cppenvironment/yaml-cpp-master/build/Release")
# include_directories("F:/cppenvironment/yaml-cpp-master/include")
# link_directories("F:/cppenvironment/yaml-cpp-master/build/Release")
# SET(yaml-cpp_DIR "F:/cppenvironment/yaml-cpp-master")
# # 在编译可执行文件时，添加YAML_CPP_STATIC_DEFINE宏
# target_compile_definitions(slinnrserver PUBLIC YAML_CPP_STATIC_DEFINE)

# 链接静态库
# TODO: 如有需要，请添加测试并安装目标。
