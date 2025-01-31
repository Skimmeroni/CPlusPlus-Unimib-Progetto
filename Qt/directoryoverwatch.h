#ifndef DIRECTORYOVERWATCH_H
#define DIRECTORYOVERWATCH_H

#include <QMainWindow>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileSystemWatcher>
#include <QString>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class DirectoryOverwatch;
}
QT_END_NAMESPACE

// Data structure that holds a file that was modified,
// what happened and when
struct PackedFile {
    QString fileName;
    QString action;
    QDateTime timestamp;

    PackedFile()
        : fileName(QString()), action(QString()), timestamp(QDateTime())
    {}

    PackedFile(QString fileName, QString action, QDateTime timestamp)
        : fileName(QString()), action(QString()), timestamp(QDateTime())
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
        : fileName(QString()), action(QString()), timestamp(QDateTime())
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

class DirectoryOverwatch : public QMainWindow
{
    Q_OBJECT

public:
    DirectoryOverwatch(QWidget *parent = nullptr);
    ~DirectoryOverwatch();

private slots:
    void on_chooseDirectory_clicked();
    void on_quit_clicked();

    void on_save_clicked();

private:
    Ui::DirectoryOverwatch *ui;
    QVector<PackedFile> PendingEvents;
    QMap<QString, QDateTime> ChosenDirStatus;
    QString logPath;
    QString chosenDirName;
    QFileSystemWatcher overwatch;
    QTimer trigger;
    void detectAdded();
    void detectDeleted();
    void detectModified();
    void exportLogToFile();
    void fileSystemInspection();
    void loadLogFromFile();
    void updateTable();
    void resetStatus();
};
#endif // DIRECTORYOVERWATCH_H
