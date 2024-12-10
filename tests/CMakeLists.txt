include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.2.1)

FetchContent_MakeAvailable(Catch2)

set(TARGET tests)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")

add_executable(${TARGET} ${SOURCE_FILES})

target_include_directories(${TARGET} PRIVATE ${SRC_DIR})

target_link_libraries(${TARGET} PRIVATE Catch2::Catch2WithMain Qt::Test libcommon)

if(WIN32)
    run_windeployqt(${TARGET})
endif()

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

include(Catch)
catch_discover_tests(${TARGET})
