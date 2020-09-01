#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "taskdelegate.h"

#include <QDebug>

MainWidget::MainWidget(Controler& controler, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , m_controler(controler)
    , m_currentTask(Task())
{
    ui->setupUi(this);

    ui->listView->setModel(m_controler.model());
    ui->stackedWidget->setCurrentWidget(ui->listPage);
    ui->listView->setItemDelegate(new TaskDelegate(this));
    ui->addButton->setIcon(QIcon::fromTheme("list-add"));
    ui->removeButton->setIcon(QIcon::fromTheme("list-remove"));
    ui->refreshButton->setIcon(QIcon::fromTheme("view-refresh"));
    ui->editButton->setIcon(QIcon::fromTheme("accessories-text-editor"));

    connect(ui->listView, &QListView::clicked, this, &MainWidget::updateUI);
    updateUI(QModelIndex());
    connect(ui->pagePreviewWidget, &PreviewTaskWidget::needClose, this, [&](){
        ui->detailsBox->hide();
    });

    connect(ui->listView, &QListView::clicked, this, &MainWidget::updatePreviewTask);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::start()
{
    m_controler.start();
}

void MainWidget::updateUI(const QModelIndex& currentIndex)
{
    bool selected = currentIndex.isValid();
    ui->detailsBox->setVisible(selected);
    ui->editButton->setEnabled(selected);
    ui->removeButton->setEnabled(selected);
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
    m_controler.asyncTasks();
}

void MainWidget::on_addButton_clicked()
{
    m_currentTask = Task();
    updateCurrentTaskUI();
    ui->stackedWidget->setCurrentWidget(ui->editPage);
}

void MainWidget::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->listPage);
}

void MainWidget::on_okButton_clicked()
{
    m_currentTask.title = ui->titleLineEdit->text();
    m_currentTask.text = ui->descTextEdit->toPlainText();
    if (ui->alarmCheckBox->isChecked())
        m_currentTask.alertDateTime = QDateTime(ui->dateEdit->date(), ui->timeEdit->time());
    else
        m_currentTask.alertDateTime = QDateTime();
    auto uuid = QUuid::createUuid();
    if (m_currentTask.id >= 0) {
        m_controler.asyncEdit(m_currentTask);
    } else {
        m_controler.asyncAdd(m_currentTask, uuid);
    }

    ui->stackedWidget->setCurrentWidget(ui->listPage);
    updatePreviewTask();
    updateUI(ui->listView->currentIndex());
}

void MainWidget::on_removeButton_clicked()
{
    /// @todo obsłużyć listę zadań do usunięcia
    if (!ui->listView->currentIndex().isValid())
        return;
    auto t = ui->listView->currentIndex().data(TaskModel::RoleData).value<Task>();
    m_controler.asyncRemove(t);
}

void MainWidget::on_editButton_clicked()
{
    if (!ui->listView->currentIndex().isValid())
        return;
    m_currentTask = ui->listView->currentIndex().data(TaskModel::RoleData).value<Task>();
    updateCurrentTaskUI();
    ui->stackedWidget->setCurrentWidget(ui->editPage);
}

void MainWidget::updateCurrentTaskUI()
{
    ui->titleLineEdit->setText(m_currentTask.title);
    ui->descTextEdit->setPlainText(m_currentTask.text);
    ui->dateEdit->setDate(m_currentTask.alertDateTime.date());
    ui->timeEdit->setTime(m_currentTask.alertDateTime.time());
}

void MainWidget::updatePreviewTask()
{
    if (!ui->listView->currentIndex().isValid())
        return;
    auto task = ui->listView->currentIndex().data(TaskModel::RoleData).value<Task>();
    ui->pagePreviewWidget->setTask(task);
}
