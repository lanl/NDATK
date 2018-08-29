cmake_minimum_required(VERSION 3.2)

if( DEFINED PROJECT_NAME )
  set( subproject ON )
else()
  set( subproject OFF )
endif()

project(ndatk VERSION 1.1.0 LANGUAGES CXX)
include(CTest)
include(CMakePackageConfigHelpers)
include(CMakeDependentOption)
list(APPEND CMAKE_MODULE_PATH "${ndi_SOURCE_DIR}/.cmake")
include(Warnings)

option(ndatk.shared_library
  "Build the ndatk as a shared library"
  "${BUILD_SHARED_LIBS}")

CMAKE_DEPENDENT_OPTION(ndatk.position_independent_code
  "Build the ndatk library with position independent code"
  "${position_independent_code}"
  "NOT ndatk_shared_library" ON)

CMAKE_DEPENDENT_OPTION(ndatk.tests
  "Build the ndatk tests and integrate with ctest"
  ON "BUILD_TESTING; NOT is_subproject" OFF)

set(ndatk.data_path "${ACE_data_path}" CACHE PATH
  "Path to the installation of the ACE-format nuclear data libraries")

if(ndatk.shared_library)
  add_library(ndatk SHARED "")
else()
  add_library(ndatk STATIC "")
endif()

add_library(ndatk::ndatk ALIAS ndatk)

set_target_properties(ndatk PROPERTIES
  POSITION_INDEPENDENT_CODE "${ndatk.position_independent_code}")

target_compile_features(ndatk PUBLIC cxx_std_11)
set_target_properties(ndatk PROPERTIES CXX_EXTENSIONS OFF)

include(src/CMakeLists.txt)
include(test/CMakeLists.txt)

install(TARGETS ndatk
  EXPORT ndatkConfig
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ
  INCLUDES DESTINATION include/ndatk)

install(DIRECTORY src/
  DESTINATION include/ndatk
  FILES_MATCHING PATTERN "*Test*" EXCLUDE PATTERN "*.hh"
  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ)

install(EXPORT ndatkConfig
  FILE ndatkConfig.cmake
  NAMESPACE ndatk
  DESTINATION share
  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ)

write_basic_package_version_file("ndatkConfigVersion.cmake"
  VERSION ${ndatk_VERSION}
  COMPATIBILITY SameMajorVersion)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/ndatkConfigVersion.cmake"
  DESTINATION share
  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ)
