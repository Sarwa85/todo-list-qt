#include "filerepository.h"
#include <QFile>

FileRepository::FileRepository(const QString &name, QObject *parent)
    : Repository(name, parent)
{

}

bool FileRepository::save(Task task)
{
    if (!isValid(task))
        return false;

    auto tasks = readAll();
    if (task.id >= 0) {
        // find and delete old task
        for (int a = 0 ; a < tasks.count() ; ++a) {
            if (tasks[a].id == task.id) {
                tasks.removeAt(a);
                break;
            }
        }
    } else {
        // gen id
        if (tasks.isEmpty())
            task.id = 0;
        else
            task.id = tasks.last().id + 1;
    }
    tasks << task;
    return write(tasks);
}

QList<Task> FileRepository::readAll()
{
    QFile repo_file(m_name);
    if (!repo_file.open(QFile::ReadOnly))
        return QList<Task>();
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

bool FileRepository::isValid(const Task &task)
{
    return !task.title.isEmpty()
            && !task.text.isEmpty();
}

bool FileRepository::write(const QList<Task> &tasks)
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
