cmake_minimum_required(VERSION 3.18)
project(lux-math)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(COMPILE_DEFINITION)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(COMPILE_DEFINITION __LUX_MATH_COMPILER_CLANG__)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILE_DEFINITION __LUX_MATH_COMPILER_GCC__)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    set(COMPILE_DEFINITION __LUX_MATH_COMPILER_INTEL__)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILE_DEFINITION __LUX_MATH_COMPILER_MSVC__)
endif()

find_package(LUX-CMAKE-TOOLSET CONFIG REQUIRED)

add_interface_component(
    COMPONENT_NAME                  math
    NAMESPACE                       lux
)

component_include_directories(
    math
    BUILD_TIME_EXPORT
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    INSTALL_TIME
        include
)

target_compile_definitions(
    math
    INTERFACE
	${COMPILE_DEFINITION}
)

install_components(
    PROJECT_NAME    lux-math
    VERSION         0.0.2
    NAMESPACE       lux::math
    COMPONENTS      math
)

set(ENABLE_TEST true BOOL "Enable test")
if(ENABLE_TEST)
    add_subdirectory(test)    
endif()
