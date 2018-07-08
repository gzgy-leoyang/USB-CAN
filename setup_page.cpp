#include "setup_page.h"
#include "ui_setup_page.h"

#include <QObject>

#include "can.h"

def_can can_para;

Setup_page::Setup_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setup_page)
{
    ui->setupUi(this);
}

Setup_page::Setup_page(can_device* can_dev,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setup_page)
{
    device = can_dev;

    can_para.port_num = device->can_para.port_num;
    can_para.buadrate = device->can_para.buadrate;
    can_para.frame_type = device->can_para.frame_type;
    can_para.mode = device->can_para.mode;

    ui->setupUi(this);

    QStringList buadrate_list;
    buadrate_list += "125000";
    buadrate_list += "250000";
    buadrate_list += "500000";
    ui->comboBox_buadrate->addItems(buadrate_list);

    QString strTemp;
    strTemp.setNum(can_para.port_num);
    if( buadrate_list.contains( strTemp )){
        ui->comboBox_buadrate->setCurrentIndex(buadrate_list.indexOf(strTemp));
    }
    connect(ui->comboBox_buadrate, SIGNAL(currentIndexChanged(int)), this, SLOT(buadrate_changed(int)));

    QStringList port_num_list;
    port_num_list += "CAN0";
    port_num_list += "CAN1";
    ui->comboBox_port_num->addItems(port_num_list);
    ui->comboBox_port_num->setCurrentIndex(can_para.port_num);
    connect(ui->comboBox_port_num, SIGNAL(currentIndexChanged(int)), this, SLOT(port_num_changed(int)));

    QStringList frame_type_list;
    frame_type_list += "Extend";
    frame_type_list += "Stand";
    ui->comboBox_frame_type->addItems(frame_type_list);
    ui->comboBox_frame_type->setCurrentIndex(can_para.frame_type);
    connect(ui->comboBox_frame_type, SIGNAL(currentIndexChanged(int)), this, SLOT(frame_type_changed(int)));

    QStringList mode_list;
    mode_list += "Normal";
    mode_list += "Loop";
    ui->comboBox_mode->addItems(mode_list);
    ui->comboBox_mode->setCurrentIndex(can_para.mode);
    connect(ui->comboBox_mode, SIGNAL(currentIndexChanged(int)), this, SLOT(mode_changed(int)));

    connect(ui->pushButton_setting,SIGNAL(clicked(bool)),this,SLOT(setting_btmClicked()));
}

Setup_page::~Setup_page()
{
    delete ui;
}

void Setup_page::
port_num_changed(int index)
{
    can_para.port_num = ui->comboBox_port_num->currentIndex();
}

void Setup_page::
buadrate_changed(int index)
{
    switch(ui->comboBox_buadrate->currentIndex()){
    case 0 :
        can_para.buadrate = 125000 ;
        break;
    case 1 :
        can_para.buadrate = 250000;
        break;
    case 2:
        can_para.buadrate = 500000;
        break;
    default:
        can_para.buadrate = 250000;
        break;
    }
}

void Setup_page::
frame_type_changed(int index)
{
    can_para.frame_type = ui->comboBox_frame_type->currentIndex();}

void Setup_page::
mode_changed(int index)
{
    can_para.mode = ui->comboBox_mode->currentIndex();
}

void Setup_page::
setting_btmClicked()
{
    device->init(can_para);
    emit new_can_para();
    deleteLater();
}

