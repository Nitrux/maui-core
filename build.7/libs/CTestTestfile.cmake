# CMake generated Testfile for 
# Source directory: /home/camiloh/maui-core/libs
# Build directory: /home/camiloh/maui-core/build.7/libs
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(appstreamtest "/usr/bin/cmake" "-DAPPSTREAMCLI=/usr/bin/appstreamcli" "-DINSTALL_FILES=/home/camiloh/maui-core/build.7/install_manifest.txt" "-P" "/usr/share/ECM/kde-modules/appstreamtest.cmake")
set_tests_properties(appstreamtest PROPERTIES  _BACKTRACE_TRIPLES "/usr/share/ECM/kde-modules/KDECMakeSettings.cmake;165;add_test;/usr/share/ECM/kde-modules/KDECMakeSettings.cmake;183;appstreamtest;/usr/share/ECM/kde-modules/KDECMakeSettings.cmake;0;;/home/camiloh/maui-core/libs/CMakeLists.txt;35;include;/home/camiloh/maui-core/libs/CMakeLists.txt;0;")
subdirs("audio")
subdirs("notifications")
subdirs("power")
