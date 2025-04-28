cmake_minimum_required(VERSION 3.30)

project(s2)

if(${CMAKE_SYSTEM_NAME} STREQUAL Darwin)
    set(S2_IS_MACOS YES CACHE BOOL "")
else()
    set(S2_IS_MACOS NO CACHE BOOL "")
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
    set(S2_IS_WINDOWS YES CACHE BOOL "")
else()
    set(S2_IS_WINDOWS NO CACHE BOOL "")
endif()

function(s2_target_common name)
    target_include_directories(${name}
        PUBLIC
            "${PROJECT_SOURCE_DIR}/source"
            "${CMAKE_BINARY_DIR}/source"
    )
    target_compile_features(${name} PUBLIC cxx_std_23)
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
        "PRIVATE;PRIVATE_MACOS;PRIVATE_WINDOWS;DEPS" # multi value
        ${ARGN})

    add_executable(${ARGS_NAME})
    s2_target_common(${ARGS_NAME})
    target_sources(${ARGS_NAME} PRIVATE ${ARGS_PRIVATE})
    if(S2_IS_MACOS)
        target_sources(${ARGS_NAME} PRIVATE ${ARGS_PRIVATE_MACOS})
    endif()
    if(S2_IS_WINDOWS)
        target_sources(${ARGS_NAME} PRIVATE ${ARGS_PRIVATE_WINDOWS})
    endif()
    target_link_libraries(${ARGS_NAME} PRIVATE ${ARGS_DEPS})
endfunction()

function(s2_add_library)
    cmake_parse_arguments(ARGS
        "" # options
        "NAME" # one value
        "PRIVATE;PRIVATE_MACOS;PRIVATE_WINDOWS;DEPS" # multi value
        ${ARGN})

    add_library(${ARGS_NAME})
    s2_target_common(${ARGS_NAME})
    target_sources(${ARGS_NAME} PRIVATE ${ARGS_PRIVATE})
    if(S2_IS_MACOS)
        target_sources(${ARGS_NAME} PRIVATE ${ARGS_PRIVATE_MACOS})
    endif()
    if(S2_IS_WINDOWS)
        target_sources(${ARGS_NAME} PRIVATE ${ARGS_PRIVATE_WINDOWS})
    endif()
    target_link_libraries(${ARGS_NAME} PRIVATE ${ARGS_DEPS})
endfunction()

if(S2_IS_MACOS)
    find_library(FRAMEWORK_APP_KIT AppKit REQUIRED)
    find_library(FRAMEWORK_METAL Metal REQUIRED)
    find_library(FRAMEWORK_QUARTZ_CORE QuartzCore REQUIRED)
endif()

add_subdirectory(source)
