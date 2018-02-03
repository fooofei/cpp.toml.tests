cmake_minimum_required(VERSION 3.1)
project(tomlc99_test)




if(APPLE)
    # no warning
    # https://stackoverflow.com/questions/31561309/cmake-warnings-under-os-x-macosx-rpath-is-not-specified-for-the-following-targe
    set(CMAKE_MACOSX_RPATH 0)
endif()

if (NOT TARGET toml)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../  build_toml)
endif ()

set(common_c_common ${CMAKE_CURRENT_SOURCE_DIR}/../c_cpp_common)




set(self_binary_name toml_test)
set(self_test_sources 
	${CMAKE_CURRENT_SOURCE_DIR}/main.c
	${common_c_common}/crt_dbg_leak.c
	${common_c_common}/crt_dbg_leak.h
	)
add_executable(${self_binary_name} ${self_test_sources})
target_include_directories(${self_binary_name} PRIVATE ${common_c_common})
source_group(files FILES ${self_test_sources})
if(WIN32)
	target_compile_options(${self_binary_name} PRIVATE /source-charset:utf-8 /execution-charset:utf-8)
else()
endif()
target_link_libraries(${self_binary_name} toml)


set(self_binary_toml_cat toml_cat)
add_executable(${self_binary_toml_cat} "${CMAKE_CURRENT_SOURCE_DIR}/../tomlc99/toml_cat.c")
target_include_directories(${self_binary_toml_cat} PRIVATE ${common_c_common})
target_link_libraries(${self_binary_toml_cat} toml)