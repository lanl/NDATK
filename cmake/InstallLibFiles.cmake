# NDTAK has three hard-coded options for data paths, depending on if you're on HPC, XLAN, or LLNL machines.
# This function checks those three paths to determine which one is valid and sets NDATK_DATA_PATH cmake variable
function(install_lib_files)
  if (DEFINED ENV{NDATK_DATA_PATH})
    set(NDATK_DATA_PATH $ENV{NDATK_DATA_PATH})
  else()
    set(searchPaths 
      "/opt/local/codes/data/nuclear/ndatk/data" 
      "/usr/gapps/lanl-data/nuclear/ndatk/data"
      "/usr/projects/data/nuclear/ndatk/data"
    )
    foreach(path ${searchPaths})
      if (EXISTS ${path})
        set(NDATK_DATA_PATH ${path})
      endif()
    endforeach()
  endif()

  if (DEFINED NDATK_DATA_PATH)
    message("ndatk InstallLibFiles -- using NDATK_DATA_PATH: ${NDATK_DATA_PATH}")
  else()
    message(WARNING "ndatk -- unable to find data.  Set NDATK_DATA_PATH environment variable to location of data.")
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
    if (EXISTS "${NDATK_DATA_PATH}/${library}")
      INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake/lib_files/${library}.lib"
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        PERMISSIONS OWNER_READ OWNER_WRITE
                    GROUP_READ
                    WORLD_READ)
    endif()
  endforeach()

# install exsdir file - TODO: configure exsdir based on installed libraries
  INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/cmake/lib_files/exsdir"
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        PERMISSIONS OWNER_READ OWNER_WRITE
                    GROUP_READ
                    WORLD_READ)

  if (EXISTS "${CMAKE_INSTALL_PREFIX}/data")
  else()
    INSTALL(CODE "execute_process(COMMAND cmake -E create_symlink ${NDATK_DATA_PATH} ${CMAKE_INSTALL_PREFIX}/data)")
  endif()
endfunction()
