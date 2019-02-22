#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SituationData;
class PathData;
class FormationData;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    SituationData* getSituationPtr() {return situation;}

private slots:

private:
    Ui::MainWindow *ui;
    SituationData  *situation;
    PathData       *path;
    FormationData  *formation;
};

#endif // MAINWINDOW_H
