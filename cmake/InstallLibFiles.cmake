# NDTAK has three hard-coded options for data paths, depending on if you're on HPC, XLAN, or LLNL machines.
# This function checks those three paths to determine which one is valid and sets NDATK_DATAPATH cmake variable
function(install_lib_files)
  if (DEFINED ENV{NDATK_DATAPATH})
    set(NDATK_DATAPATH $ENV{NDATK_DATAPATH}) 
  else()
    set(searchPaths 
      "/opt/local/codes/data/nuclear/ndatk/data" 
      "/usr/gapps/lanl-data/nuclear/ndatk/data"
      "/usr/projects/data/nuclear/ndatk/data"
    )
    foreach(path ${searchPaths})
      if (EXISTS ${path})
        set(NDATK_DATAPATH ${path})
      endif()
    endforeach()
  endif()

  if (DEFINED NDATK_DATAPATH)
    message("ndatk InstallLibFiles -- using NDATK_DATAPATH: ${NDATK_DATAPATH}")
  else()
    message(WARNING "ndatk -- unable to find data.  Set NDATK_DATAPATH environment variable to location of data.")
  endif()

  set(libraries 
    "endf71x"
    "lanl2006"
    "mcplib84"
    "mendf71x"
    "mt71x"
    "mt80"
    "mtmg08"
  )

  foreach(library ${libraries})
    if (EXISTS "${NDATK_DATAPATH}/${library}")
      INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake/lib_files/${library}.lib"
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        PERMISSIONS OWNER_READ OWNER_WRITE
                    GROUP_READ
                    WORLD_READ)
    endif()
  endforeach()

  # handle e68g_103 since it doesn't have an associated directory
  if (EXISTS ${NDATK_DATAPATH}/mcplib84)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake/lib_files/e68g_103.lib"
      DESTINATION ${CMAKE_INSTALL_PREFIX}
      PERMISSIONS OWNER_READ OWNER_WRITE
                  GROUP_READ
                  WORLD_READ)
  endif()

  # handle mendf80 since it doesn't have an associated directory
  if (EXISTS ${NDATK_DATAPATH}/mt80)
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake/lib_files/mendf80.lib"
      DESTINATION ${CMAKE_INSTALL_PREFIX}
      PERMISSIONS OWNER_READ OWNER_WRITE
                  GROUP_READ
                  WORLD_READ)
  endif()

# install exsdir file based on libraries available in NDATK_DATAPATH
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CreateExsdirFile.cmake)
  create_exsdir_file()

  if (EXISTS "${CMAKE_INSTALL_PREFIX}/data")
  else()
    INSTALL(CODE "execute_process(COMMAND cmake -E create_symlink ${NDATK_DATAPATH} ${CMAKE_INSTALL_PREFIX}/data)")
  endif()


endfunction()
