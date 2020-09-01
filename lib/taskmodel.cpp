#include "taskmodel.h"

#include <QDebug>

TaskModel::TaskModel(QObject *parent)
    : QStandardItemModel(parent)
{

}

QModelIndex TaskModel::indexFormUuid(const QUuid &uuid)
{
    for (int a = 0; a < rowCount(); ++a) {
        auto i = index(a, 0);
        auto item_uuid = i.data(RoleUuid).value<QUuid>();
        if (item_uuid == uuid)
            return i;
    }
    qWarning() << "Nie znaleziono indeksu";
    return QModelIndex();
}

QModelIndex TaskModel::indexFromId(int id)
{
    for (int a = 0; a < rowCount(); ++a) {
        auto i = index(a, 0);
        auto item_data = i.data(RoleData).value<Task>();
        if (item_data.id == id)
            return i;
    }
    qWarning() << "Nie znaleziono indeksu";
    return QModelIndex();
}

void TaskModel::append(Task task, TaskState state, QUuid uuid)
{
    auto item = new QStandardItem(task.title);
    item->setData(QVariant::fromValue<Task>(task), RoleData);
    item->setData(QVariant::fromValue<TaskState>(state), RoleState);
    item->setData(QVariant::fromValue<QUuid>(uuid), RoleUuid);
    appendRow(item);
}

void TaskModel::updateState(const QUuid &uuid, TaskModel::TaskState state)
{
    auto index = indexFormUuid(uuid);
    if (index.isValid())
        setData(index, QVariant::fromValue<TaskState>(state), RoleState);
}

void TaskModel::updateState(Task task, TaskModel::TaskState state)
{
    auto index = indexFromId(task.id);
    if (index.isValid())
        setData(index, QVariant::fromValue<TaskState>(state), RoleState);
}

void TaskModel::updateTask(const Task &task, const QUuid& uuid)
{
    auto index = indexFormUuid(uuid);
    if (!index.isValid())
        return;
    setData(index, QVariant::fromValue<Task>(task), RoleData);
    setData(index, QVariant::fromValue<TaskState>(TaskReady), RoleState);
    setData(index, QVariant::fromValue<QUuid>(QUuid()), RoleUuid);
}


