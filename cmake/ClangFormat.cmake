cmake_minimum_required(VERSION 3.0)

function(ClangFormat)
    find_program(CLANG_FORMAT_EXE clang-format)
    if(NOT CLANG_FORMAT_EXE)
        message(WARNING "clang-format not found!")
        return()
    endif()

    set(CLANG_FORMAT_FILES "${ARGN}")
    add_custom_target(
        "CLANG_FORMAT"
        "${CLANG_FORMAT_EXE}" -i -style=file ${CLANG_FORMAT_FILES}
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        COMMENT "Formatting with clang-format..."
    )
    set_property(TARGET "CLANG_FORMAT" PROPERTY FOLDER "CMake")
endfunction(ClangFormat)

function(ClangFormatTarget DEFAULT)
    option(CLANG_FORMAT_TARGET "Initialize Clang_Format target" ${DEFAULT})

    if(${CLANG_FORMAT_TARGET})
        ClangFormat(${ARGN})
    endif()
endfunction(ClangFormatTarget)
