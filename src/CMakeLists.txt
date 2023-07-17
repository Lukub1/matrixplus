cmake_minimum_required(VERSION 3.10)

project(s21_matrix_oop)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find and include Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add source files
add_library(s21_matrix_oop s21_matrix_oop.cpp s21_matrix_oop.h)
add_executable(s21_matrix_oop_test s21_matrix_oop_test.cpp)

# Link with Google Test library
target_link_libraries(s21_matrix_oop_test ${GTEST_LIBRARIES} pthread)

# Link with module s21_matrix_oop
target_link_libraries(s21_matrix_oop_test s21_matrix_oop)
