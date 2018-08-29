macro(_sbeMoveToNextNonEmptyCharacter)
  math(EXPR json_index "${json_index} + 1")
  if(${json_index} LESS ${json_jsonLen})
    string(SUBSTRING "${json_string}" ${json_index} 1 json_char)
    while(${json_char} MATCHES "[ \t\n\r]" AND ${json_index} LESS ${json_jsonLen})
      math(EXPR json_index "${json_index} + 1")
      string(SUBSTRING "${json_string}" ${json_index} 1 json_char)
    endwhile()
  endif()
endmacro()
