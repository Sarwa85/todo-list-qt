#include "filerepository.h"
#include <QFile>
#include <QThread>
#include <QDebug>

FileRepository::FileRepository(const QString &name, QObject *parent)
    : Repository(name, parent)
{

}

void FileRepository::add(Task task, QUuid uuid)
{
    QThread::sleep(2);
    if (!isValid(task)) {
        Q_EMIT saveError("Niepoprawne zadanie", uuid);
        return;
    }
    Task outTask = task;
    if (task.id >= 0) {
        // find and delete old task
        for (int a = 0 ; a < m_model.count() ; ++a) {
            if (m_model[a].id == task.id) {
                m_model.removeAt(a);
                break;
            }
        }
    } else {
        // gen id
        if (m_model.isEmpty())
            outTask.id = 0;
        else
            outTask.id = m_model.last().id + 1;
    }
    m_model << outTask;
    if (write(m_model)) {
        Q_EMIT saved(outTask, uuid);
    } else {
        Q_EMIT saveError("Zapis nieudany", uuid);
    }
}

QList<Task> FileRepository::readFromFile()
{
    QFile repo_file(m_name);
    if (!repo_file.open(QFile::ReadOnly)) {
        return QList<Task>();
    }
    QDataStream stream(&repo_file);
    QList<Task> task_list;
    while (!stream.atEnd()) {
        Task t;
        stream >> t;
        task_list << t;
    }
    repo_file.close();
    return task_list;
}

void FileRepository::readAll()
{
    QThread::sleep(2);
    m_model = readFromFile();
    Q_EMIT tasks(m_model);
}

void FileRepository::remove(Task task)
{
    QThread::sleep(2);
    for (int a = m_model.count() - 1; a >= 0; --a) {
        if (m_model[a].id == task.id) {
            auto t = m_model.takeAt(a);
            qWarning() << "Usuwam" << t.title;
            if (write(m_model)) {
                Q_EMIT removed(t);
            } else {
                Q_EMIT removeError("Zapis nieudany");
            }
            return;
        }
    }
    Q_EMIT removeError("Nie znaloziono zadania");
}

bool FileRepository::isValid(Task task)
{
    return !task.title.isEmpty()
            && !task.text.isEmpty();
}

bool FileRepository::write(QList<Task> tasks)
{
    QFile repo_file(m_name);
    if (!repo_file.open(QFile::WriteOnly))
        return false;
    QDataStream stream(&repo_file);
    for (const auto& t : qAsConst(tasks))
        stream << t;
    repo_file.close();
    return true;
}

QDataStream &operator<<(QDataStream &stream, const Task& task)
{
    stream << task.id
           << task.title
           << task.text
           << task.alertDateTime
           << task.modDateTime;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, Task &task)
{
    stream >> task.id
            >> task.title
            >> task.text
            >> task.alertDateTime
            >> task.modDateTime;
    return stream;
}
