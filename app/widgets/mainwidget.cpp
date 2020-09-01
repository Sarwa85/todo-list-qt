#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "taskdelegate.h"

#include <QDebug>

MainWidget::MainWidget(Controler& controler, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , m_controler(controler)
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

    connect(ui->listView, &QListView::clicked, this, [&](const QModelIndex& index){
        if (!index.isValid())
            return;
        auto task = index.data(TaskModel::RoleData).value<Task>();
        ui->pagePreviewWidget->setTask(task);
    });
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
    ui->stackedWidget->setCurrentWidget(ui->editPage);
}

void MainWidget::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->listPage);
}

void MainWidget::on_okButton_clicked()
{
    Task t;
    t.title = ui->titleLineEdit->text();
    t.text = ui->descTextEdit->toPlainText();
    if (ui->alarmCheckBox->isChecked())
        t.alertDateTime = QDateTime(ui->dateEdit->date(), ui->timeEdit->time());
    else
        t.alertDateTime = QDateTime();
    auto uuid = QUuid::createUuid();


    //    Q_EMIT needSave(t, uuid);
    m_controler.asyncAdd(t, uuid);
    ui->stackedWidget->setCurrentWidget(ui->listPage);
}

void MainWidget::setActive(bool active)
{
    setEnabled(active);
}

void MainWidget::on_removeButton_clicked()
{
    /// @todo obsłużyć listę zadań do usunięcia
    if (!ui->listView->currentIndex().isValid())
        return;
    auto t = ui->listView->currentIndex().data(TaskModel::RoleData).value<Task>();
    m_controler.asyncRemove(t);
}
