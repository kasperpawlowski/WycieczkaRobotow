#ifndef KEYPADPUSHBUTTON_H
#define KEYPADPUSHBUTTON_H

#include <QPushButton>

/*!
 * \brief The KeypadPushButton class is a single bi-state push button of a keypad
 *         with ability to reemit signals when clicked
 *
 * An instance of this class has attributes that describe its position (row and
 * column) in a keypad which is an owner of that instance. Signals and slots are
 * connected in a way that when the button is clicked, it reemits clicked signal
 * with information about its position.
 * It helps to handle signals from multiple buttons that serve for the same or similar action.
 */
class KeypadPushButton : public QPushButton
{
    Q_OBJECT
public:
    /*!
     * \brief KeypadPushButton constructs a new KeypadPushButton
     * \param[in] row a row in a keypad the button is placed
     * \param[in] col a column in a keypad the button is placed
     * \param[in] parent a parent widget
     */
    explicit KeypadPushButton(const unsigned int row, const unsigned int col,
                              QWidget *parent = nullptr);

signals:
    /*!
     * \brief clicked is emitted when the button is clicked
     * \param[in] row a row in a keypad the button is placed
     * \param[in] col a column in a keypad the button is placed
     */
    void clicked(const unsigned int row, const unsigned int col);

private slots:
    void reemitClicked();

private:
    KeypadPushButton() = delete;
    unsigned int row_;
    unsigned int col_;
};

#endif // KEYPADPUSHBUTTON_H
