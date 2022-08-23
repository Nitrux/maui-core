include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/code
    )

set(power_SRCS
    code/powermanagementengine.cpp
    code/powermanagementjob.cpp
    code/brightnesscontrol.cpp
    code/batteryinfo.cpp
    code/powerprofile.cpp
    code/caskpowerplugin.cpp
    code/inhibitioncontrol.cpp
)

set(
    pluginData
    controls/qmldir
    )

if(QUICK_COMPILER)
    qtquick_compiler_add_resources(power_QML_QRC resources.qrc)
else()
    qt5_add_resources(power_QML_QRC resources.qrc)
endif()


ecm_generate_qmltypes(org.mauicore.power ${PROJECT_VERSION} DESTINATION ${KDE_INSTALL_QMLDIR}/org/mauicore/power)

add_library(${PROJECT_NAME} SHARED ${power_SRCS} ${power_QML_QRC})
add_library(MauiCore::Power ALIAS ${PROJECT_NAME})

generate_export_header(${PROJECT_NAME} BASE_NAME Power)
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME Power
    )

target_include_directories(${PROJECT_NAME}
    INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/Maui/Core/Power>")

target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_BINARY_DIR};>")

if(QUICK_COMPILER)
    add_definitions(-DQUICK_COMPILER)
    target_compile_definitions(${PROJECT_NAME} PUBLIC QUICK_COMPILER)
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt5::Core
    Qt5::Qml
    KF5::Solid
    KF5::IdleTime
    KF5::CoreAddons
    KF5::I18n
    KF5::Service
    Qt::DBus
)

install(TARGETS ${PROJECT_NAME} EXPORT MauiCorePowerTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
    ${headers}
    ${CMAKE_CURRENT_BINARY_DIR}/power_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/Maui/Core/Power
    COMPONENT Devel)

if (BUILD_SHARED_LIBS)
    add_custom_target(copy_power_to_bin ALL
        COMMAND ${CMAKE_COMMAND} -E
        make_directory ${CMAKE_BINARY_DIR}/bin/org/mauicore/power/
        COMMAND ${CMAKE_COMMAND} -E
        copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/controls ${CMAKE_BINARY_DIR}/bin/org/mauicore/power/
        COMMAND ${CMAKE_COMMAND} -E
        copy $<TARGET_FILE:MauiCorePower> ${CMAKE_BINARY_DIR}/bin/org/mauicore/power/
        )

    if(QUICK_COMPILER)
        install(FILES controls/qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/org/mauicore/power)
    else()
        install(DIRECTORY controls/ DESTINATION ${KDE_INSTALL_QMLDIR}/org/mauicore/power)
    endif()

    #include(ECMGeneratePriFile)
    #ecm_generate_pri_file(BASE_NAME KQuickImageEditor LIB_NAME KQuickImageEditor DEPS "core qml quick svg" FILENAME_VAR PRI_FILENAME )
    #install(FILES ${PRI_FILENAME}
    #DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

endif()

install(TARGETS ${PROJECT_NAME} DESTINATION ${KDE_INSTALL_QMLDIR}/org/mauicore/power )

