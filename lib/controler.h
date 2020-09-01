#pragma once

#include "lib_global.h"
#include "repository.h"
#include "taskmodel.h"

#include <QObject>
#include <QThread>

class Controler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TaskModel* model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(Repository* repository READ repository WRITE setRepository NOTIFY repositoryChanged)

public:
    explicit Controler(QObject* parent = 0);
    Controler(Repository* m_repository, TaskModel* model, QObject* parent = 0);

    Repository* repository() const;
    TaskModel* model();

public Q_SLOTS:
    void asyncTasks();
    void asyncAdd(Task task, QUuid uuid = QUuid());
    void asyncRemove(Task task);
    void asyncRemoveRow(int row);
    void asyncEdit(Task task);
    void start();
    void init();
    void setModel(TaskModel* model);
    void setRepository(Repository* repository);

Q_SIGNALS:
    void needAdd(Task task, QUuid uuid);
    void needReadAll();
    void needRemove(Task task);
    void needEdit(Task task);
    void modelChanged(TaskModel* model);
    void repositoryChanged(Repository* repository);

private Q_SLOTS:
    void processSavedTask(const Task& task, const QUuid& uuid);
    void processTasks(const QList<Task> &tasks);
    void processSaveError(const QString& error, const QUuid& uuid);
    void processRemovedTask(const Task& task);
    void processRemoveError(const QString& error);
    void processEdited(Task task);

private:
    QThread* m_thread;
    TaskModel* m_model;
    Repository* m_repository;
};
