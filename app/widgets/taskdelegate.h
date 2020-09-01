#pragma once

#include <QStyledItemDelegate>

class TaskDelegate : public QStyledItemDelegate
{
public:
    TaskDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    int m_text_flags;
};

