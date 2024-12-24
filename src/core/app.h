#ifndef APP_H
#define APP_H

#include <QObject>

class MainWindow;

class Node;

class App : public QObject
{
	Q_OBJECT

public:
	App();
	virtual ~App();
	static App *sInstance();

private slots:
	void onCompress(QString aFilePath);
	void onDecompress(QString aFilePath);

private:
	QHash<QString, int> countFrequency(QString aStream);
	Node *generateTree(QList<int> aFrequencies);
	QHash<QString, QString> generateEncoding(Node *aTree, QHash<QString, int> aFrequencyHash);
	void traverseTree(Node *aTree, QHash<QString, int> &aCodes, QString aCode);

private:
	static App *sThis;
	MainWindow *mMainWindow;
	QString cSwitchCharacter;

};

#endif
