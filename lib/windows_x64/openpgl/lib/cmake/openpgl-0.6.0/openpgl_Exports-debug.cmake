#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "openpgl::openpgl" for configuration "Debug"
set_property(TARGET openpgl::openpgl APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(openpgl::openpgl PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/openpgl_d.lib"
  )

list(APPEND _cmake_import_check_targets openpgl::openpgl )
list(APPEND _cmake_import_check_files_for_openpgl::openpgl "${_IMPORT_PREFIX}/lib/openpgl_d.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
