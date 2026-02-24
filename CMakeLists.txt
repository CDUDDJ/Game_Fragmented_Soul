cmake_minimum_required(VERSION 3.25)
project(fragmented_soul)

add_subdirectory(sgf)

add_executable(fragmented_soul)

target_compile_features(fragmented_soul PRIVATE cxx_std_17)

target_sources(fragmented_soul
  PRIVATE
    main.cpp
)

target_link_libraries(fragmented_soul
  PRIVATE
    sgf::sgf
)