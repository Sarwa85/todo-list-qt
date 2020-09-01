#include "taskdelegate.h"
#include "taskmodel.h"

#include <QPainter>


TaskDelegate::TaskDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
    , m_text_flags(Qt::AlignLeft | Qt::AlignVCenter)
{

}

void TaskDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto task = index.data(TaskModel::RoleData).value<Task>();
    auto state = index.data(TaskModel::RoleState).value<TaskModel::TaskState>();
    painter->save();
    QBrush brush;
    painter->setPen(QPen(QColor("transparent")));
    switch (state) {
    case TaskModel::TaskWaitingAdd: {
        brush = QBrush(QColor("#73CB79"));
        break;
    }
    case TaskModel::TaskWaitingRemove: {
        brush = QBrush(QColor("#CB7373"));
        break;
    }
    case TaskModel::TaskWaitingEdit: {
        brush = QBrush(QColor("#73B6CB"));
        break;
    }
    default: {
        break;
    }
    }
    painter->setBrush(brush);
    painter->drawRect(option.rect);
    painter->restore();

    if (option.state & QStyle::State_Selected)
          painter->fillRect(option.rect, option.palette.highlight());

    painter->drawText(option.rect, m_text_flags, task.title);
}
