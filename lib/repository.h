#pragma once

#include "task.h"

#include <QObject>
#include <QUuid>

class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository(const QString& name, QObject *parent = nullptr);
    QString name();

    virtual void add(Task task, QUuid uuid = QUuid()) = 0;
    virtual void readAll() = 0;
    virtual void remove(Task task) = 0;

Q_SIGNALS:
    void saved(const Task& task, const QUuid& uuid);
    void removed(const Task& task);
    void saveError(const QString& errorText, const QUuid& uuid);
    void removeError(const QString& errorText);
    void tasks(const QList<Task>& list);

protected:
    QString m_name;
};
