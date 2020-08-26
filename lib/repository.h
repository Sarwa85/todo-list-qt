#pragma once

#include <QObject>
#include "task.h"

class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository(const QString& name, QObject *parent = nullptr);
    QString name();

    virtual bool save(Task task) = 0;
    virtual QList<Task> readAll() = 0;

protected:
    QString m_name;
};
