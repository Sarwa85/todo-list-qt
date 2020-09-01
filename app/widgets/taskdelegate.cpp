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
    QIcon icon;
    painter->setPen(QPen(QColor("transparent")));
    switch (state) {
    case TaskModel::TaskWaitingAdd: {
        brush = QBrush(QColor("#73CB79"));
        icon = QIcon::fromTheme("list-add");
        break;
    }
    case TaskModel::TaskWaitingRemove: {
        brush = QBrush(QColor("#CB7373"));
        icon = QIcon::fromTheme("list-remove");
        break;
    }
    case TaskModel::TaskWaitingEdit: {
        brush = QBrush(QColor("#73B6CB"));
        icon = QIcon::fromTheme("accessories-text-editor");
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

    int icon_h = option.rect.height() * 0.8;
    if (!icon.isNull()) {
        int y = option.rect.y() + (option.rect.height() - icon_h) / 2;
        QRect rect(option.rect.x() + option.rect.width() - icon_h, y, icon_h, icon_h);
        icon.paint(painter, rect);
    }

    int h_space = option.rect.width() - (icon.isNull() ? 0 : icon_h);
    painter->drawText(QRect(option.rect.x(), option.rect.y(), h_space, option.rect.height()), m_text_flags, task.title);
}
