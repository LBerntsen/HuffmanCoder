#include "mainwindow.h"

#include <QLineEdit>
#include <QPushButton>
#include <QStandardPaths>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *aParent)
	: QMainWindow(aParent)
{
	mUi.setupUi(this);
	mUi.mCompress->setEnabled(false);
	mUi.mDecompress->setEnabled(false);

	mUi.mSelectedFile->setText(QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).last());

	connect(mUi.mBrowseFiles, &QPushButton::clicked, this, &MainWindow::onBrowseFile);
	connect(mUi.mSelectedFile, &QLineEdit::textChanged, this, &MainWindow::onValidateFile);
	connect(mUi.mCompress, &QPushButton::clicked, this, &MainWindow::onCompress);
	connect(mUi.mDecompress, &QPushButton::clicked, this, &MainWindow::onDecompress);
}


MainWindow::~MainWindow()
{

}


void
MainWindow::onBrowseFile()
{
	QString filePath = QFileDialog::getOpenFileUrl(this, "Open .txt file", QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).last(), "Text Files (*.txt)").toString(QUrl::RemoveScheme);

	if(!filePath.isEmpty())
		mUi.mSelectedFile->setText(filePath);
}


void
MainWindow::onValidateFile(QString aFilePath)
{
	QFileInfo fileInfo(aFilePath);

	if(fileInfo.exists() && fileInfo.completeSuffix() == "txt")
	{
		mUi.mCompress->setEnabled(true);
		mUi.mDecompress->setEnabled(true);
		mUi.mStatus->setText("This is a valid file, click one of the buttons to start.");
	}
	else
	{
		mUi.mCompress->setEnabled(false);
		mUi.mDecompress->setEnabled(false);
		mUi.mStatus->setText("This is an invalid file, it must exist and be of type .txt.");
	}
}


void
MainWindow::onCompress()
{
	emit sigCompress(mUi.mSelectedFile->text());
}


void
MainWindow::onDecompress()
{
	emit sigDecompress(mUi.mSelectedFile->text());
}
