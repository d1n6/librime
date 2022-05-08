project(rime-cloud)
cmake_minimum_required(VERSION 3.10)

aux_source_directory(src cloud_src)

add_library(rime-cloud-objs OBJECT ${cloud_src})
if(BUILD_SHARED_LIBS)
  set_target_properties(rime-cloud-objs
    PROPERTIES
    POSITION_INDEPENDENT_CODE ON)
endif()

set(plugin_name rime-cloud PARENT_SCOPE)
set(plugin_objs $<TARGET_OBJECTS:rime-cloud-objs> PARENT_SCOPE)
set(plugin_deps ${rime_library} PARENT_SCOPE)
set(plugin_modules "cloud" PARENT_SCOPE)
