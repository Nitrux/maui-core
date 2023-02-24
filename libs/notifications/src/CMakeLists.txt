# SPDX-FileCopyrightText: 2020 Carl Schwan <carl@carlschwan.eu>
#
# SPDX-License-Identifier: BSD-2-Clause

#ecm_create_qm_loader(mauicorenotifications_QM_LOADER libmauicorenotificationsplugin_qt)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/code
    )

set(
    SRCS
    code/notificationimagesstorage.cpp
    code/notificationserver.cpp
    code/notifications.cpp
    code/notificationsimageutils.cpp
    code/notificationsimageprovider.cpp
    code/plugin.cpp
    code/notification.cpp
    code/notificationsmodel.cpp
    code/historymodel.cpp
    code/datehelper.cpp


    ${mauicorenotifications_QM_LOADER}
    )

set(
    headers
    code/notificationimagesstorage.h
    code/notificationserver.h
#    code/notifications_plugin.h

    code/notifications.h
    code/notificationsimageutils.h
    code/notificationsimageprovider.h
    code/notification.h
    code/notificationsmodel.h
    code/historymodel.h
    code/datehelper.h
    )

set(
    pluginData
    controls/qmldir
    )

qt_add_dbus_interface(SRCS code/org.freedesktop.Notifications.xml notifications_interface )

qt_add_dbus_adaptor(SRCS code/org.freedesktop.Notifications.xml code/notificationserver.h NotificationServer notifications_adaptor)

if(QUICK_COMPILER)
    qtquick_compiler_add_resources(mauicorenotifications_QML_QRC resources.qrc)
else()
    qt5_add_resources(mauicorenotifications_QML_QRC resources.qrc)
endif()

ecm_generate_qmltypes(org.mauicore.notifications ${PROJECT_VERSION} DESTINATION ${KDE_INSTALL_QMLDIR}/org/mauicore/notifications)

add_library(
    ${PROJECT_NAME}
    SHARED
    ${SRCS}
    ${headers}
    )
add_library(MauiCore::Notifications ALIAS ${PROJECT_NAME})

generate_export_header(${PROJECT_NAME} BASE_NAME Notifications)
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME Notifications
    )

target_include_directories(${PROJECT_NAME}
    INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/Maui/Core/Notifications>")

target_include_directories(${PROJECT_NAME}  PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_BINARY_DIR};>")

if(QUICK_COMPILER)
    add_definitions(-DQUICK_COMPILER)
    target_compile_definitions(${PROJECT_NAME}  PUBLIC QUICK_COMPILER)
endif()

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    Qt5::Core
    Qt5::Quick
    Qt5::DBus
    Qt5::Gui
    KF5::I18n
    )

install(TARGETS ${PROJECT_NAME}  EXPORT MauiCoreNotificationsTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
    ${headers}
    ${CMAKE_CURRENT_BINARY_DIR}/notifications_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/Maui/Core/Notifications
    COMPONENT Devel)

if (BUILD_SHARED_LIBS)
    add_custom_target(copy_notifications_to_bin ALL
        COMMAND ${CMAKE_COMMAND} -E
        make_directory ${CMAKE_BINARY_DIR}/bin/org/mauicore/notifications/
        COMMAND ${CMAKE_COMMAND} -E
        copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/controls ${CMAKE_BINARY_DIR}/bin/org/mauicore/notifications/
        COMMAND ${CMAKE_COMMAND} -E
        copy $<TARGET_FILE:MauiCoreNotifications> ${CMAKE_BINARY_DIR}/bin/org/mauicore/notifications/
        )

    if(QUICK_COMPILER)
        install(FILES controls/qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/org/mauicore/notifications)
    else()
        install(DIRECTORY controls/ DESTINATION ${KDE_INSTALL_QMLDIR}/org/mauicore/notifications)
    endif()

    #include(ECMGeneratePriFile)
    #ecm_generate_pri_file(BASE_NAME KQuickImageEditor LIB_NAME KQuickImageEditor DEPS "core qml quick svg" FILENAME_VAR PRI_FILENAME )
    #install(FILES ${PRI_FILENAME}
    #DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

endif()

install(TARGETS ${PROJECT_NAME}  DESTINATION ${KDE_INSTALL_QMLDIR}/org/mauicore/notifications )
