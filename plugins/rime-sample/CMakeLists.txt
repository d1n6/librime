project(rime-sample)
cmake_minimum_required(VERSION 3.10)

set(SAMPLE_VERSION 1.0.0)
set(SAMPLE_SOVERSION 1)

aux_source_directory(src sample_src)

set(plugin_library rime-sample)
set(sample_deps ${rime_library})
set(sample_modules "sample")

if(0)
  # to build the sample plugin, console app and tests, set BUILD_SAMPLE=ON
  set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

  message(STATUS "${plugin_library} provides modules: ${sample_modules}")
  add_library(${plugin_library} ${sample_src})
  target_link_libraries(${plugin_library} ${sample_deps})
  set_target_properties(${plugin_library}
    PROPERTIES
    VERSION ${SAMPLE_VERSION}
    SOVERSION ${SAMPLE_SOVERSION})
  if(XCODE_VERSION)
    set_target_properties(${plugin_library}
      PROPERTIES
      INSTALL_NAME_DIR "@rpath")
  endif(XCODE_VERSION)
  install(TARGETS ${plugin_library} DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})

  add_subdirectory(tools)
  if(BUILD_TEST)
    message(STATUS --------------${sample_src})
    add_subdirectory(test)
  endif()
else()
  # to build as a standard Rime plugin, link or copy the directory to plugins/
  add_library(rime-sample-objs OBJECT ${sample_src})
  if(BUILD_SHARED_LIBS)
    set_target_properties(rime-sample-objs
      PROPERTIES
      POSITION_INDEPENDENT_CODE ON)
  endif()

  set(plugin_name ${plugin_library} PARENT_SCOPE)
  set(plugin_objs $<TARGET_OBJECTS:rime-sample-objs> PARENT_SCOPE)
  set(plugin_deps ${sample_deps} PARENT_SCOPE)
  set(plugin_modules ${sample_modules} PARENT_SCOPE)
endif()
