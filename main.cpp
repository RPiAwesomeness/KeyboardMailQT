#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    a.setApplicationDisplayName("KeyboardMail");
    a.setApplicationName("KeyboardMail");
    a.setApplicationVersion("0.0.2");
    a.setOrganizationName("spam");

    w.show();

    return a.exec();
}
