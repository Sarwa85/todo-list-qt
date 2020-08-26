#include <QApplication>
#include "widgets/mainwidget.h"
#include "controler.h"
#include "filerepository.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget widget;

    FileRepository repo("todo-base");
    Controler controler(repo);

    QObject::connect(&widget, &MainWidget::needTasks, &widget, [&](){
        widget.updateTasks(controler.tasks());
    });

    widget.show();
    return a.exec();
}
