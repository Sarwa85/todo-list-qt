#include "widgets/mainwidget.h"
#include "widgets/mainwindow.h"
#include "controler.h"
#include "filerepository.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FileRepository repo("todo-base");
    TaskModel m_model;

    Controler controler(repo, m_model);

    MainWidget widget(controler);
    widget.show();

    QMetaObject::invokeMethod(&widget, "start", Qt::QueuedConnection);

//    MainWindow mw;
//    mw.show();
    return a.exec();
}

