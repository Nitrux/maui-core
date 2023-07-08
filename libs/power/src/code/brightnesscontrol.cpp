#include "brightnesscontrol.h"
#include <QDebug>

#include <QDBusConnectionInterface>
#include <QDBusError>
#include <QDBusInterface>
#include <QDBusMetaType>
#include <QDBusPendingCallWatcher>
#include <QDBusReply>

static const QString SOLID_POWERMANAGEMENT_SERVICE = QStringLiteral("org.kde.Solid.PowerManagement");

BrightnessControl::BrightnessControl(QObject *parent) : QObject(parent)
  ,m_screenBrightness(-1)
  ,m_keyboardBrightness(-1)
  ,m_maximumScreenBrightness(-1)
  ,m_maximumKeyboardBrightness(-1)
{
    if(QDBusConnection::sessionBus().interface()->isServiceRegistered(SOLID_POWERMANAGEMENT_SERVICE))
    {

        if (!QDBusConnection::sessionBus().connect(SOLID_POWERMANAGEMENT_SERVICE,
                                                   QStringLiteral("/org/kde/Solid/PowerManagement/Actions/BrightnessControl"),
                                                   QStringLiteral("org.kde.Solid.PowerManagement.Actions.BrightnessControl"),
                                                   QStringLiteral("brightnessChanged"),
                                                   this,
                                                   SLOT(setScreenBrightness(int)))) {
            qDebug() << "error connecting to Brightness changes via dbus";
        }

        if (!QDBusConnection::sessionBus().connect(SOLID_POWERMANAGEMENT_SERVICE,
                                                   QStringLiteral("/org/kde/Solid/PowerManagement/Actions/BrightnessControl"),
                                                   QStringLiteral("org.kde.Solid.PowerManagement.Actions.BrightnessControl"),
                                                   QStringLiteral("brightnessMaxChanged"),
                                                   this,
                                                   SLOT(setMaximumScreenBrightness(int)))) {
            qDebug() << "error connecting to max brightness changes via dbus";
        }

        if (!QDBusConnection::sessionBus().connect(SOLID_POWERMANAGEMENT_SERVICE,
                                                   QStringLiteral("/org/kde/Solid/PowerManagement/Actions/KeyboardBrightnessControl"),
                                                   QStringLiteral("org.kde.Solid.PowerManagement.Actions.KeyboardBrightnessControl"),
                                                   QStringLiteral("keyboardBrightnessChanged"),
                                                   this,
                                                   SLOT(setKeyboardBrightness(int)))) {
            qDebug() << "error connecting to Keyboard Brightness changes via dbus";
        }

        if (!QDBusConnection::sessionBus().connect(SOLID_POWERMANAGEMENT_SERVICE,
                                                   QStringLiteral("/org/kde/Solid/PowerManagement/Actions/KeyboardBrightnessControl"),
                                                   QStringLiteral("org.kde.Solid.PowerManagement.Actions.KeyboardBrightnessControl"),
                                                   QStringLiteral("keyboardBrightnessMaxChanged"),
                                                   this,
                                                   SLOT(setMaximumKeyboardBrightness(int)))) {
            qDebug() << "error connecting to max keyboard Brightness changes via dbus";
        }

        if (!QDBusConnection::sessionBus().connect(SOLID_POWERMANAGEMENT_SERVICE,
                                                   QStringLiteral("/org/kde/Solid/PowerManagement/Actions/HandleButtonEvents"),
                                                   QStringLiteral("org.kde.Solid.PowerManagement.Actions.HandleButtonEvents"),
                                                   QStringLiteral("triggersLidActionChanged"),
                                                   this,
                                                   SLOT(setTriggersLidAction(bool)))) {
            qDebug() << "error connecting to lid action trigger changes via dbus";
        }
    }

    QDBusMessage screenMsg = QDBusMessage::createMethodCall(SOLID_POWERMANAGEMENT_SERVICE,
                                                            QStringLiteral("/org/kde/Solid/PowerManagement/Actions/BrightnessControl"),
                                                            QStringLiteral("org.kde.Solid.PowerManagement.Actions.BrightnessControl"),
                                                            QStringLiteral("brightness"));

    QDBusPendingReply<int> screenReply = QDBusConnection::sessionBus().asyncCall(screenMsg);
    QDBusPendingCallWatcher *screenWatcher = new QDBusPendingCallWatcher(screenReply, this);
    QObject::connect(screenWatcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<int> reply = *watcher;
        if (!reply.isError()) {
            setScreenBrightness(reply.value());
        }
        watcher->deleteLater();
    });

    QDBusMessage maxScreenMsg = QDBusMessage::createMethodCall(SOLID_POWERMANAGEMENT_SERVICE,
                                                               QStringLiteral("/org/kde/Solid/PowerManagement/Actions/BrightnessControl"),
                                                               QStringLiteral("org.kde.Solid.PowerManagement.Actions.BrightnessControl"),
                                                               QStringLiteral("brightnessMax"));
    QDBusPendingReply<int> maxScreenReply = QDBusConnection::sessionBus().asyncCall(maxScreenMsg);
    QDBusPendingCallWatcher *maxScreenWatcher = new QDBusPendingCallWatcher(maxScreenReply, this);
    QObject::connect(maxScreenWatcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<int> reply = *watcher;
        if (!reply.isError()) {
            setMaximumScreenBrightness(reply.value());
        }else
        {
            qDebug() << "POWER" << reply.error().message();
        }
        watcher->deleteLater();
    });

    QDBusMessage keyboardMsg = QDBusMessage::createMethodCall(SOLID_POWERMANAGEMENT_SERVICE,
                                                              QStringLiteral("/org/kde/Solid/PowerManagement/Actions/KeyboardBrightnessControl"),
                                                              QStringLiteral("org.kde.Solid.PowerManagement.Actions.KeyboardBrightnessControl"),
                                                              QStringLiteral("keyboardBrightness"));
    QDBusPendingReply<int> keyboardReply = QDBusConnection::sessionBus().asyncCall(keyboardMsg);
    QDBusPendingCallWatcher *keyboardWatcher = new QDBusPendingCallWatcher(keyboardReply, this);
    QObject::connect(keyboardWatcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<int> reply = *watcher;
        if (!reply.isError()) {
            setKeyboardBrightness(reply.value());
        }
        watcher->deleteLater();
    });

    QDBusMessage maxKeyboardMsg = QDBusMessage::createMethodCall(SOLID_POWERMANAGEMENT_SERVICE,
                                                                 QStringLiteral("/org/kde/Solid/PowerManagement/Actions/KeyboardBrightnessControl"),
                                                                 QStringLiteral("org.kde.Solid.PowerManagement.Actions.KeyboardBrightnessControl"),
                                                                 QStringLiteral("keyboardBrightnessMax"));
    QDBusPendingReply<int> maxKeyboardReply = QDBusConnection::sessionBus().asyncCall(maxKeyboardMsg);
    QDBusPendingCallWatcher *maxKeyboardWatcher = new QDBusPendingCallWatcher(maxKeyboardReply, this);
    QObject::connect(maxKeyboardWatcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<int> reply = *watcher;
        if (!reply.isError()) {
            setMaximumKeyboardBrightness(reply.value());
        }
        watcher->deleteLater();
    });

    QDBusMessage lidIsPresentMsg = QDBusMessage::createMethodCall(SOLID_POWERMANAGEMENT_SERVICE,
                                                                  QStringLiteral("/org/kde/Solid/PowerManagement"),
                                                                  SOLID_POWERMANAGEMENT_SERVICE,
                                                                  QStringLiteral("isLidPresent"));
    QDBusPendingReply<bool> lidIsPresentReply = QDBusConnection::sessionBus().asyncCall(lidIsPresentMsg);
    QDBusPendingCallWatcher *lidIsPresentWatcher = new QDBusPendingCallWatcher(lidIsPresentReply, this);
    QObject::connect(lidIsPresentWatcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<bool> reply = *watcher;
        if (!reply.isError()) {
            setLidPresent(reply.value());
        }
        watcher->deleteLater();
    });

    QDBusMessage triggersLidActionMsg = QDBusMessage::createMethodCall(SOLID_POWERMANAGEMENT_SERVICE,
                                                                       QStringLiteral("/org/kde/Solid/PowerManagement/Actions/HandleButtonEvents"),
                                                                       QStringLiteral("org.kde.Solid.PowerManagement.Actions.HandleButtonEvents"),
                                                                       QStringLiteral("triggersLidAction"));
    QDBusPendingReply<bool> triggersLidActionReply = QDBusConnection::sessionBus().asyncCall(triggersLidActionMsg);
    QDBusPendingCallWatcher *triggersLidActionWatcher = new QDBusPendingCallWatcher(triggersLidActionReply, this);
    QObject::connect(triggersLidActionWatcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<bool> reply = *watcher;
        if (!reply.isError()) {
            setTriggersLidAction(reply.value());
        }
        watcher->deleteLater();
    });
}

int BrightnessControl::screenBrightness() const
{
    return m_screenBrightness;
}

int BrightnessControl::keyboardBrightness() const
{
    return m_keyboardBrightness;
}

int BrightnessControl::maximumScreenBrightness() const
{
    return m_maximumScreenBrightness;
}

void BrightnessControl::setMaximumScreenBrightness(int value)
{
    if(value == m_maximumScreenBrightness)
    {
        return;
    }

    m_maximumScreenBrightness = value;
    Q_EMIT maximumScreenBrightnessChanged(m_maximumScreenBrightness);

    setScreenBrightnessAvailable(m_maximumScreenBrightness > 0);
}

int BrightnessControl::maximumKeyboardBrightness() const
{
    return m_maximumKeyboardBrightness;
}

void BrightnessControl::setMaximumKeyboardBrightness(int value)
{
    if(value == m_maximumKeyboardBrightness)
    {
        return;
    }

    m_maximumKeyboardBrightness = value;
    Q_EMIT maximumScreenBrightnessChanged(m_maximumKeyboardBrightness);

    setKeyboardBrightnessAvailable(m_maximumKeyboardBrightness > 0);
}

void BrightnessControl::setScreenBrightness(int screenBrightness)
{
    if(screenBrightness == m_screenBrightness)
    {
        return;
    }

    m_screenBrightness = screenBrightness;
    Q_EMIT screenBrightnessChanged(m_screenBrightness);
}

void BrightnessControl::setKeyboardBrightness(int keyboardBrightness)
{
    if (m_keyboardBrightness == keyboardBrightness)
        return;

    m_keyboardBrightness = keyboardBrightness;
    Q_EMIT keyboardBrightnessChanged(m_keyboardBrightness);
}

void BrightnessControl::changeScreenBrightness(int value, bool silent)
{
    QDBusMessage msg = QDBusMessage::createMethodCall(QStringLiteral("org.kde.Solid.PowerManagement"),
                                                      QStringLiteral("/org/kde/Solid/PowerManagement/Actions/BrightnessControl"),
                                                      QStringLiteral("org.kde.Solid.PowerManagement.Actions.BrightnessControl"),
                                                      silent ? QStringLiteral("setBrightnessSilent") : QStringLiteral("setBrightness"));
    msg << value;

    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(QDBusConnection::sessionBus().asyncCall(msg), this);
    QObject::connect(watcher, &QDBusPendingCallWatcher::finished, this, [](QDBusPendingCallWatcher *watcher) {
        watcher->deleteLater();
    });
}

void BrightnessControl::changeKeyboardBrightness(int value, bool silent)
{
    QDBusMessage msg = QDBusMessage::createMethodCall(QStringLiteral("org.kde.Solid.PowerManagement"),
                                                      QStringLiteral("/org/kde/Solid/PowerManagement/Actions/KeyboardBrightnessControl"),
                                                      QStringLiteral("org.kde.Solid.PowerManagement.Actions.KeyboardBrightnessControl"),
                                                      silent ? QStringLiteral("setKeyboardBrightnessSilent") : QStringLiteral("setKeyboardBrightness"));
    msg << value;

    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(QDBusConnection::sessionBus().asyncCall(msg), this);
    QObject::connect(watcher, &QDBusPendingCallWatcher::finished, this, [](QDBusPendingCallWatcher *watcher) {
        watcher->deleteLater();
    });
}

void BrightnessControl::setLidPresent(bool lidPresent)
{
    if (m_lidPresent == lidPresent)
        return;

    m_lidPresent = lidPresent;
    Q_EMIT lidPresentChanged(m_lidPresent);
}

void BrightnessControl::setTriggersLidAction(bool triggersLidAction)
{
    if (m_triggersLidAction == triggersLidAction)
        return;

    m_triggersLidAction = triggersLidAction;
    Q_EMIT triggersLidActionChanged(m_triggersLidAction);
}

bool BrightnessControl::screenBrightnessAvailable() const
{
    return m_screenBrightnessAvailable;
}

void BrightnessControl::setScreenBrightnessAvailable(bool newScreenBrightnessAvailable)
{
    if (m_screenBrightnessAvailable == newScreenBrightnessAvailable)
        return;
    m_screenBrightnessAvailable = newScreenBrightnessAvailable;
    Q_EMIT screenBrightnessAvailableChanged();
}

bool BrightnessControl::keyboardBrightnessAvailable() const
{
    return m_keyboardBrightnessAvailable;
}

void BrightnessControl::setKeyboardBrightnessAvailable(bool newKeyboardBrightnessAvailable)
{
    if (m_keyboardBrightnessAvailable == newKeyboardBrightnessAvailable)
        return;
    m_keyboardBrightnessAvailable = newKeyboardBrightnessAvailable;
    Q_EMIT keyboardBrightnessAvailableChanged();
}

bool BrightnessControl::lidPresent() const
{
    return m_lidPresent;
}

bool BrightnessControl::triggersLidAction() const
{
    return m_triggersLidAction;
}
