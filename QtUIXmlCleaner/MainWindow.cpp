#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(std::make_unique<Ui::MainWindow>())
{
	ui->setupUi(this);

	QMetaObject::connectSlotsByName(this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_browseInputFileButton_clicked()
{
	auto filename = QFileDialog::getOpenFileName(this, "Select Qt UI file to clean");
}

void MainWindow::on_browseOutputFileButton_clicked()
{
	auto filename = QFileDialog::getOpenFileName(this, "Save new file as...");
}

void MainWindow::on_runButton_clicked()
{

}

void MainWindow::on_closeButton_clicked()
{

}