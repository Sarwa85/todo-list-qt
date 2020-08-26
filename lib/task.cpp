#include "task.h"

Task::Task()
    : id(-1)
{

}

Task::Task(const QString &title, const QString &text, const QDateTime &dateTime)
    : id(-1)
    , title(title)
    , text(text)
    , modDateTime(dateTime)
{

}
