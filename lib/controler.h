#pragma once

#include "lib_global.h"
#include <QObject>

class Controler : public QObject
{
    Q_OBJECT

public:
    Controler(QObject* parent);
};
