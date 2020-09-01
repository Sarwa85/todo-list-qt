#include "taskmodel.h"

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(modelTask)
Q_LOGGING_CATEGORY(modelTask, "model.task")

TaskModel::TaskModel(QObject *parent)
    : QStandardItemModel(parent)
{
    m_roles.insert(RoleData, "roleData");
    m_roles.insert(RoleState, "roleState");
    m_roles.insert(RoleUuid, "roleUuid");
    m_roles.insert(RoleTitle, "roleTitle");
    m_roles.insert(RoleText, "roleText");
}

QModelIndex TaskModel::indexFormUuid(const QUuid &uuid)
{
    for (int a = 0; a < rowCount(); ++a) {
        auto i = index(a, 0);
        auto item_uuid = i.data(RoleUuid).value<QUuid>();
        if (item_uuid == uuid)
            return i;
    }
    qCWarning(modelTask) << "Nie znaleziono indeksu";
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
    qCWarning(modelTask) << "Nie znaleziono indeksu";
    return QModelIndex();
}

QHash<int, QByteArray> TaskModel::roleNames() const
{
    return m_roles;
}

void TaskModel::append(Task task, TaskState state, QUuid uuid)
{
    auto item = new QStandardItem(task.title);
    item->setData(task.title, RoleTitle);
    item->setData(task.text, RoleText);
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
    setData(index, task.title, RoleTitle);
    setData(index, task.text, RoleText);
    setData(index, QVariant::fromValue<Task>(task), RoleData);
    setData(index, QVariant::fromValue<TaskState>(TaskReady), RoleState);
    setData(index, QVariant::fromValue<QUuid>(QUuid()), RoleUuid);
}

void TaskModel::updateTask(const Task &task, TaskState state)
{
    auto index = indexFromId(task.id);
    if (!index.isValid()) {
        qCWarning(modelTask) << "Nie znaleziono zadania";
        return;
    }

    setData(index, task.title, RoleTitle);
    setData(index, task.text, RoleText);
    setData(index, QVariant::fromValue<Task>(task), RoleData);
    setData(index, QVariant::fromValue<QUuid>(QUuid()), RoleUuid);
    setData(index, QVariant::fromValue<TaskState>(state), RoleState);
}

QModelIndex TaskModel::indexFromRow(int row) const
{
    return index(row, 0);
}


