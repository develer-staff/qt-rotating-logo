set(TARGET libcommon)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/libcommon)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")

add_library(${TARGET} STATIC ${SOURCE_FILES})

target_include_directories(${TARGET} PRIVATE ${SRC_DIR})
target_include_directories(${TARGET} PUBLIC ${SRC_DIR}/..)

target_link_libraries(${TARGET} PUBLIC Qt::Widgets)
