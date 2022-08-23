# SPDX-FileCopyrightText: 2021 Camilo Higuita <milo.h@aol.com>
#
# SPDX-License-Identifier: BSD-2-Clause

cmake_minimum_required(VERSION 3.16)

set(AUTOMOC_MOC_OPTIONS -Muri=org.mauicore.audio)

project(MauiCoreAudio LANGUAGES CXX VERSION ${MAUICORE_VERSION})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/MauiCoreAudio")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/MauiCoreAudioConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/MauiCoreAudioConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
    PATH_VARS KF5_INCLUDE_INSTALL_DIR CMAKE_INSTALL_PREFIX
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/MauiCoreAudioConfigVersion.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/MauiCoreAudioConfig.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT MauiCoreAudioTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE MauiCoreAudioTargets.cmake
    NAMESPACE MauiCore::)

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX MauiCoreAudio
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/mauicoreaudio_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/MauiCoreAudioConfigVersion.cmake"
    SOVERSION ${PROJECT_VERSION_MAJOR}
    )

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/mauicoreaudio_version.h"
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/Maui/Core/Audio
    COMPONENT Devel)

option(QUICK_COMPILER "Use QtQuick compiler to improve performance" TRUE)

find_package(Qt5 ${REQUIRED_QT_VERSION} COMPONENTS Core Quick DBus Gui Widgets REQUIRED)
find_package(KF5 ${REQUIRED_KF5_VERSION} REQUIRED COMPONENTS I18n)

find_package(PkgConfig)
find_package(Canberra REQUIRED)

find_package(CanberraPulse)
set_package_properties(CanberraPulse PROPERTIES
    DESCRIPTION "Pulseaudio backend for libcanberra"
    PURPOSE "Required for volume feedback sounds"
    TYPE RUNTIME
    )

find_package(SoundThemeFreedesktop)
set_package_properties(SoundThemeFreedesktop PROPERTIES
    DESCRIPTION "The standard freedesktop sound theme"
    PURPOSE "Required for volume feedback sounds"
    URL "https://www.freedesktop.org/wiki/Specifications/sound-theme-spec/"
    TYPE RUNTIME
    )

pkg_check_modules(LIBPULSE libpulse REQUIRED IMPORTED_TARGET)
pkg_check_modules(LIBPULSE_MAINLOOP libpulse-mainloop-glib REQUIRED IMPORTED_TARGET)

if(QUICK_COMPILER)
        find_package(Qt5QuickCompiler)
        set_package_properties(Qt5QuickCompiler PROPERTIES
                DESCRIPTION "Compile QML at build time"
                TYPE OPTIONAL
        )
endif()

add_subdirectory(src)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
