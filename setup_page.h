#ifndef SETUP_PAGE_H
#define SETUP_PAGE_H

#include <QWidget>
#include "can_device.h"

namespace Ui {
class Setup_page;
}

class Setup_page : public QWidget
{
    Q_OBJECT

public:
    explicit Setup_page(QWidget *parent = 0);
    Setup_page(can_device* can_dev,QWidget *parent = 0);
    ~Setup_page();

private:
    Ui::Setup_page *ui;

    void init_list(void);
    can_device* device;

public slots:
    void port_num_changed(int index);
    void buadrate_changed(int index);
    void frame_type_changed(int index);
    void mode_changed(int index);
    void setting_btmClicked();

signals:
    void new_can_para();
};

#endif // SETUP_PAGE_H
