#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "situationdata.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    situation = new SituationData(ui->situationView);

    //TODO
//    DisplayableObjectType obj;
//    for(int i=0; i< 3; i++)
//    {
//        obj.setPosition({100, (i+1)*64, i*45.0});
//        if(i == 0)
//        {
//            obj.setPixmapFilename("C:\\Users\\Kasper\\Desktop\\OKNO\\ZCpp\\WycieczkaRobotow\\pixmaps\\leader.png");
//            obj.setPixmapDimensions({48, 48});
//        }
//        else
//        {
//            obj.setPixmapFilename("C:\\Users\\Kasper\\Desktop\\OKNO\\ZCpp\\WycieczkaRobotow\\pixmaps\\troop.png");
//            obj.setPixmapDimensions({32, 32});
//        }
//        situation->addObject(i, obj);
//    }
}

MainWindow::~MainWindow()
{
    delete situation;
    delete ui;
}
