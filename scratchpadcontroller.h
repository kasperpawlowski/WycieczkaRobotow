#ifndef SCRATCHPADCONTROLER_H
#define SCRATCHPADCONTROLER_H

#include <QWidget>
#include <QPushButton>
#include "scratchpad.h"

/*!
 * \brief The ScratchpadController class adds "Accept" and "Clear" buttons to
 *        the scratchpad and controls it
 *
 * "Clear" button serves for instant clearing of the path drawn on the scratchpad.
 * "Accept" button serves for generation of a file that contains information about
 * the points that form the drawn path.
 */
class ScratchpadController : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief ScratchpadController constructs a new ScratchpadController
     * \param[in] parent a parent widget
     */
    ScratchpadController(QWidget *parent = nullptr);

private slots:
    void acceptButtonClicked();
    void clearButtonClicked();
    void newDrawingAppeared();

private:
    enum GenerationState {NOT_GENERATED_YET, NOT_GENERATED_INVALID, GENERATED};
    void refreshAcceptButtonState();

    Scratchpad       *scratchpad_;
    GenerationState  generationState_;
    QPushButton      *acceptButton_;
    QPushButton      *clearButton_;
};

#endif // SCRATCHPADCONTROLER_H
