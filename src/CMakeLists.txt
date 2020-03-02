cmake_policy( SET CMP0079 NEW )

target_include_directories(ndatk PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
  #
  # Why is the include directory after installation not prefixed by the
  # project name?
  #
  $<INSTALL_INTERFACE:include/ndatk>)

#
# Why on Earth are you copying source files to the binary tree?
#
# The previous build system assumed in-source builds and existing
# tests use their own source files as resources for testing. This
# was a bad idea then, and is troublesome now.
#
file(COPY utilsTest.cc DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY FinderTest.cc DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if( ndatk.use_cxx17 )
    find_package( Boost REQUIRED )
    target_include_directories( ndatk PRIVATE ${Boost_INCLUDE_DIRS} )
else()
    find_package( Boost COMPONENTS filesystem REQUIRED )
    target_link_libraries( ndatk PUBLIC Boost::filesystem )
endif()

target_sources(ndatk PRIVATE
  $<BUILD_INTERFACE:
    ${CMAKE_CURRENT_LIST_DIR}/Chart.cc
    ${CMAKE_CURRENT_LIST_DIR}/CuratedData.cc
    ${CMAKE_CURRENT_LIST_DIR}/Exsdir.cc
    ${CMAKE_CURRENT_LIST_DIR}/FileStat.cc
    ${CMAKE_CURRENT_LIST_DIR}/Finder.cc
    ${CMAKE_CURRENT_LIST_DIR}/Library.cc
    ${CMAKE_CURRENT_LIST_DIR}/element_composition.cc
    ${CMAKE_CURRENT_LIST_DIR}/translate_isomer.cc
    ${CMAKE_CURRENT_LIST_DIR}/utils.cc> )
 
target_sources(ndatk PUBLIC
  $<BUILD_INTERFACE:
    ${CMAKE_CURRENT_LIST_DIR}/Chart.hh
    ${CMAKE_CURRENT_LIST_DIR}/constants.hh
    ${CMAKE_CURRENT_LIST_DIR}/CuratedData.hh
    ${CMAKE_CURRENT_LIST_DIR}/element_composition.hh
    ${CMAKE_CURRENT_LIST_DIR}/Exsdir.hh
    ${CMAKE_CURRENT_LIST_DIR}/FileStat.hh
    ${CMAKE_CURRENT_LIST_DIR}/Finder.hh
    ${CMAKE_CURRENT_LIST_DIR}/Library.hh
    ${CMAKE_CURRENT_LIST_DIR}/ndatk.hh
    ${CMAKE_CURRENT_LIST_DIR}/translate_isomer.hh
    ${CMAKE_CURRENT_LIST_DIR}/utils.hh>
  $<INSTALL_INTERFACE:
    include/ndatk/Chart.hh
    include/ndatk/constants.hh
    include/ndatk/CuratedData.hh
    include/ndatk/element_composition.hh
    include/ndatk/Exsdir.hh
    include/ndatk/FileStat.hh
    include/ndatk/Finder.hh
    include/ndatk/Library.hh
    include/ndatk/ndatk.hh
    include/ndatk/translate_isomer.hh
    include/ndatk/utils.hh>)

if (ndatk.tests)
  add_library(UnitTest STATIC
    ${CMAKE_CURRENT_LIST_DIR}/UnitTest.cc
    ${CMAKE_CURRENT_LIST_DIR}/UnitTest.hh)

  add_executable(ndatk.test
    ${CMAKE_CURRENT_LIST_DIR}/ChartTest.cc
    ${CMAKE_CURRENT_LIST_DIR}/ChartTest.hh
    ${CMAKE_CURRENT_LIST_DIR}/ExsdirTest.cc
    ${CMAKE_CURRENT_LIST_DIR}/ExsdirTest.hh
    ${CMAKE_CURRENT_LIST_DIR}/FinderTest.cc
    ${CMAKE_CURRENT_LIST_DIR}/FinderTest.hh
    ${CMAKE_CURRENT_LIST_DIR}/LibraryTest.cc
    ${CMAKE_CURRENT_LIST_DIR}/LibraryTest.hh
    ${CMAKE_CURRENT_LIST_DIR}/TestRunner.cc
    ${CMAKE_CURRENT_LIST_DIR}/translate_isomerTest.cc
    ${CMAKE_CURRENT_LIST_DIR}/translate_isomerTest.hh
    ${CMAKE_CURRENT_LIST_DIR}/utilsTest.cc
    ${CMAKE_CURRENT_LIST_DIR}/utilsTest.hh)

  target_link_libraries(ndatk.test PUBLIC ndatk)
  target_link_libraries(ndatk.test PUBLIC UnitTest)

  add_test(NAME ndatk.test COMMAND ndatk.test)
endif()
