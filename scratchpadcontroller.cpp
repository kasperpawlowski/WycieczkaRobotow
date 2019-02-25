#include <QDesktopWidget>
#include <QVBoxLayout>
#include "scratchpadcontroller.h"

ScratchpadController::ScratchpadController(QWidget *parent) :
    QWidget(parent), generationState_(NOT_GENERATED_YET)
{
    // calculate the size of a widget
    int widget_size = int(0.45*QDesktopWidget().screenGeometry(this).height());
    setFixedSize(widget_size, widget_size);

    scratchpad_   = new Scratchpad(this);
    acceptButton_ = new QPushButton(this);
    clearButton_  = new QPushButton("Clear", this);

    QVBoxLayout *controller_layout = new QVBoxLayout(this);
    controller_layout->addWidget(scratchpad_);
    controller_layout->addWidget(acceptButton_);
    controller_layout->addWidget(clearButton_);

    connect(acceptButton_, SIGNAL(clicked()), this, SLOT(acceptButtonClicked()));
    connect(clearButton_, SIGNAL(clicked()), this, SLOT(clearButtonClicked()));
    connect(scratchpad_, SIGNAL(mouseCorrectReleaseEvent()), this, SLOT(newDrawingAppeared()));
    refreshAcceptButtonState();
}

void ScratchpadController::acceptButtonClicked()
{
    if(scratchpad_->isDrawingValid())
    {
        generationState_ = GENERATED;
        scratchpad_->generatePathData();
    }
    else
    {
        generationState_ = NOT_GENERATED_INVALID;
    }
    refreshAcceptButtonState();
}

void ScratchpadController::clearButtonClicked()
{
    scratchpad_->clearScratchpad();
    generationState_ = NOT_GENERATED_YET;
    refreshAcceptButtonState();
}

void ScratchpadController::newDrawingAppeared()
{
    // when new path drawn assume that the new file is meant to be generated
    generationState_ = NOT_GENERATED_YET;
    refreshAcceptButtonState();
}

void ScratchpadController::refreshAcceptButtonState()
{
    switch(generationState_)
    {
        case NOT_GENERATED_YET:
            acceptButton_->setText("Accept (path data not generated)");
            acceptButton_->setStyleSheet("");
            break;
        case NOT_GENERATED_INVALID:
            acceptButton_->setText("Accept (nothing drawn yet)");
            acceptButton_->setStyleSheet("background-color: rgb(255, 0, 0); color: rgb(0, 0, 0)");
            break;
        case GENERATED:
            acceptButton_->setText("Accept (path data generated)");
            acceptButton_->setStyleSheet("background-color: rgb(0, 255, 0); color: rgb(0, 0, 0)");
            break;
    }
}
