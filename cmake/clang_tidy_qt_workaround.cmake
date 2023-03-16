function(clang_tidy_qt_workaround)
    # See also: https://gitlab.kitware.com/cmake/cmake/-/merge_requests/777
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/.clang-tidy" "Checks: -*,llvm-twine-local")
endfunction()
