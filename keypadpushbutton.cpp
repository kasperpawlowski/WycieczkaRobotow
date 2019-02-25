#include "keypadpushbutton.h"

KeypadPushButton::KeypadPushButton(const unsigned int row, const unsigned int col,
                                   QWidget *parent) :
    QPushButton(parent), row_(row), col_(col)
{
    setCheckable(true);
    setChecked(false);

    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}

void KeypadPushButton::reemitClicked()
{
    emit clicked(row_, col_);
}
