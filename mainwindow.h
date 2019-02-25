#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "situationscene.h"
#include "formationkeypad.h"
#include "scratchpadcontroller.h"

/// Provides forward declaration of a Ui::MainWindow class
namespace Ui {
class MainWindow;
}

/*!
 * \brief The MainWindow class holds all the entities of the main window
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /*!
     * \brief getSituationPtr TODO
     * \return
     */
    SituationScene* getSituationPtr() const  {return situation_;}

private:
    Ui::MainWindow       *ui_;
    QGridLayout          *mainLayout_;
    QGraphicsView        *view_;
    SituationScene       *situation_;
    FormationKeypad      *formation_;
    ScratchpadController *path_;
    QPushButton          *simulationControlButton_;
};

#endif // MAINWINDOW_H
