#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "can_device.h"
#include "setup_page.h"
#include "update_page.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void pushButton_update_clicked(void);
    void pushButton_setting_clicked(void);
    void updata_can_param(void);

private:
    void update_status_label(const def_can& can_para);

    can_device* can_dev;
    Ui::MainWindow *ui;
    QLabel* label_port_status;
    QLabel* label_port_para;

    Setup_page* set_page;
    Update_page* updat_page;

};

#endif // MAINWINDOW_H
