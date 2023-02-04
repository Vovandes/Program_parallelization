# CMakeList.txt: проект CMake для Program_parallelization; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.15)

project ("Program_parallelization")

add_executable(Program_parallelization    
    source/main.cpp
    source/program_parallelization.cpp
    source/simple_timer.cpp
 )
  
set_property(TARGET Program_parallelization PROPERTY CXX_STANDARD 20)

target_include_directories(Program_parallelization PRIVATE 
    include
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(Program_parallelization PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(Program_parallelization PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()

target_compile_features(Program_parallelization PUBLIC cxx_std_20)