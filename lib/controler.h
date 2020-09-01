#pragma once

#include "lib_global.h"
#include "repository.h"
#include "taskmodel.h"

#include <QObject>
#include <QThread>

class Controler : public QObject
{
    Q_OBJECT
public:
    Controler(Repository& m_repository, TaskModel& model, QObject* parent = 0);
    void asyncTasks();
    void asyncAdd(Task task, QUuid uuid = QUuid());
    void asyncRemove(Task task);
    void start();
    TaskModel* model();

public Q_SLOTS:
    void processSavedTask(const Task& task, const QUuid& uuid);
    void processTasks(const QList<Task> &tasks);
    void processSaveError(const QString& error, const QUuid& uuid);
    void processRemovedTask(const Task& task);
    void processRemoveError(const QString& error);

Q_SIGNALS:
//    void saved(const Task& task, const QUuid& uuid);
//    void removed(const Task& task);
//    void saveError(const QString& errorText, const QUuid& uuid);
//    void removeError(const QString& text);
//    void tasks(const QList<Task>& list);

    void needAdd(Task task, QUuid uuid);
    void needReadAll();
    void needRemove(Task task);

private:
    Repository& m_repository;
    TaskModel& m_model;
    QThread* m_thread;
};
