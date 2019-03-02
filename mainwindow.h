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
    /*!
     * \brief MainWindow constructs a new MainWindow
     * \param[in] parent a parent widget
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /*!
     * \brief ~MainWindow destructs the MainWindow
     */
    ~MainWindow();

signals:
    /*!
     * \brief SimulationStartRequest emitted when "Start simulation" button clicked
     * \param[in] scene a pointer to the scene that holds objects to be displayed
     */
    void SimulationStartRequest(const SituationScene *const scene);

    /*!
     * \brief SimulationStopRequest emitted when "Stop simulation" button clicked
     */
    void SimulationStopRequest();

private slots:
    void clicked();

private:
    void refreshSimulationControlButton();

    Ui::MainWindow       *ui_;
    QGridLayout          *mainLayout_;
    QGraphicsView        *view_;
    SituationScene       *situation_;
    FormationKeypad      *formation_;
    ScratchpadController *path_;
    QPushButton          *simulationControlButton_;
    bool                 simulationStarted_;
};

#endif // MAINWINDOW_H
