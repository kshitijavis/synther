cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
project(synther)

# This tells the compiler to not aggressively optimize and
# to include debugging information so that the debugger
# can properly read what's going on.
set(CMAKE_BUILD_TYPE Debug)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Warning flags
if(MSVC)
    # warning level 3 and all warnings as errors
    add_compile_options(/W3 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wpedantic -Werror)
endif()

# To find Cocoa framework
if(APPLE)
    set(CMAKE_FIND_FRAMEWORK LAST)
    set(CMAKE_FIND_APPBUNDLE LAST)
endif()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.x
)

FetchContent_Declare(
        json
        # Use smaller ArthurSonzogni repo instead of the standard nlohmann repo: specifically for FetchContent
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.7.3
)

# Add catch2 testing library
FetchContent_GetProperties(catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_library(catch2 INTERFACE)
    target_include_directories(catch2 INTERFACE ${catch2_SOURCE_DIR}/single_include)
endif()

# Add nlohmann/json library
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)

include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")

list(APPEND SOURCE_FILES    ${CORE_SOURCE_FILES}
        src/visualizer/synther_app.cc
        src/visualizer/piano.cc
        src/visualizer/piano_key.cc
        src/visualizer/pedal.cc)

list(APPEND SOURCE_FILES src/core/music_note.cc)
list(APPEND SOURCE_FILES src/core/player.cc)
list(APPEND SOURCE_FILES src/core/sound_json_parser.cc)
list(APPEND SOURCE_FILES src/core/piano_keybinder.cc)

list(APPEND TEST_FILES tests/music_note_test.cc)
list(APPEND TEST_FILES tests/piano_test.cc)
list(APPEND TEST_FILES tests/soundsfile_parser_test.cc)
list(APPEND TEST_FILES tests/player_test.cc)
list(APPEND TEST_FILES tests/pedal_test.cc)
list(APPEND TEST_FILES tests/piano_keybinder_test.cc)

ci_make_app(
        APP_NAME        synther-app
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         apps/cinder_app_main.cc ${SOURCE_FILES}
        INCLUDES        include
        LIBRARIES       nlohmann_json::nlohmann_json
)

ci_make_app(
        APP_NAME        synther-test
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         tests/test_main.cc ${SOURCE_FILES} ${TEST_FILES}
        INCLUDES        include
        LIBRARIES       catch2 nlohmann_json::nlohmann_json
)

if(MSVC)
    set_property(TARGET synther-test APPEND_STRING PROPERTY LINK_FLAGS " /SUBSYSTEM:CONSOLE")
endif()