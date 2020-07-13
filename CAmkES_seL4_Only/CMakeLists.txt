# This file will be regenerated, do not edit

cmake_minimum_required(VERSION 3.8.2)

project (top_impl_Instance C)

add_definitions(-DCAMKES)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "(C|c?)lang")
  add_compile_options("$<$<CONFIG:Release>:-Oz>")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-fstack-usage)
  add_compile_options("$<$<CONFIG:Release>:-Os>")
endif()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/types)

DeclareCAmkESComponent(A_impl
  SOURCES components/A_impl//src/a.c components/A_impl/src/sb_A_impl.c types/src/sb_queue_int8_t_2.c
  INCLUDES components/A_impl/includes/ types/includes
)

DeclareCAmkESComponent(B_impl
  SOURCES components/B_impl//src/b.c components/B_impl/src/sb_B_impl.c types/src/sb_queue_int8_t_2.c
  INCLUDES components/B_impl/includes/ types/includes
)

DeclareCAmkESComponent(C_impl
  SOURCES components/C_impl//src/c.c components/C_impl/src/sb_C_impl.c types/src/sb_queue_int8_t_2.c
  INCLUDES components/C_impl/includes/ types/includes
)

DeclareCAmkESComponent(D_impl
  SOURCES components/D_impl//src/d.c components/D_impl/src/sb_D_impl.c types/src/sb_queue_int8_t_2.c
  INCLUDES components/D_impl/includes/ types/includes
)

DeclareCAmkESRootserver(top_impl_Instance.camkes)
