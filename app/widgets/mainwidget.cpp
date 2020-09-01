#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "taskdelegate.h"

#include <QDebug>

MainWidget::MainWidget(Controler& controler, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , m_controler(controler)
    , m_activeTask(Task())
{
    ui->setupUi(this);

    ui->listView->setModel(m_controler.model());
    ui->stackedWidget->setCurrentWidget(ui->listPage);
    ui->listView->setItemDelegate(new TaskDelegate(this));
    ui->addButton->setIcon(QIcon::fromTheme("list-add"));
    ui->removeButton->setIcon(QIcon::fromTheme("list-remove"));
    ui->refreshButton->setIcon(QIcon::fromTheme("view-refresh"));
    ui->editButton->setIcon(QIcon::fromTheme("accessories-text-editor"));
    ui->okButton->setIcon(QIcon::fromTheme("document-save"));
    ui->backButton->setIcon(QIcon::fromTheme("window-close"));

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
    m_activeTask = Task();
    updateActiveTaskUI();
    ui->stackedWidget->setCurrentWidget(ui->editPage);
}

void MainWidget::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->listPage);
}

void MainWidget::on_okButton_clicked()
{
    readActiveTask();
    auto uuid = QUuid::createUuid();
    if (m_activeTask.id >= 0) {
        m_controler.asyncEdit(m_activeTask);
    } else {
        m_controler.asyncAdd(m_activeTask, uuid);
    }

    ui->stackedWidget->setCurrentWidget(ui->listPage);
    updatePreviewTask();
    updateUI(ui->listView->currentIndex());
}

void MainWidget::on_removeButton_clicked()
{
    m_controler.asyncRemove(currentTask());
}

void MainWidget::on_editButton_clicked()
{
    m_activeTask = currentTask();
    updateActiveTaskUI();
    ui->stackedWidget->setCurrentWidget(ui->editPage);
}

void MainWidget::updateActiveTaskUI()
{
    ui->editGroupBox->setTitle(m_activeTask.id > 0 ? tr("Edycja zadania") : tr("Nowe zadanie"));
    ui->titleLineEdit->setText(m_activeTask.title);
    ui->descTextEdit->setPlainText(m_activeTask.text);
    ui->dateEdit->setDate(m_activeTask.dateTime.date());
    ui->timeEdit->setTime(m_activeTask.dateTime.time());
}

void MainWidget::updatePreviewTask()
{
    ui->pagePreviewWidget->setTask(currentTask());
}

Task MainWidget::currentTask() const
{
    if (!ui->listView->currentIndex().isValid())
        return Task();
    return ui->listView->currentIndex().data(TaskModel::RoleData).value<Task>();
}

void MainWidget::readActiveTask()
{
    m_activeTask.title = ui->titleLineEdit->text();
    m_activeTask.text = ui->descTextEdit->toPlainText();
    if (ui->alarmCheckBox->isChecked())
        m_activeTask.dateTime = QDateTime(ui->dateEdit->date(), ui->timeEdit->time());
    else
        m_activeTask.dateTime = QDateTime();
}

void MainWidget::on_listView_doubleClicked(const QModelIndex &index)
{
    if (index.isValid())
        on_editButton_clicked();
}
