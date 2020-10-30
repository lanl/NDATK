function(create_exsdir_file)
  set(filename ${CMAKE_CURRENT_BINARY_DIR}/exsdir)
  file(WRITE ${filename} "type: ndatk_exsdir_1.0\n")
  file(APPEND ${filename} "name: exsdir\n")
  file(APPEND ${filename} "%%\n")
  file(APPEND ${filename} "DIRECTORY\n")
  
  # write chart file
  if (EXISTS ${NDATK_DATAPATH}/endf71x/chart)
    file(APPEND ${filename} "chart 0.0 endf71x/chart\n")
  endif()

  # write .lib files
  foreach(library ${libraries})
    if (EXISTS ${NDATK_DATAPATH}/${library})
      file(APPEND ${filename} "${library} 0.0 ${library}.lib\n")
    endif()
  endforeach()

  # handle e68g_103 since it doesn't have an associated directory
  if (EXISTS ${NDATK_DATAPATH}/mt71x)
    if (EXISTS ${NDATK_DATAPATH}/mcplib84)
      file(APPEND ${filename} "e68g_103 0.0 e68g_103.lib\n")
    endif()
  endif()

  # write include lines
  foreach(library ${libraries})
    if (EXISTS ${NDATK_DATAPATH}/${library})
      if (${library} STREQUAL "mt71x")
        file(APPEND ${filename} "include ${library}/xsdir_pt\n")
      else()
        file(APPEND ${filename} "include ${library}/xsdir\n")
      endif()
    endif()
  endforeach()

  INSTALL(FILES "${filename}"
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    PERMISSIONS OWNER_READ OWNER_WRITE
                GROUP_READ
                WORLD_READ)


endfunction()
