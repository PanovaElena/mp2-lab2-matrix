file(GLOB samples_list CONFIGURE_DEPENDS "*.cpp")

foreach(sample_filename IN LISTS samples_list)
    get_filename_component(sample "${sample_filename}" NAME_WE)

    add_executable(${sample} "${sample_filename}")

    target_include_directories(${sample}
        PRIVATE "${MP2_INCLUDE}"
    )

    set_target_properties(${sample} PROPERTIES
        OUTPUT_NAME "${sample}"
        PROJECT_LABEL "${sample}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
endforeach()