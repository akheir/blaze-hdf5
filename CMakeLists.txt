# Copyright (c) 2018 Alireza Kheirkhahan
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.8)
project(cpp_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

include_directories("${PROJECT_SOURCE_DIR}")
link_directories(${CMAKE_BINARY_DIR}/lib)

find_package(HighFive REQUIRED NO_MODULE NO_CMAKE_PACKAGE_REGISTRY)
if(NOT HighFive_FOUND)
    message("HighFive could not be found, please set HighFive_DIR to help locating it.")
endif()

find_package(blaze NO_CMAKE_PACKAGE_REGISTRY)
if(NOT blaze_FOUND)
    message("Blaze could not be found. Please specify blaze_DIR to assist locating it.")
endif()

set(SOURCE_FILES
        hdf5_blaze
        read_write_vector_dataset
        )

foreach(file ${SOURCE_FILES})
    add_executable(${file} ${file}.cpp)
    target_link_libraries(${file} 
	    HighFive
	    blaze::blaze)
endforeach()

