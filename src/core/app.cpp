#include "app.h"
#include "gui/mainwindow.h"

#include <QDebug>

App *App::sThis = NULL;

App::App()
{
	sThis = this;
	mMainWindow = new MainWindow();
	
	mMainWindow->show();
}

App::~App()
{

}

App*
App::sInstance()
{
	if (sThis == NULL)
		new App;
	return sThis;
}
