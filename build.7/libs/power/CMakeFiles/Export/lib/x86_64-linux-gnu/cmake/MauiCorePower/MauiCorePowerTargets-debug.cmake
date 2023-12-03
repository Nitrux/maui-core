#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MauiCore::Power" for configuration "Debug"
set_property(TARGET MauiCore::Power APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MauiCore::Power PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "Qt6::Core;Qt6::Qml;KF6::Solid;KF6::IdleTime;KF6::CoreAddons;KF6::I18n;KF6::Service;Qt6::DBus"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/libMauiCorePower.so.0.6.6"
  IMPORTED_SONAME_DEBUG "libMauiCorePower.so.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS MauiCore::Power )
list(APPEND _IMPORT_CHECK_FILES_FOR_MauiCore::Power "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/libMauiCorePower.so.0.6.6" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
