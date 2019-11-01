if (ndatk.tests)
  configure_file(${CMAKE_CURRENT_LIST_DIR}/chart.dat chart.dat COPYONLY)
  configure_file(${CMAKE_CURRENT_LIST_DIR}/endf71x.lib endf71x.lib COPYONLY)
  configure_file(${CMAKE_CURRENT_LIST_DIR}/lanl2006.lib lanl2006.lib COPYONLY)
  configure_file(${CMAKE_CURRENT_LIST_DIR}/mtmg08.lib mtmg08.lib COPYONLY)
  configure_file(${CMAKE_CURRENT_LIST_DIR}/xsdir.beta3 xsdir.beta3 COPYONLY)
  configure_file(${CMAKE_CURRENT_LIST_DIR}/xsdir.inc xsdir.inc COPYONLY)

  add_executable(test_Chart ${CMAKE_CURRENT_LIST_DIR}/test_Chart.cc)
  target_link_libraries(test_Chart PUBLIC ndatk UnitTest  )
  add_test(NAME test_Chart COMMAND test_Chart ./chart.dat)

  add_executable(test_Exsdir ${CMAKE_CURRENT_LIST_DIR}/test_Exsdir.cc)
  target_link_libraries(test_Exsdir PUBLIC ndatk UnitTest  )

  add_executable(test_FileStat ${CMAKE_CURRENT_LIST_DIR}/test_FileStat.cc)
  target_link_libraries(test_FileStat PUBLIC ndatk UnitTest )

  add_executable(test_translate_isomer ${CMAKE_CURRENT_LIST_DIR}/test_translate_isomer.cc)
  target_link_libraries(test_translate_isomer PUBLIC ndatk UnitTest )

  add_executable(test_utils ${CMAKE_CURRENT_LIST_DIR}/test_utils.cc)
  target_link_libraries(test_utils PUBLIC ndatk UnitTest )

  add_executable(use0_Library ${CMAKE_CURRENT_LIST_DIR}/use0_Library.cc)
  target_link_libraries(use0_Library PUBLIC ndatk UnitTest )

  add_executable(use1_Chart ${CMAKE_CURRENT_LIST_DIR}/use1_Chart.cc)
  target_link_libraries(use1_Chart PUBLIC ndatk UnitTest )

  add_executable(use2_Library ${CMAKE_CURRENT_LIST_DIR}/use2_Library.cc)
  target_link_libraries(use2_Library PUBLIC ndatk UnitTest )

#  add_executable(use3_ndi_comp_of ${CMAKE_CURRENT_LIST_DIR}/use3_ndi_comp_of.cc)
#  target_link_libraries(use3_ndi_comp_of PUBLIC ndatk UnitTest)
endif()
