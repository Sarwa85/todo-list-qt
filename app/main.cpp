#include "widgets/mainwidget.h"
#include "widgets/mainwindow.h"
#include "controler.h"
#include "filerepository.h"

#include <QApplication>
#include <QThread>
#include <QQuickView>

Q_DECLARE_METATYPE(TaskModel*)

int main(int argc, char *argv[])
{
    qmlRegisterType<Controler>("pl.osla.todo", 1, 0, "Controler");
    qmlRegisterType<FileRepository>("pl.osla.todo", 1, 0, "FileRepository");
    qmlRegisterType<TaskModel>("pl.osla.todo", 1, 0, "TaskModel");
    qmlRegisterSingletonType(QUrl("qml/Style.qml"), "pl.osla.todo", 1, 0, "Style" );

    QApplication a(argc, argv);

    // widgets
//    FileRepository repo;
//    repo.setName("todo-base");
//    TaskModel m_model;
//    Controler controler(&repo, &m_model);
//    MainWidget widget(controler);
//    widget.show();
//    QMetaObject::invokeMethod(&widget, "start", Qt::QueuedConnection);

    // qml
    QQuickView view;
    view.setSource(QUrl("qml/main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();
    view.resize(600, 400);

    return a.exec();
}

