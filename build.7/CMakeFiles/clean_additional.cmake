# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "libs/audio/src/CMakeFiles/MauiCoreAudio_autogen.dir/AutogenUsed.txt"
  "libs/audio/src/CMakeFiles/MauiCoreAudio_autogen.dir/ParseCache.txt"
  "libs/audio/src/MauiCoreAudio_autogen"
  "libs/notifications/src/CMakeFiles/MauiCoreNotifications_autogen.dir/AutogenUsed.txt"
  "libs/notifications/src/CMakeFiles/MauiCoreNotifications_autogen.dir/ParseCache.txt"
  "libs/notifications/src/MauiCoreNotifications_autogen"
  "libs/power/src/CMakeFiles/MauiCorePower_autogen.dir/AutogenUsed.txt"
  "libs/power/src/CMakeFiles/MauiCorePower_autogen.dir/ParseCache.txt"
  "libs/power/src/MauiCorePower_autogen"
  )
endif()
