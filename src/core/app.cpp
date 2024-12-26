#include "app.h"
#include "gui/mainwindow.h"

#include "Node.h"

#include <QDebug>
#include <QFile>
#include <QFileInfo>

#include "PriorityQueue.h"

App *App::sThis = NULL;

App::App()
{
	sThis = this;
	mMainWindow = new MainWindow();
	
	mMainWindow->show();

    cSwitchCharacter = "§";

	connect(mMainWindow, &MainWindow::sigCompress, this, &App::onCompress);
	connect(mMainWindow, &MainWindow::sigDecompress, this, &App::onDecompress);
    connect(this, &App::sigStatusChanged, mMainWindow, &MainWindow::onStatusChanged);
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


void
App::onCompress(QString aFilePath)
{
    // Initialize some stats
    int bitsBefore = 0;
    int bitsAfter = 0;

    // First have to read file to generate encoding table from frequencies
    QFile file(aFilePath);
    file.open(QIODevice::ReadOnly);
    QTextStream textStream(&file);
    QString stream = textStream.readAll();
    bitsBefore = stream.length() * 8;
    stream.replace("\n", cSwitchCharacter);
    file.close();

    QHash<QString, int> frequencyHash = countFrequency(stream);
    QList<int> frequencyList = frequencyHash.values();
    Node *tree = generateTree(frequencyList);
    QHash<QString, QString> encoding = generateEncoding(tree, frequencyHash);

    // Generate encoding table to send out into new compressed file line 1
    QString outEncoding = "";
    QList<QString> encodingKeys = encoding.keys();
    for(QString key : encodingKeys)
        outEncoding += QString("%1^%2;").arg(key).arg(encoding[key]);
    outEncoding += "\n";

    // Generate encoded stream to send out into new compressed file
    QString outStream = "";
    for(QString character : stream)
        outStream += encoding[character];
    bitsAfter = outStream.length();

    // Write encoding table and data to file with compressed suffix
    QFileInfo fileInfo(aFilePath);
    QList<QString> filenameParts = fileInfo.fileName().split(".");
    QString filename = filenameParts[0] + "_compressed." + filenameParts[1];
    QFile compressedFile(fileInfo.absolutePath() + "/" + filename);
    compressedFile.open(QIODevice::WriteOnly);
    QTextStream outTextStream(&compressedFile);
    outTextStream << outEncoding;
    outTextStream << outStream;
    compressedFile.close();

    emit sigStatusChanged(QString("New file was written to %1 \n Old file was %2 bits in size \n The compressed file is %3 bits in size \n This results in %4 bits saved or around %5 bytes saved.").arg(filename).arg(bitsBefore).arg(bitsAfter).arg(bitsBefore - bitsAfter).arg((bitsBefore - bitsAfter) / 8));
}


void
App::onDecompress(QString aFilePath)
{
    // Read encoding table and data from file
    QFile file(aFilePath);
    file.open(QIODevice::ReadOnly);
    QTextStream textStream(&file);
    QString encodingTableStream = textStream.readLine();
    QString dataStream = textStream.readAll();
    file.close();

    // Create decoding hash from encoding table
    QHash<QString, QString> decodingHash;
    QStringList encodingTableParts = encodingTableStream.split(";");
    for(QString code : encodingTableParts)
    {
        if(code == "" || code == "\n")
            continue;

        QStringList codeParts = code.split("^");
        decodingHash[codeParts[1]] = codeParts[0];
    }

    // Decode
    QString outStream = "";
    QString currentCode = "";
    for(QString code : dataStream)
    {
        currentCode += code;
        if(decodingHash.contains(currentCode))
        {
            outStream += decodingHash[currentCode];
            currentCode = "";
        }
    }
    outStream = outStream.replace(cSwitchCharacter, "\n");

    // Write decoded data to file with decompressed suffix
    QFileInfo fileInfo(aFilePath);
    QStringList filenameParts = fileInfo.fileName().split(".");
    QString filename = filenameParts[0] + "_decompressed." + filenameParts[1];
    QFile decompressedFile(fileInfo.absolutePath() + "/" + filename);
    decompressedFile.open(QIODevice::WriteOnly);
    QTextStream outTextStream(&decompressedFile);
    outTextStream << outStream;
    decompressedFile.close();

    emit sigStatusChanged(QString("New file was written to %1").arg(filename));
}


QHash<QString, int>
App::countFrequency(QString aStream)
{
    QHash<QString, int> frequencies;

    for(QString character: aStream)
    {
        if(!frequencies.contains(character))
            frequencies[character] = 1;
        else
            frequencies[character] = frequencies[character] + 1;
    }

    return frequencies;
}


Node *
App::generateTree(QList<int> aFrequencies)
{
    PriorityQueue queue;
    for(int frequency: aFrequencies)
        queue.append(new Node(frequency));

    while(queue.length() > 1) // If list is 1 long then its only the root node
    {
        Node *leftChild = queue.pop();
        Node *rightChild = queue.pop();
        int sum = leftChild->getValue() + rightChild->getValue();
        Node *parentNode = new Node(sum, leftChild, rightChild);
        queue.append(parentNode);
    }

    return queue.pop();
}


QHash<QString, QString>
App::generateEncoding(Node *aTree, QHash<QString, int> aFrequencyHash)
{
    QHash<QString, int> codes;
    QHash<QString, QString> letterCodes;
    traverseTree(aTree, codes, "");

    QList<int> valuesList = aFrequencyHash.values();
    QList<QString> keysList = aFrequencyHash.keys();

    QList<QString> codesKeys = codes.keys();
    for(int i = 0; i < codes.size(); i++)
    {
        int value = codes[codesKeys[i]];
        int index = valuesList.indexOf(value);
        QString character = keysList[index];
        keysList.removeAt(index);
        valuesList.removeAt(index);
        letterCodes[codesKeys[i]] = character;
    }

    // Flip codes and letters
    QHash<QString, QString> encoding;
    QList<QString> resultValues = letterCodes.values();
    QList<QString> resultKeys = letterCodes.keys();

    for(int i = 0; i < resultValues.length(); i++)
        encoding[resultValues[i]] = resultKeys[i];

    return encoding;
}


void
App::traverseTree(Node *aTree, QHash<QString, int> &aCodes, QString aCode)
{
    // Base case leaf node add aCode to aCodes with root value
    if(aTree->isLeaf())
    {
        aCodes[aCode] = aTree->getValue();
        return;
    }

    if(aTree->getLeftChild() != nullptr)
    {
        QString code = aCode;
        code += "0";
        traverseTree(aTree->getLeftChild(), aCodes, code);
    }

    if(aTree->getRightChild() != nullptr)
    {
        QString code = aCode;
        code += "1";
        traverseTree(aTree->getRightChild(), aCodes, code);
    }
}