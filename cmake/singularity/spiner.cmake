macro(singularity_enable_spiner target)
  if(NOT TARGET spiner::spiner)
    find_package(spiner REQUIRED)
  endif()
  target_link_libraries(${target} PUBLIC spiner::spiner)
endmacro()
