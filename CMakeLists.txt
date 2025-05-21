cmake_minimum_required(VERSION 3.10)
project(GrayscaleImageProcessing)

set(CMAKE_CXX_STANDARD 17)

# Include headers
include_directories(include)

# Add GoogleTest submodule
add_subdirectory(external/googletest)

enable_testing()

# Your image processing lib
add_library(image_processing src/image_processing.cpp)

# The test executable
add_executable(test_grayscale test/test_image_processing.cpp)
add_executable(convert_grayscale src/main.cpp)
target_link_libraries(test_grayscale image_processing gtest_main)

# Add tests
include(GoogleTest)
gtest_discover_tests(test_grayscale)
