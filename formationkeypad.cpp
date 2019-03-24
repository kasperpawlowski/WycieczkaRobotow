#include <QGridLayout>
#include <QDesktopWidget>
#include <QFile>
#include <QDebug>
#include <QDir>
#include "formationkeypad.h"
#include "filesgenerator.h"

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

bool FormationKeypad::generateFormationData(const QString filePath) const
{
    std::pair<unsigned int, unsigned int> min_max_row = {rows_, 0};
    std::pair<unsigned int, unsigned int> min_max_col = {cols_, 0};

    // find the smallest rectange that contains all the checked buttons
    for(unsigned int i = 0; i < rows_; ++i)
    {
        for(unsigned int j = 0; j < cols_; ++j)
        {
            if(formationButtons_[i][j]->isChecked())
            {
                if(i < min_max_row.first)
                {
                    min_max_row.first = i;
                }

                if(i > min_max_row.second)
                {
                    min_max_row.second = i;
                }

                if(j < min_max_col.first)
                {
                    min_max_col.first = j;
                }

                if(j > min_max_col.second)
                {
                    min_max_col.second = j;
                }
            }
        }
    }

    // transform the coordinates in a way the coordinate system begins
    // in the left bottom corner of the rectange that contains all the
    // checked buttons
    std::vector<QPoint> formation;
    for(unsigned int i = min_max_row.first; i <= min_max_row.second; ++i)
    {
        for(unsigned int j = min_max_col.first; j <= min_max_col.second; ++j)
        {
            if(formationButtons_[i][j]->isChecked())
            {
                formation.push_back(QPoint(int(j - min_max_col.first), int(min_max_row.second - i)));
            }
        }
    }

    return FilesGenerator<std::vector>::generateFile(filePath, formation);
}

void FormationKeypad::buttonClicked(const unsigned int /*row*/, const unsigned int /*col*/)
{
    // when any button clicked assume that the new file is meant to be generated
    generationState_ = NOT_GENERATED_YET;
    refreshAcceptButtonState();
}

void FormationKeypad::acceptButtonClicked()
{
    const QString filePath = ".\\data\\FormationData.txt";
    QFile file(filePath);

    if(!QDir(".\\data").exists())
    {
        QDir().mkdir(".\\data");
    }

    if(file.exists())
    {
        file.remove();
    }

    if(isFormationValid())
    {
        generationState_ = GENERATED;

        if(!generateFormationData(filePath))
        {
            qCritical() << "Formation Keypad: unable to generate the formation file";
            generationState_ = NOT_GENERATED_INVALID;
        }
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
