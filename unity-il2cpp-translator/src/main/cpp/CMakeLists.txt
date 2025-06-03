cmake_minimum_required(VERSION 3.22.1)

project("unity_il2cpp_translator")

find_package(shadowhook REQUIRED CONFIG)

add_library(${CMAKE_PROJECT_NAME} SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        unity_il2cpp_translator.cpp
        translator.cpp
        il2cpp_manager.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        shadowhook::shadowhook
        android
        log)