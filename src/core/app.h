#ifndef APP_H
#define APP_H

#include <QObject>

class MainWindow;

class App : public QObject
{
	Q_OBJECT

public:
	App();
	virtual ~App();
	static App *sInstance();

private:
	static App *sThis;
	MainWindow *mMainWindow;

};

#endif
