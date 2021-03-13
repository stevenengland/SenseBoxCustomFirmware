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

# ========= Set directory names =========

set(calculator_dir ${CMAKE_CURRENT_SOURCE_DIR}/sketches/calculator)
set(magiccar_dir ${CMAKE_CURRENT_SOURCE_DIR}/sketches/MagicCarControllerTestable)
set(ComponentDir ${CMAKE_CURRENT_SOURCE_DIR}/Components)
set(TestDir ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(SketchesDir ${CMAKE_CURRENT_SOURCE_DIR}/sketches)

# ========= Read configuration file and set configuration values =========

function(SetConfigurationValuesByFile fileName)
    file(STRINGS ${fileName} configContents)
    foreach(NameAndValue ${configContents})
      # Strip leading spaces
      string(REGEX REPLACE "^[ ]+" "" NameAndValue ${NameAndValue})
      # Find variable name
      string(REGEX MATCH "^[^=]+" Name ${NameAndValue})
      # Find the value
      string(REPLACE "${Name}=" "" Value ${NameAndValue})
      # Set the variable
      set(${Name} "${Value}" PARENT_SCOPE)
      message(STATUS "[INFO] Read ${Name}=${Value} from config file ${fileName}.")
    endforeach()
endfunction()

# ========= Find and return header directories =========

function(SetHeaderDirectories returnList dirToProcess)
    message(STATUS "[INFO] Looking for headers in: ${dirToProcess}")
    FILE(GLOB_RECURSE new_list CONFIGURE_DEPENDS "${dirToProcess}/*.h" "${dirToProcess}/*.hpp")
    SET(dirList "")
    foreach(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dirList ${dirList} ${dir_path})
    endforeach()
    LIST(REMOVE_DUPLICATES dirList)
    foreach(dir ${dirList})
        message(STATUS "[INFO] Adding header directory: ${dir}")
    endforeach()
    SET(${returnList} ${dirList} PARENT_SCOPE)
endfunction()

SetHeaderDirectories(ComponentHeaderDirs ${ComponentDir})
SetHeaderDirectories(TestHeaderDirs ${TestDir})
SetHeaderDirectories(SketchesHeaderDirs ${SketchesDir})

list(APPEND AllTargetsIncludeDirs ${ComponentHeaderDirs} ${TestHeaderDirs} ${SketchesHeaderDirs})

add_subdirectory(test)
add_subdirectory(Components)

enable_testing()
