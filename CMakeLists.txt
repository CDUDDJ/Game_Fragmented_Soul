cmake_minimum_required(VERSION 3.10)
project(Fragmented_Soul)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

add_subdirectory(core/vendored/SDL3 EXCLUDE_FROM_ALL)
add_subdirectory(core/vendored/SDL3_image EXCLUDE_FROM_ALL)
add_subdirectory(core/vendored/SDL3_ttf EXCLUDE_FROM_ALL)

aux_source_directory(src SRC_LIST)
add_executable(Fragmented_Soul WIN32 main.cpp ${SRC_LIST})

target_link_libraries(Fragmented_Soul PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)

enable_testing()
add_subdirectory(Fragmented_Soul)