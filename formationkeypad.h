#ifndef FORMATIONKEYPAD_H
#define FORMATIONKEYPAD_H

#include <QWidget>
#include "keypadpushbutton.h"

/*!
 * \brief The FormationKeypad class is a keypad widget that allows the user to
 *        define a desired formation of pushed buttons.
 *
 * A square keypad is formed in a grid. Contains (rows_ x cols_) bi-state push buttons
 * that let the user to define a desired formation pattern.
 * "Clear" button serves for instant clearing of the pattern that have been pushed.
 * "Accept" button serves for generation of a file that contains information about
 * a position of the pushed buttons.
 */
class FormationKeypad : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief FormationKeypad constructs a new FormationKeypad
     * \param[in] rows a number of rows for bi-state push buttons
     * \param[in] cols a number of columns for bi-state push buttons
     * \param[in] parent a parent widget
     */
    explicit FormationKeypad(const unsigned int rows, const unsigned int cols,
                             QWidget *parent = nullptr);

    /*!
     * \brief isFormationValid checks whether any bi-state push button has been pushed
     * \return true when any button has been pushed, false otherwise
     */
    bool isFormationValid() const;

    /*!
     * \brief generateFormationData generates the file that contains information
     *        about a position of the pushed buttons. Assumes that validity of the
     *        formation has been checked
     * \return true on success, false otherwise
     */
    virtual bool generateFormationData();

private slots:
    void buttonClicked(const unsigned int row, const unsigned int col);
    void acceptButtonClicked();
    void clearButtonClicked();

private:
    typedef std::vector<KeypadPushButton*> ButtonsVector;
    typedef std::vector<ButtonsVector>     ButtonsContainer;
    enum GenerationState {NOT_GENERATED_YET, NOT_GENERATED_INVALID, GENERATED};
    FormationKeypad() = delete;
    void refreshAcceptButtonState();
    void clearKeypad();

    unsigned int     rows_;
    unsigned int     cols_;
    GenerationState  generationState_;
    ButtonsContainer formationButtons_;
    QPushButton      *acceptButton_;
    QPushButton      *clearButton_;
};

#endif // FORMATIONKEYPAD_H
