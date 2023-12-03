include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/code)

set(power_SRCS
    code/powermanagementengine.cpp
    code/powermanagementjob.cpp
    code/brightnesscontrol.cpp
    code/batteryinfo.cpp
    code/powerprofile.cpp
    code/caskpowerplugin.cpp
    code/inhibitioncontrol.cpp)

ecm_add_qml_module(${PROJECT_NAME} URI "org.mauicore.power" VERSION 1.0 CLASSNAME PowerPlugin)

#ecm_target_qml_sources(${PROJECT_NAME} SOURCES
#    controls/PulseObjectFilterModel.qml)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${power_SRCS})

add_library(MauiCore::Power ALIAS ${PROJECT_NAME})

generate_export_header(${PROJECT_NAME} BASE_NAME Power)
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME "Power")

target_include_directories(${PROJECT_NAME}
    INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/Maui/Core/Power>")

target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_BINARY_DIR};>")

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt6::Core
    Qt6::Qml
    KF6::Solid
    KF6::IdleTime
    KF6::CoreAddons
    KF6::I18n
    KF6::Service
    Qt6::DBus)

ecm_finalize_qml_module(${PROJECT_NAME} DESTINATION ${KDE_INSTALL_QMLDIR})
ecm_generate_qmltypes(org.mauicore.power ${PROJECT_VERSION} DESTINATION ${KDE_INSTALL_QMLDIR}/org/mauicore/power)

install(TARGETS ${PROJECT_NAME} EXPORT MauiCorePowerTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
    ${headers}
    ${CMAKE_CURRENT_BINARY_DIR}/power_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/Maui/Core/Power
    COMPONENT Devel)
