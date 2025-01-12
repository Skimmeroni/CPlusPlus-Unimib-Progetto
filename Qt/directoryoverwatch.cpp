#include "directoryoverwatch.h"
#include "ui_directoryoverwatch.h"

DirectoryOverwatch::DirectoryOverwatch(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DirectoryOverwatch)
    , PendingEvents(QVector<PackedFile>(0))
    , ChosenDirStatus(QMap<QString, QDateTime>())
    , chosenDirName(QString())
    , overwatch(QFileSystemWatcher())
    , trigger(QTimer())
{
    // Whenever the watcher detects a change, take a look
    QObject::connect(&(this->overwatch), &QFileSystemWatcher::directoryChanged,
                     this, &DirectoryOverwatch::fileSystemInspection);

    // Update the table every 3 seconds
    QObject::connect(&(this->trigger), &QTimer::timeout,
                     this, &DirectoryOverwatch::updateTable);
    ui->setupUi(this);
}

DirectoryOverwatch::~DirectoryOverwatch()
{
    this->resetStatus();
    delete ui;
}

// Reset everything 
void DirectoryOverwatch::resetStatus()
{
    this->ChosenDirStatus.clear();
    this->PendingEvents.clear();
    ui->tabledContent->clearContents();
    ui->tabledContent->setRowCount(0);
}

void DirectoryOverwatch::on_chooseDirectory_clicked()
{
    QString d = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home",
                                                  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    // If 'cancel' was clicked, do nothing
    if (!d.isEmpty()) {
        this->resetStatus();

	// Add trailing '/'
        this->chosenDirName = d + "/";
        QDir theDir(chosenDirName);
        QStringList DirContent = theDir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);

        QStringList::const_iterator start = DirContent.cbegin();
        QStringList::const_iterator finish = DirContent.cend();

	// Add all directories to the list
        while (start != finish) {
            QString thisFile = *start;
            QDateTime lastModified = QFileInfo(chosenDirName + thisFile).lastModified();
            this->ChosenDirStatus[thisFile] = lastModified;
            ++start;
        }

        this->overwatch.addPath(chosenDirName);
        ui->infoLabel->setText("Watching directory: " + chosenDirName);

	// If a log file is found, load it
        QString logPath = this->chosenDirName + ".overwatch.log";
        if (QFileInfo(logPath).exists()) {
            this->loadLogFromFile();
        }

        this->updateTable();
        this->trigger.start(3000);
        ui->save->setEnabled(true);
    }
}

void DirectoryOverwatch::loadLogFromFile()
{
    QString logPath = this->chosenDirName + ".overwatch.log";
    QFile logFile(logPath);
    logFile.open(QIODevice::ReadOnly);
    QTextStream input(&logFile);

    QString thisLine;
    while (input.readLineInto(&thisLine)) {
        QStringList thisLineTokens = thisLine.split(u',', Qt::SkipEmptyParts);

        QString a = thisLineTokens[0];
        QString b = thisLineTokens[1];
        QDateTime c = QDateTime::fromString(thisLineTokens[2]);

        PackedFile thisEvent(a, b, c);
        this->PendingEvents.push_back(thisEvent);
    }

    logFile.close();
}

void DirectoryOverwatch::detectAdded()
{
    QDir chosenDirectory(this->chosenDirName);
    QStringList DirContent = chosenDirectory.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);

    QStringList::const_iterator start_1 = DirContent.cbegin();
    QStringList::const_iterator finish_1 = DirContent.cend();

    while (start_1 != finish_1) {
        QString thisFile = *start_1;
        if (this->ChosenDirStatus.count(thisFile) <= 0) {
            QDateTime lastModified = QFileInfo(this->chosenDirName + thisFile).lastModified();
            PackedFile p(thisFile, "Added", lastModified);
            this->PendingEvents.push_back(p);
            this->ChosenDirStatus[thisFile] = lastModified;
            break;
        }
        ++start_1;
    }
}

void DirectoryOverwatch::detectDeleted()
{
    QMap<QString, QDateTime>::key_value_iterator start_2 = this->ChosenDirStatus.keyValueBegin();
    QMap<QString, QDateTime>::key_value_iterator finish_2 = this->ChosenDirStatus.keyValueEnd();

    while (start_2 != finish_2) {
        QString thisFile = start_2->first;
        if (!QFileInfo(this->chosenDirName + thisFile).exists()) {
            QDateTime lastModified = start_2->second;
            PackedFile p(thisFile, "Deleted", lastModified);
            this->PendingEvents.push_back(p);
            this->ChosenDirStatus.remove(start_2->first);
            break;
        }
        ++start_2;
    }
}

void DirectoryOverwatch::detectModified()
{
    QMap<QString, QDateTime>::key_value_iterator start_3 = this->ChosenDirStatus.keyValueBegin();
    QMap<QString, QDateTime>::key_value_iterator finish_3 = this->ChosenDirStatus.keyValueEnd();

    while (start_3 != finish_3) {
        QString thisFile = start_3->first;
        if (QFileInfo(this->chosenDirName + thisFile).exists()) {
            QDateTime timestampInTheMap = start_3->second;
            QDateTime timestampInTheDir = QFileInfo(this->chosenDirName + thisFile).lastModified();

            if (timestampInTheMap != timestampInTheDir) {
                PackedFile p(thisFile, "Modified", timestampInTheDir);
                this->PendingEvents.push_back(p);
                this->ChosenDirStatus[thisFile] = timestampInTheDir;
                break;
            }
        }
        ++start_3;
    }
}

void DirectoryOverwatch::fileSystemInspection()
{
    // Detect which kind of event
    this->detectAdded();
    this->detectDeleted();
    this->detectModified();
}

void DirectoryOverwatch::exportLogToFile()
{

    QString logPath = this->chosenDirName + ".overwatch.log";
    QFile logFile(logPath);
    logFile.open(QIODevice::WriteOnly);
    QTextStream output(&logFile);

    for (int i = 0; i < ui->tabledContent->rowCount(); ++i) {
        output << ui->tabledContent->item(i, 1)->text() << ","
               << ui->tabledContent->item(i, 2)->text() << ","
               << ui->tabledContent->item(i, 3)->text() << "\n";
    }

    logFile.close();

}

void DirectoryOverwatch::updateTable()
{
    QVector<PackedFile>::const_iterator start = this->PendingEvents.cbegin();
    QVector<PackedFile>::const_iterator finish = this->PendingEvents.cend();

    int n = static_cast<int>(std::distance(start, finish));
    int previousLastRow = ui->tabledContent->rowCount();
    ui->tabledContent->setRowCount(previousLastRow + n);

    while (start != finish) {
        QTableWidgetItem* flag = new QTableWidgetItem();
        flag->setText("▪");
        flag->setFont(QFont(this->font().family(), 36));

        if (start->action == "Added") {
            flag->setForeground(QBrush(Qt::green));
        } else if (start->action == "Deleted") {
            flag->setForeground(QBrush(Qt::red));
        } else {
            flag->setForeground(QBrush(Qt::blue));
        }

        ui->tabledContent->setItem(previousLastRow, 0, flag);
        ui->tabledContent->setItem(previousLastRow, 1, new QTableWidgetItem(start->fileName));
        ui->tabledContent->setItem(previousLastRow, 2, new QTableWidgetItem(start->action));
        ui->tabledContent->setItem(previousLastRow, 3, new QTableWidgetItem((start->timestamp).toString()));

        ++previousLastRow;
        ++start;
    }

    this->PendingEvents.clear();
    if (n > 0) {
        ui->tabledContent->sortItems(3, Qt::AscendingOrder);
    }
}

void DirectoryOverwatch::on_quit_clicked()
{
    ui->tabledContent->sortItems(3, Qt::AscendingOrder);
    this->exportLogToFile();
}


void DirectoryOverwatch::on_save_clicked()
{
    ui->tabledContent->sortItems(3, Qt::AscendingOrder);
    this->exportLogToFile();
}

