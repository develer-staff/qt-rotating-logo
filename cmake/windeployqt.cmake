function(run_windeployqt TARGET)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs QML_DIRS)
    cmake_parse_arguments(_ "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(_QML_OPTIONS)
    if(DEFINED __QML_DIRS)
        # Force windeployqt to add QML and Qt Quick runtimes since sometimes auto-detection doesn't work.
        list(APPEND _QML_OPTIONS -qml -quick)

        foreach(QML_DIR ${__QML_DIRS})
            list(APPEND _QML_OPTIONS --qmldir ${QML_DIR})
        endforeach(QML_DIR ${__QML_DIRS})
    endif()

    get_target_property(QMAKE_EXECUTABLE Qt::qmake IMPORTED_LOCATION)

    get_filename_component(QT_BIN_DIR "${QMAKE_EXECUTABLE}" DIRECTORY)

    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${QT_BIN_DIR}")

    add_custom_command(
        TARGET ${TARGET}
        POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E echo "-- Running windeployqt for ${TARGET}"
        COMMAND "${CMAKE_COMMAND}" -E env PATH="${QT_BIN_DIR}" "${WINDEPLOYQT_EXECUTABLE}" --verbose=0 ${_QML_OPTIONS}
                "$<TARGET_FILE:${TARGET}>"
        COMMENT "Running windeployqt...")

    add_custom_command(
        TARGET ${TARGET}
        POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E rm -f "$<TARGET_FILE_DIR:${TARGET}>/vc_redist.x64.exe"
        COMMENT "Removing Visual C++ redistributable package...")
endfunction()
