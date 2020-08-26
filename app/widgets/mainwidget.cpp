#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->listView->setModel(&m_model);
    ui->stackedWidget->setCurrentWidget(ui->listPage);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::updateTasks(QList<Task> tasks)
{
    m_model.clear();
    for (const auto& t : tasks) {
        auto item = new QStandardItem(t.title);
        m_model.appendRow(item);
    }
}

void MainWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWidget::on_refreshButton_clicked()
{
    Q_EMIT needTasks();
}

void MainWidget::on_addButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->editPage);
}

void MainWidget::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->listPage);
}
