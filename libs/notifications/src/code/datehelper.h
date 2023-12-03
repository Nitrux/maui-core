#pragma once

#include <QObject>

class DateHelper : public QObject
{
    Q_OBJECT

public:
    explicit DateHelper(QObject *parent = nullptr);

    Q_INVOKABLE static QString friendlyTime(const QDateTime &time);
};
