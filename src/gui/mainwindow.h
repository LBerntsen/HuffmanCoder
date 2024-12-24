#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *aParent = Q_NULLPTR);
	~MainWindow();

signals:
	void sigCompress(QString aFilePath);
	void sigDecompress(QString aFilePath);

private slots:
	void onBrowseFile();
	void onValidateFile(QString aFilePath);
	void onCompress();
	void onDecompress();

private:
	Ui::MainWindowClass mUi;
};

#endif
