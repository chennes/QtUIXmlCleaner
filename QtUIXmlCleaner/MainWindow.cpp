// MIT License
//
// Copyright(c) 2021 Chris Hennes <chennes@pioneerlibrarysystem.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Cleaner.h"
#include <version.h>

#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>
#include <QScreen>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

#include <iostream>

#if __cplusplus >= 202000L
#include <format>
#else
#include <sstream>
#endif

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(std::make_unique<Ui::MainWindow>())
{
	ui->setupUi(this);
	setWindowIcon(QIcon("ui_icon.svg"));
	
#if __cplusplus >= 202000L
	std::string version = std::format("v{}.{}.{}", QtUIXmlCleaner_VERSION_MAJOR, QtUIXmlCleaner_VERSION_MINOR, QtUIXmlCleaner_VERSION_PATCH);
#else
	std::ostringstream s;
	s << "v" << QtUIXmlCleaner_VERSION_MAJOR << "." << QtUIXmlCleaner_VERSION_MINOR << "." << QtUIXmlCleaner_VERSION_PATCH;
	std::string version = s.str();
#endif
	ui->versionLabel->setText(QString::fromStdString(version));

	QSettings settings;

	settings.beginGroup("Options");
	ui->inputFileLineEdit->setText(settings.value("inputFile", QDir::homePath()+"/NewUIFile.ui").toString());
	ui->outputFileLineEdit->setText(settings.value("outputFile", "").toString());
	ui->sortQGridLayoutCheckbox->setChecked(settings.value("sortQGridLayoutChildren", true).toBool());
	ui->removeNativeTrueCheckbox->setChecked(settings.value("removeNativeTrue", true).toBool());
	ui->removeStdsetZeroCheckbox->setChecked(settings.value("removeStdsetZero", false).toBool());
	settings.endGroup();

	// Calculate a default position:
	QSize defaultSize(597, 209);
	auto screenSize = qApp->primaryScreen()->size();
	QPoint upperLeft(screenSize.width() / 2 - defaultSize.width() / 2, screenSize.height() / 2 - defaultSize.height() / 2);

	settings.beginGroup("MainWindow");
	resize(settings.value("size", defaultSize).toSize());
	move(settings.value("pos", upperLeft).toPoint());
	settings.endGroup();
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_browseInputFileButton_clicked()
{
	auto filename = QFileDialog::getOpenFileName(this, "Select Qt UI file to clean", ui->inputFileLineEdit->text(),"Qt UI Files (*.ui)");
	if (!filename.isEmpty()) {
		ui->inputFileLineEdit->setText(filename);
		ui->outputFileLineEdit->setText(filename + ".cleaned"); // Update the output filename automatically
	}
}

void MainWindow::on_browseOutputFileButton_clicked()
{
	auto filename = QFileDialog::getSaveFileName(this, "Save new file as...", ui->outputFileLineEdit->text());
	if (!filename.isEmpty())
		ui->outputFileLineEdit->setText(filename);
}

void MainWindow::on_runButton_clicked()
{
	ui->runButton->setDisabled(true);
	auto cleaner = new QtXMLCleaner::Cleaner(ui->inputFileLineEdit->text(), ui->outputFileLineEdit->text()); // Deleted via a deleteLater slot
	cleaner->SetSortQGridLayoutChildren(ui->sortQGridLayoutCheckbox->isChecked());
	cleaner->SetRemoveNativeTrue(ui->removeNativeTrueCheckbox->isChecked());
	cleaner->SetRemoveStdsetZero(ui->removeStdsetZeroCheckbox->isChecked());

	// Store off the last thing we ran as our default settings for next time...
	QSettings settings;	
	settings.beginGroup("Options");

	settings.setValue("inputFile", ui->inputFileLineEdit->text());
	settings.setValue("outputFile", ui->outputFileLineEdit->text());
	settings.setValue("sortQGridLayoutChildren", ui->sortQGridLayoutCheckbox->isChecked());
	settings.setValue("removeNativeTrue", ui->removeNativeTrueCheckbox->isChecked());
	settings.setValue("removeStdsetZero", ui->removeStdsetZeroCheckbox->isChecked());
	settings.endGroup();
	settings.sync();

	connect(cleaner, &QThread::finished, cleaner, &QObject::deleteLater);
	connect(cleaner, &QtXMLCleaner::Cleaner::processComplete, this, &MainWindow::handleSuccess);
	connect(cleaner, &QtXMLCleaner::Cleaner::errorOccurred, this, &MainWindow::handleError);
	cleaner->start();
}

void MainWindow::on_closeButton_clicked()
{
	QSettings settings;
	settings.beginGroup("MainWindow");
	settings.setValue("size", size());
	settings.setValue("pos", pos());
	settings.endGroup();
	settings.sync();
	QApplication::quit();
}

void MainWindow::handleSuccess()
{
	QMessageBox::information(this, "Processing complete", "The XML file was processed successfully.", QMessageBox::Close);
	ui->runButton->setEnabled(true);
}

void MainWindow::handleError(QString message)
{
	QMessageBox::warning(this, "Processing failed", message, QMessageBox::Close);
	ui->runButton->setEnabled(true);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	QSettings settings;
	settings.beginGroup("MainWindow");
	settings.setValue("size", size());
	settings.setValue("pos", pos());
	settings.endGroup();
	settings.sync();
	event->accept();
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasUrls())
		event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent* event)
{
	ui->inputFileLineEdit->setText(event->mimeData()->urls().first().toLocalFile());
	ui->outputFileLineEdit->setText(event->mimeData()->urls().first().toLocalFile());

	event->acceptProposedAction();
}