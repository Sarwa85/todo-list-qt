#pragma once

#include "repository.h"
#include <QObject>
#include <QDataStream>

class FileRepository : public Repository
{
    Q_OBJECT
public:
    FileRepository(const QString& name, QObject* parent = 0);

    void add(Task task, QUuid uuid = QUuid());
    void readAll();
    void remove(Task task);

private:
    QList<Task> readFromFile();
    bool isValid(Task task);
    bool write(QList<Task> tasks);
    QList<Task> m_model;
};

QDataStream &operator<<(QDataStream &stream, const Task &);
QDataStream &operator>>(QDataStream &stream, Task &);

