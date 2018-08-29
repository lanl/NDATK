if(CMAKE_VERSION VERSION_LESS 3.10.2)
  macro(include_guard)
    if(${ARGC})
      set(scope ${ARGV0})
      if(NOT scope STREQUAL "DIRECTORY"
          AND NOT scope STREQUAL "GLOBAL")
        message(FATAL_ERROR "Invalid argument to include_gaurd: ${scope}")
      endif()
    else()
      set(scope DIRECTORY)
    endif()

    string(SHA512 path_hash "${CMAKE_CURRENT_LIST_FILE}")

    if(scope STREQUAL DIRECTORY)
      if(DEFINED ${path_hash})
        message("already covered ${CMAKE_CURRENT_LIST_FILE}")
        return()
      endif()
      set(${path_hash} TRUE)
    else()
      get_property(${path_hash} GLOBAL PROPERTY ${path_hash} SET)
      if(${path_hash})
        message("already covered ${CMAKE_CURRENT_LIST_FILE}")
        return()
      endif()
      set_property(GLOBAL PROPERTY ${path_hash} TRUE)
    endif()

    unset(scope)
    unset(path_hash)
  endmacro()

endif()
