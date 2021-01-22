// QtUIXmlCleaner.cpp : Defines the entry point for the application.
//

#include <QApplication>
#include "MainWindow.h"

using namespace std;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Pioneer Library System");
    QCoreApplication::setOrganizationDomain("pioneerlibrarysystem.org");
    QCoreApplication::setApplicationName("Qt UI XML Cleaner (Overkill Edition)");

    MainWindow window;
    window.show();

    return app.exec();
}
