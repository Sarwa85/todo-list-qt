#pragma once

#include <QWidget>
#include "task.h"
#include <QStandardItemModel>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

public slots:
    void updateTasks(QList<Task> tasks);

signals:
    void needTasks();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_refreshButton_clicked();

    void on_addButton_clicked();

    void on_backButton_clicked();

private:
    Ui::MainWidget *ui;
    QStandardItemModel m_model;
};

