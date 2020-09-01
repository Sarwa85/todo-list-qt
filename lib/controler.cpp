#include "controler.h"

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(controler)
Q_LOGGING_CATEGORY(controler, "controler")

Controler::Controler(Repository &repository, TaskModel &model, QObject *parent)
    : QObject(parent)
    , m_repository(repository)
    , m_model(model)
{
    connect(&m_repository, &Repository::removed, this, &Controler::processRemovedTask, Qt::QueuedConnection);
    connect(&m_repository, &Repository::removeError, this, &Controler::processRemoveError, Qt::QueuedConnection);
    connect(&m_repository, &Repository::saveError, this, &Controler::processSaveError, Qt::QueuedConnection);
    connect(&m_repository, &Repository::saved, this, &Controler::processSavedTask, Qt::QueuedConnection);
    connect(&m_repository, &Repository::tasks, this, &Controler::processTasks, Qt::QueuedConnection);
    connect(&m_repository, &Repository::edited, this, &Controler::processEdited, Qt::QueuedConnection);

    connect(this, &Controler::needAdd, &m_repository, &Repository::add, Qt::QueuedConnection);
    connect(this, &Controler::needReadAll, &m_repository, &Repository::readAll, Qt::QueuedConnection);
    connect(this, &Controler::needRemove, &m_repository, &Repository::remove, Qt::QueuedConnection);
    connect(this, &Controler::needEdit, &m_repository, &Repository::edit, Qt::QueuedConnection);

    m_thread = new QThread();
    connect(m_thread, &QThread::started, m_thread, [=](){
        asyncTasks();
    });
}

void Controler::asyncTasks()
{
    qCDebug(controler) << "Pobieranie zadań";
    Q_EMIT needReadAll();
}

void Controler::asyncAdd(Task task, QUuid uuid)
{
    qCDebug(controler) << "Zapisywanie zadań";
    m_model.append(task, TaskModel::TaskWaitingAdd, uuid);
    Q_EMIT needAdd(task, uuid);
}

void Controler::asyncRemove(Task task)
{
    qCDebug(controler) << "Usuwanie zadania";
    m_model.updateState(task, TaskModel::TaskWaitingRemove);
    Q_EMIT needRemove(task);
}

void Controler::asyncEdit(Task task)
{
    qCDebug(controler) << "Edycja zadania";
    m_model.updateTask(task, TaskModel::TaskWaitingEdit);
    Q_EMIT needEdit(task);
}

void Controler::start()
{
    m_repository.moveToThread(m_thread);
    m_thread->start();
}

TaskModel *Controler::model()
{
    return &m_model;
}

void Controler::processSavedTask(const Task &task, const QUuid &uuid)
{
    qCDebug(controler) << "Przetwarzanie zapisanego zadania" << uuid;
    m_model.updateTask(task, uuid);
}

void Controler::processTasks(const QList<Task> &tasks)
{
    qCDebug(controler) << "Przetwarzanie zadań";
    m_model.clear();
    for (const auto& t : tasks)
        m_model.append(t, TaskModel::TaskReady);
}

void Controler::processSaveError(const QString &error, const QUuid &uuid)
{
    qCDebug(controler) << "Błąd zapisu" << error;
}

void Controler::processRemovedTask(const Task &task)
{
    qCDebug(controler) << "Przetwarzania usuniętego zadania";
    auto index = m_model.indexFromId(task.id);
    if (!index.isValid())
        return;
    m_model.removeRow(index.row());
}

void Controler::processRemoveError(const QString &error)
{
    qCDebug(controler) << "Przetwarzanie błędu usunięcia zadania";
}

void Controler::processEdited(Task task)
{
    qCDebug(controler) << "Przetwarzanie zapisanego zadania";
    m_model.updateTask(task, TaskModel::TaskReady);
}
