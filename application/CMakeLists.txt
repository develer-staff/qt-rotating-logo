set(TARGET application)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(RES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/res)
set(QML_DIR ${RES_DIR}/qml)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.h")
file(GLOB_RECURSE RESOURCE_FILES CONFIGURE_DEPENDS "${RES_DIR}/*.*")

add_executable(${TARGET} WIN32 ${SOURCE_FILES})

target_compile_definitions(${TARGET} PRIVATE BUILD_VERSION="${BUILD_VERSION}")
target_compile_definitions(${TARGET} PRIVATE BUILD_COMMIT="${BUILD_COMMIT}")
target_compile_definitions(${TARGET} PRIVATE BUILD_BRANCH="${BUILD_BRANCH}")
target_compile_definitions(${TARGET} PRIVATE APPLICATION_NAME="${CMAKE_PROJECT_NAME}")

target_include_directories(${TARGET} PRIVATE ${SRC_DIR})

target_link_libraries(${TARGET} PRIVATE libcommon Qt::QuickWidgets)

set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
                                           ADDITIONAL_CLEAN_FILES "${CMAKE_CURRENT_BINARY_DIR}/bin")

qt_add_resources(
    ${TARGET} resources
    BASE ${RES_DIR}
    PREFIX "/"
    FILES ${RESOURCE_FILES})

run_windeployqt(${TARGET} QML_DIRS ${QML_DIR})
