cmake_minimum_required(VERSION 3.1)
project(tomlc99)


set(binary_name toml)

if(APPLE)
    # no warning
    # https://stackoverflow.com/questions/31561309/cmake-warnings-under-os-x-macosx-rpath-is-not-specified-for-the-following-targe
    set(CMAKE_MACOSX_RPATH 0)
endif()



set(Source_files 
	${CMAKE_CURRENT_SOURCE_DIR}/tomlc99/toml.h
	${CMAKE_CURRENT_SOURCE_DIR}/tomlc99/toml.c

	)

add_library(${binary_name} STATIC ${Source_files})

source_group(files FILES ${Source_files})

if(WIN32)
	target_compile_options(${binary_name} PRIVATE /source-charset:utf-8 /execution-charset:utf-8)
else()
	# remove original file's use
	#target_compile_options(${binary_name} PRIVATE  -std=c99)
endif()



target_include_directories(${binary_name} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/tomlc99/)