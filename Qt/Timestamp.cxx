/*
#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileSystemWatcher>
#include <QString>

enum Action {Nothing, Modified, Added, Deleted};

struct PackedFile {
    QString fileName;
    Action action;
    QDateTime timestamp;

    PackedFile()
    : fileName(QString()), action(Nothing), timestamp(QDateTime())
    {}

    PackedFile(QString fileName, Action action, QDateTime timestamp)
    : fileName(QString()), action(Nothing), timestamp(QDateTime())
    {
        this->fileName = fileName;
        this->action = action;
        this->timestamp = timestamp;
    }

    ~PackedFile() {}

    void swap(PackedFile& other)
    {
        std::swap(this->fileName, other.fileName);
        std::swap(this->action, other.action);
        std::swap(this->timestamp, other.timestamp);
    }

    PackedFile(const PackedFile& other)
    : fileName(QString()), action(Nothing), timestamp(QDateTime())
    {
        this->fileName = other.fileName;
        this->action = other.action;
        this->timestamp = other.timestamp;
    }

    PackedFile& operator=(const PackedFile& other)
    {
        if (this != &other) {
            PackedFile temp(other);
            this->swap(temp);
        }

        return *this;
    }
};

struct CmpDecreasingFileName {
    bool operator()(PackedFile a, PackedFile b) const {
        return a.fileName <= b.fileName;
    }
};

struct CmpIncreasingFileName {
    bool operator()(PackedFile a, PackedFile b) const {
        return a.fileName > b.fileName;
    }
};

struct CmpDecreasingAction {
    bool operator()(PackedFile a, PackedFile b) const {
        return a.action <= b.action;
    }
};

struct CmpIncreasingAction {
    bool operator()(PackedFile a, PackedFile b) const {
        return a.action > b.action;
    }
};

struct CmpDecreasingTimestamp {
    bool operator()(PackedFile a, PackedFile b) const {
        return a.timestamp <= b.timestamp;
    }
};

struct CmpIncreasingTimestamp {
    bool operator()(PackedFile a, PackedFile b) const {
        return a.timestamp > b.timestamp;
    }
};

static QVector<PackedFile> CollectedEvents(0);
static QMap<QString, QDateTime> DirStatus;
static const QString logPath = "";
static const QString dirName = "";

void exportLogToFile()
{
    QFile logFile(logPath);
    logFile.open(QIODevice::WriteOnly);
    QTextStream output(&logFile);

    QVector<PackedFile>::const_iterator start = CollectedEvents.cbegin();
    QVector<PackedFile>::const_iterator finish = CollectedEvents.cend();

    while (start != finish) {
        output << start->fileName << ","
               << start->action << ","
               << (start->timestamp).toString() << "\n";
        ++start;
    }

    logFile.close();
}

void loadLogFromFile()
{
    QFile logFile(logPath);
    logFile.open(QIODevice::ReadOnly);
    QTextStream input(&logFile);

    QString thisLine;
    while (input.readLineInto(&thisLine)) {
        QStringList thisLineTokens = thisLine.split(u',', Qt::SkipEmptyParts);

        QString a = thisLineTokens[0];
        Action b = Action(thisLineTokens[1].toInt());
        QDateTime c = QDateTime::fromString(thisLineTokens[2]);

        PackedFile thisEvent(a, b, c);
        CollectedEvents.push_back(thisEvent);
    }

    logFile.close();
}

void fileSystemInspection()
{
    // É una aggiunta
    QDir chosenDirectory(dirName);
    QStringList DirContent = chosenDirectory.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);

    QStringList::const_iterator start_1 = DirContent.cbegin();
    QStringList::const_iterator finish_1 = DirContent.cend();

    while (start_1 != finish_1) {
        QString thisFile = *start_1;
        if (DirStatus.count(thisFile) <= 0) {
            QDateTime lastModified = QFileInfo(dirName + thisFile).lastModified();
            PackedFile p(thisFile, Added, lastModified);
            CollectedEvents.push_back(p);
            DirStatus[thisFile] = lastModified;
            break;
        }
        ++start_1;
    }

    // É una rimozione
    QMap<QString, QDateTime>::key_value_iterator start_2 = DirStatus.keyValueBegin();
    QMap<QString, QDateTime>::key_value_iterator finish_2 = DirStatus.keyValueEnd();

    while (start_2 != finish_2) {
        QString thisFile = start_2->first;
        if (!QFileInfo(dirName + thisFile).exists()) {
            QDateTime lastModified = start_2->second;
            PackedFile p(thisFile, Deleted, lastModified);
            CollectedEvents.push_back(p);
            DirStatus.remove(start_2->first);
            break;
        }
        ++start_2;
    }

    // É una modifica
    QMap<QString, QDateTime>::key_value_iterator start_3 = DirStatus.keyValueBegin();
    QMap<QString, QDateTime>::key_value_iterator finish_3 = DirStatus.keyValueEnd();

    while (start_3 != finish_3) {
        QString thisFile = start_3->first;
        if (QFileInfo(dirName + thisFile).exists()) {
            QDateTime timestampInTheMap = start_3->second;
            QDateTime timestampInTheDir = QFileInfo(dirName + thisFile).lastModified();

            if (timestampInTheMap != timestampInTheDir) {
                PackedFile p(thisFile, Modified, timestampInTheDir);
                CollectedEvents.push_back(p);
                DirStatus[thisFile] = timestampInTheDir;
                break;
            }
        }
        ++start_3;
    }
}

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);

    QDir chosenDirectory(dirName);
    QStringList DirContent = chosenDirectory.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);

    QStringList::const_iterator start = DirContent.cbegin();
    QStringList::const_iterator finish = DirContent.cend();

    while (start != finish) {
        QString thisFile = *start;
        QDateTime lastModified = QFileInfo(dirName + thisFile).lastModified();
        DirStatus[thisFile] = lastModified;
        ++start;
    }

    loadLogFromFile();

    QFileSystemWatcher overwatch;
    overwatch.addPath(dirName);

    fileSystemInspection();
    exportLogToFile();

	return a.exec();
}
*/
