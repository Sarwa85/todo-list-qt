#pragma once

#include <QDateTime>

class Task
{
public:
    explicit Task();
    explicit Task(const QString& title, const QString& text, const QDateTime& dateTime);
    int id;
    QDateTime alertDateTime;
    QString title;
    QString text;
    QDateTime modDateTime;
};

