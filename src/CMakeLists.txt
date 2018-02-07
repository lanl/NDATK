target_include_directories(ndatk PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
  $<INSTALL_INTERFACE:include/ndatk>)

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
    ${CMAKE_CURRENT_LIST_DIR}/translate_isomerTest.cc
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
