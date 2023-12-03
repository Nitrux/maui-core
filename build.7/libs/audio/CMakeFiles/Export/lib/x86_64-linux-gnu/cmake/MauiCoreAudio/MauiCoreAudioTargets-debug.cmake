#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MauiCore::Audio" for configuration "Debug"
set_property(TARGET MauiCore::Audio APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(MauiCore::Audio PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "Qt6::Core;Qt6::Qml;Qt6::Gui;Qt6::Widgets;Qt6::DBus;Qt6::Quick;KF6::I18n"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/libMauiCoreAudio.so.0.6.6"
  IMPORTED_SONAME_DEBUG "libMauiCoreAudio.so.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS MauiCore::Audio )
list(APPEND _IMPORT_CHECK_FILES_FOR_MauiCore::Audio "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/libMauiCoreAudio.so.0.6.6" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
