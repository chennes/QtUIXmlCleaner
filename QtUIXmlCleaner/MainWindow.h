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

#ifndef _QTUIXMLCLEANER_MAINWINDOW_H_
#define _QTUIXMLCLEANER_MAINWINDOW_H_

#include <QMainWindow>
#include <QThread>
#include <memory>

namespace Ui {
	class MainWindow;
}

/**
 * \brief The main (and only) window of the program.
 * 
 * Construct a single MainWindow object at the beginning of the program: it expects no
 * parent widget and is entirely self-contained. There are no further user-callable
 * functions except those provided by `QMainWindow`.
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

protected:
	void closeEvent(QCloseEvent* event) override;
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;

private slots:
	void on_browseInputFileButton_clicked();
	void on_browseOutputFileButton_clicked();
	void on_runButton_clicked();
	void on_closeButton_clicked();
	void handleSuccess();
	void handleError(QString message);

private:
	std::unique_ptr<Ui::MainWindow> ui;
	QThread workerThread;
};

#endif // _QTUIXMLCLEANER_MAINWINDOW_H_