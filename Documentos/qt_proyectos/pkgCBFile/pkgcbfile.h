#ifndef PKGCBFILE_H
#define PKGCBFILE_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>

namespace Ui {
class pkgCBFile;
}

class pkgCBFile : public QMainWindow
{
    Q_OBJECT

public:
    explicit pkgCBFile(QWidget *parent = 0);
    ~pkgCBFile();

private:
    Ui::pkgCBFile *ui;
    QFileDialog selectFIles;

private slots:
    void selectFolder();

};

#endif // PKGCBFILE_H
