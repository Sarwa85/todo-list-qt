#include "controler.h"

Controler::Controler(Repository &repository, QObject *parent)
    : QObject(parent)
    , m_repository(repository)
{
}

QList<Task> Controler::tasks()
{
    return m_repository.readAll();
}
