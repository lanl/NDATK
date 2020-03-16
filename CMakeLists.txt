cmake_minimum_required(VERSION 3.10)

if( DEFINED PROJECT_NAME )
  set( subproject ON )
else()
  set( subproject OFF )
endif()

project(ndatk
  VERSION 1.1.1
  DESCRIPTION "Library Abstraction for ACE-format Nuclear Data"
  LANGUAGES CXX)

include(CTest)
include(CMakePackageConfigHelpers)
include(CMakeDependentOption)

list(APPEND CMAKE_MODULE_PATH "${ndatk_SOURCE_DIR}/.cmake")
include(Warnings)

option(ndatk.shared_library
  "Build the ndatk as a shared library"
  "${BUILD_SHARED_LIBS}")

CMAKE_DEPENDENT_OPTION(ndatk.position_independent_code
  "Build the ndatk library with position independent code"
  "${CMAKE_POSITION_INDEPENDENT_CODE}"
  "ndatk_shared_library" ON)

CMAKE_DEPENDENT_OPTION(ndatk.tests
  "Build the ndatk tests and integrate with ctest"
  ON "BUILD_TESTING; NOT subproject" OFF)

if(ndatk.shared_library)
  add_library(ndatk SHARED "")
else()
  add_library(ndatk STATIC "")
endif()

add_library(ndatk::ndatk ALIAS ndatk)

option( ndatk.use_cxx17
        "Build ndatk using c++17 capabilities"
        OFF )
if( ndatk.use_cxx17 )
    target_compile_features(ndatk PRIVATE cxx_std_17)
    target_compile_definitions( ndatk PRIVATE USING_CXX17 )
else()
    target_compile_features(ndatk PRIVATE cxx_std_14)
endif()

set_target_properties(ndatk PROPERTIES
  POSITION_INDEPENDENT_CODE "${ndatk.position_independent_code}"
  CXX_EXTENSIONS OFF
  WARN_ALL ON
  WARN_ERROR ON)

target_link_libraries(ndatk PRIVATE
  $<BUILD_INTERFACE:Warnings::Warnings_CXX>)

add_subdirectory(src)
add_subdirectory(test)

install(TARGETS ndatk
  EXPORT ndatkConfig
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  PERMISSIONS OWNER_EXECUTE OWNER_READ
              GROUP_EXECUTE GROUP_READ
              WORLD_EXECUTE WORLD_READ)

install(DIRECTORY src/
  DESTINATION include/ndatk
  PATTERN "*Test*" EXCLUDE
  PATTERN "*.hh"
  PERMISSIONS OWNER_READ OWNER_WRITE
              GROUP_READ
              WORLD_READ)

install(EXPORT ndatkConfig
  FILE ndatkConfig.cmake
  NAMESPACE ndatk::
  DESTINATION share/cmake/ndatk
  PERMISSIONS OWNER_READ OWNER_WRITE
              GROUP_READ
              WORLD_READ)

write_basic_package_version_file("ndatkConfigVersion.cmake"
  VERSION ${ndatk_VERSION}
  COMPATIBILITY SameMajorVersion)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/ndatkConfigVersion.cmake"
  DESTINATION share/cmake/ndatk
  PERMISSIONS OWNER_READ OWNER_WRITE
              GROUP_READ
              WORLD_READ)

if(NOT subproject)
  include( InstallRequiredSystemLibraries )
  set( CPACK_PACKAGE_VENDOR "Los Alamos National Laboratory" )
  set( CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE" )
  set( CMAKE_PROJECT_HOMEPAGE_URL "https://xcp-stash.lanl.gov/projects/NDT/repos/ndatk/browse" )
  set( CPACK_PACKAGE_CONTACT "amccartney@lanl.gov" )
  include( CPack )
endif()
