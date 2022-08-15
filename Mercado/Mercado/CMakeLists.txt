cmake_minimum_required (VERSION 3.8)

# set name for the target that will be specified inside this file
set (TARGET_NAME Mercado)

set(PYBIND11_PYTHON_VERSION 3.9.8 CACHE STRING "")
find_package(pybind11 CONFIG REQUIRED)
    # Note: 9 target(s) were omitted.
	add_executable (${TARGET_NAME} "Mercado.cpp" "Mercado.h")
    target_link_libraries(${TARGET_NAME} PRIVATE pybind11::lto pybind11::embed pybind11::module)
# set binary filenames
set_target_properties( ${TARGET_NAME} PROPERTIES OUTPUT_NAME_DEBUG Americanas)
set_target_properties( ${TARGET_NAME} PROPERTIES OUTPUT_NAME_RELWITHDEBINFO ${TARGET_NAME}-relwidthdebinfo )
set_target_properties( ${TARGET_NAME} PROPERTIES OUTPUT_NAME_RELEASE ${TARGET_NAME}-release )
set_target_properties( ${TARGET_NAME} PROPERTIES OUTPUT_NAME_MINSIZEREL ${TARGET_NAME}-minsizerel )

# set warning levels
if (MSVC)
	target_compile_options(${TARGET_NAME} PUBLIC /W4 /permissive)
else()
	target_compile_options(${TARGET_NAME} PUBLIC -Wall -Wextra -pedantic)
endif()