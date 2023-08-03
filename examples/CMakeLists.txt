include(../cmake/flags.cmake)
include(../cmake/ccache.cmake)

function(add_cli_exe T)
  add_executable(${T} ${ARGN})

  set_flags(${T})
  setup_linker(${T})
  set_sanitizers(${T})

  target_link_libraries(${T} PUBLIC
    ${CMAKE_THREAD_LIBS_INIT}
  )

  target_include_directories(${T} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
  )

  set_property(TARGET ${T} PROPERTY FOLDER "Examples")

  add_dependencies(${T} mcquack_vector)
endfunction()

add_cli_exe(emplace_back emplace_back.cpp)
