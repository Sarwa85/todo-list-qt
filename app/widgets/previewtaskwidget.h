#pragma once

#include <QWidget>
#include "task.h"

namespace Ui {
class PreviewTaskWidget;
}

class PreviewTaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewTaskWidget(QWidget *parent = nullptr);
    ~PreviewTaskWidget();
    void setTask(const Task& task);

Q_SIGNALS:
    void needClose();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_closeButton_clicked();

private:
    Ui::PreviewTaskWidget *ui;
};

