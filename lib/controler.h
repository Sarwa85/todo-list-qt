#pragma once

#include "lib_global.h"
#include <QObject>
#include "repository.h"

class Controler : public QObject
{
    Q_OBJECT

public:
    Controler(Repository& m_repository, QObject* parent = 0);
    QList<Task> tasks();

private:
    Repository& m_repository;
};
