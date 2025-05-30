find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG QUIET)

if(NOT pybind11_FOUND)
  message(STATUS "No pybind11 installation found, fetching from GitHub.")
  include(FetchContent)
  FetchContent_Declare(pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11
    GIT_TAG        v2.9.2
  )
  FetchContent_GetProperties(pybind11)
  if(NOT pybind11_POPULATED)
    FetchContent_Populate(pybind11)
    add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})
  endif()
endif()

pybind11_add_module(singularity_eos
  module.cpp
  modifier_shifted.cpp
  modifier_scaled.cpp
  modifier_bilinear_ramp.cpp
)
target_link_libraries(singularity_eos PRIVATE singularity-eos_Interface)

include(GNUInstallDirs)

set(PYTHON_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/site-packages")

install(TARGETS singularity_eos
  COMPONENT python
  LIBRARY DESTINATION "${PYTHON_INSTALL_DIR}")
