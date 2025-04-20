include(${CMAKE_CURRENT_LIST_DIR}/CPM.cmake)

CPMAddPackage("gh:fmtlib/fmt#11.1.4")

CPMAddPackage(
    NAME pybind11
    GITHUB_REPOSITORY  pybind/pybind11    
    GIT_TAG v2.12.0
  )

