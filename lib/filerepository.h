#pragma once

#include "repository.h"
#include <QObject>
#include <QDataStream>

class FileRepository : public Repository
{
    Q_OBJECT
public:
    FileRepository(const QString& name, QObject* parent = 0);

    // Repository interface
public:
    bool save(Task task);
    QList<Task> readAll();

private:
    bool isValid(const Task& task);
    bool write(const QList<Task>& tasks);
};

QDataStream &operator<<(QDataStream &stream, const Task &);
QDataStream &operator>>(QDataStream &stream, Task &);

