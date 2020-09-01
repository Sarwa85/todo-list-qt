#pragma once

#include "repository.h"
#include <QObject>
#include <QDataStream>

class FileRepository : public Repository
{
    Q_OBJECT
public:
    FileRepository(const QString& name, QObject* parent = 0);

    void add(Task task, QUuid uuid = QUuid()) override;
    void readAll() override;
    void remove(Task task) override;
    void edit(Task task) override;

private:
    QList<Task> readFromFile();
    bool isValid(Task task);
    bool write(QList<Task> tasks);
    QList<Task> m_model;
    static int taskIndex(const Task& task, const QList<Task>& taskList);
};

QDataStream &operator<<(QDataStream &stream, const Task &);
QDataStream &operator>>(QDataStream &stream, Task &);

