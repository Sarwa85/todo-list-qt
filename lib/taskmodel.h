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
        TaskWaitingUpdate
    };

    enum Roles {
        RoleData = Qt::UserRole,
        RoleState,
        RoleUuid
    };

    TaskModel(QObject *parent = nullptr);
    QModelIndex indexFormUuid(const QUuid& uuid);
    QModelIndex indexFromId(int id);

public Q_SLOTS:
    void append(Task task, TaskState state, QUuid uuid = QUuid());
    void updateState(const QUuid& uuid, TaskModel::TaskState state);
    void updateState(Task task, TaskModel::TaskState state);
    void updateTask(const Task& task, const QUuid &uuid);
};

Q_DECLARE_METATYPE(TaskModel::TaskState);

