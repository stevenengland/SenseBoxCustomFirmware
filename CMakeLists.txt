cmake_minimum_required(VERSION 3.15)
project(SenseboxMcu)

set(CMAKE_CXX_STANDARD 14)

if (MSVC)
    add_compile_options(
            /W4 
            /WX
            )
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
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

set(ComponentDir ${CMAKE_CURRENT_SOURCE_DIR}/Components)
set(TestDir ${CMAKE_CURRENT_SOURCE_DIR}/Tests)
set(SketchesDir ${CMAKE_CURRENT_SOURCE_DIR}/Sketches)
set(ConfigurationsDir ${CMAKE_CURRENT_SOURCE_DIR}/Configurations)

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
    file(GLOB_RECURSE new_list CONFIGURE_DEPENDS "${dirToProcess}/*.h" "${dirToProcess}/*.hpp")
    set(dirList "")
    foreach(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dirList ${dirList} ${dir_path})
    endforeach()
    list(REMOVE_DUPLICATES dirList)
    foreach(dir ${dirList})
        message(STATUS "[INFO] Adding header directory: ${dir}")
    endforeach()
    set(${returnList} ${dirList} PARENT_SCOPE)
endfunction()

SetHeaderDirectories(ComponentHeaderDirs ${ComponentDir})
SetHeaderDirectories(TestHeaderDirs ${TestDir})
SetHeaderDirectories(SketchesHeaderDirs ${SketchesDir})

list(APPEND AllTargetsIncludeDirs ${ComponentHeaderDirs} ${TestHeaderDirs} ${SketchesHeaderDirs})

# ========= Providing intellisense for Arduino =========

if(EXISTS "${ConfigurationsDir}/arduino.ini")
    SetConfigurationValuesByFile("${ConfigurationsDir}/arduino.ini")
    file(GLOB_RECURSE allCppSourceFiles CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
    file(GLOB_RECURSE allInoSourceFiles CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.ino")
    add_executable(IntellisenseProject EXCLUDE_FROM_ALL ${allCppSourceFiles} ${allInoSourceFiles})
    foreach(inoFile ${allInoSourceFiles})
        set_source_files_properties(${inoFile} PROPERTIES LANGUAGE CXX)
    endforeach()
    SetHeaderDirectories(ArduinoPackagesHeaderDirs ${ArduinoUserPackagesDir})
    SetHeaderDirectories(ArduinoLibrariesHeaderDirs ${ArduinoUserLibrariesDir})
    target_include_directories(IntellisenseProject PUBLIC ${ArduinoPackagesHeaderDirs} ${ArduinoLibrariesHeaderDirs} ${AllTargetsIncludeDirs})
endif()

# ========= Adding subdirectories =========

add_subdirectory(${TestDir})
add_subdirectory(${ComponentDir})

# ========= Target for firmware build process =========

file(GLOB_RECURSE firmwareFiles CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.ino")

add_executable(BuildFirmware
        ${SketchesDir}/BuildFirmware.cpp)

foreach(firmwareFile ${firmwareFiles})
    get_filename_component(firmwareFilePath ${firmwareFile} PATH)
    #GET_FILENAME_COMPONENT(firmwareFileNameWe ${firmwareFile} NAME_WE)
    set(buildCommand "arduino-cli compile --fqbn sensebox:samd:sb --libraries \"./Components/\" -u -p \"PORT\" ${firmwareFilePath}")
    message(STATUS "[INFO] Creating post build firmware command for ${firmwareFile}.")
    add_custom_command(
        TARGET BuildFirmware POST_BUILD 
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMAND ${CMAKE_COMMAND} -E echo "[INFO] Building firmware file: ${firmwareFile}"
        COMMAND ${CMAKE_COMMAND} -E echo "[INFO] Use this command to upload a copy to the board: ${buildCommand}"
        #COMMAND arduino-cli compile --fqbn sensebox:samd:sb --build-path "${CMAKE_CURRENT_SOURCE_DIR}/firmware_build/${firmwareFileNameWe}" --libraries "./Components/" ${firmwareFilePath}
        COMMAND arduino-cli compile --fqbn sensebox:samd:sb --libraries "./Components/" ${firmwareFilePath}
    )
endforeach()

# ========= Testing =========

enable_testing()
