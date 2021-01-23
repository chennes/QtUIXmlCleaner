#ifndef _QTUIXMLCLEANER_MAINWINDOW_H_
#define _QTUIXMLCLEANER_MAINWINDOW_H_

#include <QMainWindow>
#include <QThread>
#include <memory>

namespace Ui {
	class MainWindow;
}

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