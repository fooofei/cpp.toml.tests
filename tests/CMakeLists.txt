cmake_minimum_required(VERSION 3.1)
project(tomlc99_test)


set(binary_name toml_test)

if(APPLE)
    # no warning
    # https://stackoverflow.com/questions/31561309/cmake-warnings-under-os-x-macosx-rpath-is-not-specified-for-the-following-targe
    set(CMAKE_MACOSX_RPATH 0)
endif()



set(Source_files 
	${CMAKE_CURRENT_SOURCE_DIR}/main.c
	${CMAKE_CURRENT_SOURCE_DIR}/../c_cpp_common/crt_dbg_leak.c
	${CMAKE_CURRENT_SOURCE_DIR}/../c_cpp_common/crt_dbg_leak.h

	)
set(common_c_common ${CMAKE_CURRENT_SOURCE_DIR}/../c_cpp_common)



add_executable(${binary_name} ${Source_files})
target_include_directories(${binary_name} PRIVATE ${common_c_common})

source_group(files FILES ${Source_files})

if(WIN32)
	target_compile_options(${binary_name} PRIVATE /source-charset:utf-8 /execution-charset:utf-8)
else()

endif()


if (NOT TARGET toml)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../  build_toml)
endif ()
target_link_libraries(${binary_name} toml)