#include "previewtaskwidget.h"
#include "ui_previewtaskwidget.h"

PreviewTaskWidget::PreviewTaskWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewTaskWidget)
{
    ui->setupUi(this);
    ui->closeButton->setIcon(QIcon::fromTheme("window-close"));
}

PreviewTaskWidget::~PreviewTaskWidget()
{
    delete ui;
}

void PreviewTaskWidget::setTask(const Task& task)
{
    if (task.id < 0)
        return;

    ui->titleLabel->setText(task.title);
    ui->descLabel->setText(task.text);
    ui->alarmLabel->setText(task.dateTime.toString("yyyy-MM-dd hh:mm:ss"));
    ui->idLabel->setText(QString::number(task.id));
}

void PreviewTaskWidget::changeEvent(QEvent *e)
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

void PreviewTaskWidget::on_closeButton_clicked()
{
    Q_EMIT needClose();
}
