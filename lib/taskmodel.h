#pragma once

#include <QStandardItemModel>
#include "task.h"
#include <QUuid>

class TaskModel : public QStandardItemModel
{
public:
    enum TaskState {
        TaskReady,
        TaskWaitingRemove,
        TaskWaitingAdd,
        TaskWaitingEdit
    };

    enum Roles {
        RoleTitle = Qt::UserRole,
        RoleText,
        RoleData,
        RoleState,
        RoleUuid
    };

    TaskModel(QObject *parent = nullptr);
    QModelIndex indexFormUuid(const QUuid& uuid);
    QModelIndex indexFromId(int id);
    QHash<int, QByteArray> roleNames() const;

public Q_SLOTS:
    void append(Task task, TaskState state, QUuid uuid = QUuid());
    void updateState(const QUuid& uuid, TaskModel::TaskState state);
    void updateState(Task task, TaskModel::TaskState state);
    void updateTask(const Task& task, const QUuid &uuid);
    void updateTask(const Task& task, TaskState state);
    QModelIndex indexFromRow(int row) const;

private:
    QHash<int, QByteArray> m_roles;
};

Q_DECLARE_METATYPE(TaskModel::TaskState);

