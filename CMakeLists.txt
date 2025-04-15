cmake_minimum_required(VERSION 4.0)

project(s2)

function(s2_target_common name)
    target_include_directories(${name}
        PUBLIC
            "${PROJECT_SOURCE_DIR}/source"
            "${CMAKE_BINARY_DIR}/source"
    )
    target_compile_features(${name} PUBLIC cxx_std_20)
    set_target_properties(${name}
        PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endfunction()

function(s2_add_executable)
    cmake_parse_arguments(ARGS
        "" # options
        "NAME" # one value
        "PRIVATE;DEPS" # multi value
        ${ARGN})

    add_executable(${ARGS_NAME})
    s2_target_common(${ARGS_NAME})
    target_sources(${ARGS_NAME} PRIVATE ${ARGS_PRIVATE})
    target_link_libraries(${ARGS_NAME} PRIVATE ${ARGS_DEPS})
endfunction()

function(s2_add_library)
    cmake_parse_arguments(ARGS
        "" # options
        "NAME" # one value
        "PRIVATE;DEPS" # multi value
        ${ARGN})

    add_library(${ARGS_NAME})
    s2_target_common(${ARGS_NAME})
    target_sources(${ARGS_NAME} PRIVATE ${ARGS_PRIVATE})
    target_link_libraries(${ARGS_NAME} PRIVATE ${ARGS_DEPS})
endfunction()

find_library(FRAMEWORK_APP_KIT AppKit REQUIRED)
find_library(FRAMEWORK_METAL Metal REQUIRED)
find_library(FRAMEWORK_QUARTZ_CORE QuartzCore REQUIRED)

add_subdirectory(source)
