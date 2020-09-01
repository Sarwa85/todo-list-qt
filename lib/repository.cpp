#include "repository.h"

Repository::Repository(QObject *parent)
    : QObject(parent)
{

}

QString Repository::name()
{
    return m_name;
}

void Repository::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    Q_EMIT nameChanged(m_name);
}
