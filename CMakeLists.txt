cmake_minimum_required(VERSION 3.15)
project(SenseboxMcu)

set(CMAKE_CXX_STANDARD 14)

if (MSVC)
    add_compile_options(
            /W4 
            /WX
            )
else()
    add_compile_options(
            -Wcast-align
            -Wpedantic
            -Wcast-qual
            -Wconversion
            -Wctor-dtor-privacy
            -Wnon-virtual-dtor
            -Wmissing-include-dirs
            -Wdisabled-optimization
            -Winit-self
            -Wnon-virtual-dtor
            -Wold-style-cast
            -Woverloaded-virtual
            -Wparentheses
            -Wredundant-decls
            -Wshadow
            -Wsign-promo
            -Wstrict-aliasing
            -Wall
            -Wextra
            -Werror
    )
endif()

# ========= Include path configurations =========

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        message(STATUS "[INFO] Adding ${file_path} header directory.")
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(header_dir_list)

list(LENGTH header_dir_list header_dir_list_count)
message(STATUS "[INFO] Found ${header_dir_list_count} header directories.")

set(calculator_dir ${CMAKE_CURRENT_SOURCE_DIR}/sketches/calculator)
set(magiccar_dir ${CMAKE_CURRENT_SOURCE_DIR}/sketches/MagicCarControllerTestable)
set(SoundLevelMeterDir ${CMAKE_CURRENT_SOURCE_DIR}/Components/SoundLevelMeter)
set(ArduinoDir ${CMAKE_CURRENT_SOURCE_DIR}/Components/Arduino)

add_subdirectory(test)
add_subdirectory(Components)

enable_testing()
