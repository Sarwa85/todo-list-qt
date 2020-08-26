#include "repository.h"

Repository::Repository(const QString &name, QObject *parent)
    : QObject(parent)
    , m_name(name)
{

}

QString Repository::name()
{
    return m_name;
}
