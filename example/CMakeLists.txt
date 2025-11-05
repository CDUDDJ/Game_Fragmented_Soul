aux_source_directory(. EXAMPLE_SRC)

add_executable(example WIN32 main.cpp ${CORE_SRC} ${EXAMPLE_SRC})

target_link_libraries(example
    PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf
)