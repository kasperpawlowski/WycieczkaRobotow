#include <QGridLayout>
#include <QDesktopWidget>
#include <QDebug>
#include "formationkeypad.h"

FormationKeypad::FormationKeypad(const unsigned int rows, const unsigned int cols,
                                 QWidget *parent) :
    QWidget(parent), rows_(rows), cols_(cols), generationState_(NOT_GENERATED_YET)
{
    // calculate the size of a widget
    int widget_size = int(0.45*QDesktopWidget().screenGeometry(this).height());
    setFixedSize(widget_size, widget_size);

    // creates a container for to be created bi-state push buttons,
    // thanks to that we can refer to a particular element with square brackets
    formationButtons_ = ButtonsContainer(rows_, ButtonsVector(cols_, nullptr));

    QGridLayout* keypad_layout = new QGridLayout(this);
    for(unsigned int i = 0; i < rows_; ++i)
    {
        for(unsigned int j = 0; j < cols_; ++j)
        {
            formationButtons_[i][j] = new KeypadPushButton(i, j, this);
            keypad_layout->addWidget(formationButtons_[i][j], int(i), int(j));

            connect(formationButtons_[i][j], SIGNAL(clicked(const unsigned int, const unsigned int)),
                    this, SLOT(buttonClicked(const unsigned int, const unsigned int)));
        }
    }

    // add "Accept" and "Clear" buttons
    acceptButton_ = new QPushButton(this);
    clearButton_  = new QPushButton("Clear", this);
    keypad_layout->addWidget(acceptButton_, int(rows_), 0, 1, int(cols_));
    keypad_layout->addWidget(clearButton_, int(rows_ + 1), 0, 1, int(cols_));
    connect(acceptButton_, SIGNAL(clicked()), this, SLOT(acceptButtonClicked()));
    connect(clearButton_, SIGNAL(clicked()), this, SLOT(clearButtonClicked()));
    refreshAcceptButtonState();
}

bool FormationKeypad::isFormationValid() const
{
    bool any_object_in_formation = false;

    for(unsigned int i = 0; i < rows_; ++i)
    {
        for(unsigned int j = 0; j < cols_; ++j)
        {
            if(formationButtons_[i][j]->isChecked())
            {
                any_object_in_formation = true;
                break;
            }
        }
    }

    if(!any_object_in_formation)
    {
        qWarning() << "Formation Keypad: there is no object in a formation";
    }

    return any_object_in_formation;
}

bool FormationKeypad::generateFormationData() const
{
    return true;
}

void FormationKeypad::buttonClicked(const unsigned int /*row*/, const unsigned int /*col*/)
{
    // when any button clicked assume that the new file is meant to be generated
    generationState_ = NOT_GENERATED_YET;
    refreshAcceptButtonState();
}

void FormationKeypad::acceptButtonClicked()
{
    if(isFormationValid())
    {
        generateFormationData();
        generationState_ = GENERATED;
    }
    else
    {
        generationState_ = NOT_GENERATED_INVALID;
    }
    refreshAcceptButtonState();
}

void FormationKeypad::clearButtonClicked()
{
    clearKeypad();
    refreshAcceptButtonState();
}

void FormationKeypad::refreshAcceptButtonState()
{
    switch(generationState_)
    {
        case NOT_GENERATED_YET:
            acceptButton_->setText("Accept (formation not generated)");
            acceptButton_->setStyleSheet("");
            break;
        case NOT_GENERATED_INVALID:
            acceptButton_->setText("Accept (formation invalid)");
            acceptButton_->setStyleSheet("background-color: rgb(255, 0, 0); color: rgb(0, 0, 0)");
            break;
        case GENERATED:
            acceptButton_->setText("Accept (formation generated)");
            acceptButton_->setStyleSheet("background-color: rgb(0, 255, 0); color: rgb(0, 0, 0)");
            break;
    }
}

void FormationKeypad::clearKeypad()
{
    for(unsigned int i = 0; i < rows_; ++i)
    {
        for(unsigned int j = 0; j < cols_; ++j)
        {
            formationButtons_[i][j]->setChecked(false);
        }
    }
    generationState_ = NOT_GENERATED_YET;
}
