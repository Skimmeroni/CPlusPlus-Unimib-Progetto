#include "directoryoverwatch.h"
#include "ui_directoryoverwatch.h"

DirectoryOverwatch::DirectoryOverwatch(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DirectoryOverwatch)
    , CollectedEvents(QVector<PackedFile>(0))
    , ChosenDirStatus(QMap<QString, QDateTime>())
    , chosenDirName(QString())
    , overwatch(QFileSystemWatcher())
{
    QObject::connect(&(this->overwatch), &QFileSystemWatcher::directoryChanged,
                     this, &DirectoryOverwatch::fileSystemInspection);
    ui->setupUi(this);
}

DirectoryOverwatch::~DirectoryOverwatch()
{
    delete ui;
}

void DirectoryOverwatch::on_chooseDirectory_clicked()
{
    QString d = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home",
                                                  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!d.isEmpty()) {
        this->ChosenDirStatus.clear();
        this->CollectedEvents.clear();
        ui->tabledContent->clearContents();
        ui->tabledContent->setRowCount(0);
        ui->refresh->setEnabled(true);

        this->chosenDirName = d + "/";

        QDir theDir(chosenDirName);
        QStringList DirContent = theDir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);

        QStringList::const_iterator start = DirContent.cbegin();
        QStringList::const_iterator finish = DirContent.cend();

        while (start != finish) {
            QString thisFile = *start;
            QDateTime lastModified = QFileInfo(chosenDirName + thisFile).lastModified();
            this->ChosenDirStatus[thisFile] = lastModified;
            ++start;
        }

        this->overwatch.addPath(chosenDirName);
        ui->infoLabel->setText("Watching directory: " + chosenDirName);

        QString logPath = this->chosenDirName + ".overwatch.log";
        if (QFileInfo(logPath).exists()) {
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
                this->CollectedEvents.push_back(thisEvent);
            }

            logFile.close();
        }
    }
}

void DirectoryOverwatch::fileSystemInspection()
{
    // É una aggiunta
    QDir chosenDirectory(this->chosenDirName);
    QStringList DirContent = chosenDirectory.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);

    QStringList::const_iterator start_1 = DirContent.cbegin();
    QStringList::const_iterator finish_1 = DirContent.cend();

    while (start_1 != finish_1) {
        QString thisFile = *start_1;
        if (this->ChosenDirStatus.count(thisFile) <= 0) {
            QDateTime lastModified = QFileInfo(this->chosenDirName + thisFile).lastModified();
            PackedFile p(thisFile, "Added", lastModified);
            this->CollectedEvents.push_back(p);
            this->ChosenDirStatus[thisFile] = lastModified;
            break;
        }
        ++start_1;
    }

    // É una rimozione
    QMap<QString, QDateTime>::key_value_iterator start_2 = this->ChosenDirStatus.keyValueBegin();
    QMap<QString, QDateTime>::key_value_iterator finish_2 = this->ChosenDirStatus.keyValueEnd();

    while (start_2 != finish_2) {
        QString thisFile = start_2->first;
        if (!QFileInfo(this->chosenDirName + thisFile).exists()) {
            QDateTime lastModified = start_2->second;
            PackedFile p(thisFile, "Deleted", lastModified);
            this->CollectedEvents.push_back(p);
            this->ChosenDirStatus.remove(start_2->first);
            break;
        }
        ++start_2;
    }

    // É una modifica
    QMap<QString, QDateTime>::key_value_iterator start_3 = this->ChosenDirStatus.keyValueBegin();
    QMap<QString, QDateTime>::key_value_iterator finish_3 = this->ChosenDirStatus.keyValueEnd();

    while (start_3 != finish_3) {
        QString thisFile = start_3->first;
        if (QFileInfo(this->chosenDirName + thisFile).exists()) {
            QDateTime timestampInTheMap = start_3->second;
            QDateTime timestampInTheDir = QFileInfo(this->chosenDirName + thisFile).lastModified();

            if (timestampInTheMap != timestampInTheDir) {
                PackedFile p(thisFile, "Modified", timestampInTheDir);
                this->CollectedEvents.push_back(p);
                this->ChosenDirStatus[thisFile] = timestampInTheDir;
                break;
            }
        }
        ++start_3;
    }
}

void DirectoryOverwatch::on_refresh_clicked()
{
    QVector<PackedFile>::const_iterator start = this->CollectedEvents.cbegin();
    QVector<PackedFile>::const_iterator finish = this->CollectedEvents.cend();

    unsigned int n = static_cast<unsigned int>(std::distance(start, finish));
    ui->tabledContent->clearContents();
    ui->tabledContent->setRowCount(n);

    for (unsigned int i = 0; i < n; ++i, ++start) {
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

        ui->tabledContent->setItem(i, 0, flag);
        ui->tabledContent->setItem(i, 1, new QTableWidgetItem(start->fileName));
        ui->tabledContent->setItem(i, 2, new QTableWidgetItem(start->action));
        ui->tabledContent->setItem(i, 3, new QTableWidgetItem((start->timestamp).toString()));
    }

    QString logPath = this->chosenDirName + ".overwatch.log";
    QFile logFile(logPath);
    logFile.open(QIODevice::WriteOnly);
    QTextStream output(&logFile);

    start = this->CollectedEvents.cbegin();

    while (start != finish) {
        output << start->fileName << ","
               << start->action << ","
               << (start->timestamp).toString() << "\n";
        ++start;
    }

    logFile.close();
}
