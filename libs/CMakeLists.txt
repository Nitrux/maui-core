# Copyright 2018-2020 Camilo Higuita <milo.h@aol.com>
# Copyright 2018-2020 Nitrux Latinoamericana S.C.
#
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.16)

set(KF5_VERSION "5.70.0")
set(REQUIRED_QT_VERSION 5.15.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

project(MauiCore VERSION ${MAUICORE_VERSION})

find_package(ECM ${KF5_VERSION} NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(GNUInstallDirs)
include(FeatureSummary)
include(ECMPoQmTools)
include(ECMSetupVersion)
include(ECMGenerateQmlTypes)
include(CMakePackageConfigHelpers)
include(KDEPackageAppTemplates)
include(KDECompilerSettings)
include(KDEInstallDirs)
include(KDECMakeSettings)

##CMAKE PARTS
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/MauiCore")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/MauiCoreConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/MauiCoreConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    PATH_VARS  KF5_INCLUDE_INSTALL_DIR CMAKE_INSTALL_PREFIX
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/MauiCoreConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/MauiCoreConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

#install(EXPORT MauiCoreTargets
#    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
#    FILE MauiCoreTargets.cmake
#    NAMESPACE MauiCore::)

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX MauiCore
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/mauicore_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/MauiCoreConfigVersion.cmake"
    SOVERSION ${PROJECT_VERSION_MAJOR}
    )

#target_include_directories(${PROJECT_NAME}
#    INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/MauiCore>")

#target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_BINARY_DIR};>")

#add_subdirectory(network)
add_subdirectory(audio)
add_subdirectory(notifications)
add_subdirectory(power)


feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
