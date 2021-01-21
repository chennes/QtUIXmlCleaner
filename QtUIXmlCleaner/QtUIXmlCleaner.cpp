// QtUIXmlCleaner.cpp : Defines the entry point for the application.
//

#include "QtUIXmlCleaner.h"
#include "boost/property_tree/ptree.hpp"

#include <QApplication>
#include "MainWindow.h"

using namespace std;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}
