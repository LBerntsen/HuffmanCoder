#include "core/app.h"

#include <QApplication>

int main(int aNumArgs, char *aArgArray[])
{
	Q_INIT_RESOURCE(mainwindow);

	QApplication kuApp(aNumArgs, aArgArray);

	App::sInstance();
	return kuApp.exec();
}
