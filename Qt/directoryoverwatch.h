#ifndef DIRECTORYOVERWATCH_H
#define DIRECTORYOVERWATCH_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class DirectoryOverwatch;
}
QT_END_NAMESPACE

class DirectoryOverwatch : public QMainWindow
{
    Q_OBJECT

public:
    DirectoryOverwatch(QWidget *parent = nullptr);
    ~DirectoryOverwatch();

private:
    Ui::DirectoryOverwatch *ui;
};
#endif // DIRECTORYOVERWATCH_H
