#pragma once

#include "task.h"
#include "controler.h"

#include <QWidget>
#include <QUuid>
#include <QQueue>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(Controler& controler, QWidget *parent = nullptr);
    ~MainWidget();

public slots:
    void start();
    void updateUI(const QModelIndex& currentIndex);

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_refreshButton_clicked();
    void on_addButton_clicked();
    void on_backButton_clicked();
    void on_okButton_clicked();
    void on_removeButton_clicked();

private:
    Ui::MainWidget *ui;
    QQueue<QUuid> m_queue;
    Controler& m_controler;

    void setActive(bool active);
};


