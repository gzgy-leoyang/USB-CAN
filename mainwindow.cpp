#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWindow>

#include "setup_page.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    label_port_para = new QLabel(this);
    label_port_status = new QLabel(this);
    ui->statusBar->addWidget(label_port_para);
    ui->statusBar->addWidget(label_port_status);

    can_dev = new can_device();
    can_dev->open_can_port();
    update_status_label(can_dev->can_para);

    connect(ui->pushButton_update,QPushButton::clicked,this,&pushButton_update_clicked);
    connect(ui->pushButton_setting,QPushButton::clicked,this,&pushButton_setting_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updata_can_param(void)
{
    update_status_label(can_dev->can_para);
}

void MainWindow::
update_status_label(const def_can& can_para)
{
    QStringList str;
    QString strTemp;

    if ( can_para.port_num == 0)
        str.append("CAN0");
    else
        str.append("CAN1");

    strTemp.setNum(can_para.buadrate);
    str.append(strTemp);

    if ( can_para.mode == 0)
        str.append("Normal");
    else
        str.append("Loop");

    if ( can_para.frame_type == 0)
        str.append("Ext");
    else
        str.append("Std");

    if ( can_dev->opened ){
        str.append("[OPEN]");
    } else {
        str.append("[CLOSE]");
    }

    label_port_para->setText(str.join(" | "));
}

void MainWindow::
pushButton_update_clicked(void)
{
    updat_page = new Update_page();
    updat_page->show();
}

void MainWindow::pushButton_setting_clicked(void)
{
    set_page = new Setup_page(can_dev);
    set_page->show();
    connect(set_page,SIGNAL(new_can_para()),this,SLOT(updata_can_param()));
}
