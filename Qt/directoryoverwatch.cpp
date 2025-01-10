#include "directoryoverwatch.h"
#include "ui_directoryoverwatch.h"

DirectoryOverwatch::DirectoryOverwatch(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DirectoryOverwatch)
{
    ui->setupUi(this);
}

DirectoryOverwatch::~DirectoryOverwatch()
{
    delete ui;
}
