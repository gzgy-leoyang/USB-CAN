#ifndef UPDATE_PAGE_H
#define UPDATE_PAGE_H

#include <QWidget>

namespace Ui {
class Update_page;
}

class Update_page : public QWidget
{
    Q_OBJECT

public:
    explicit Update_page(QWidget *parent = 0);
    ~Update_page();


public slots:
    void loading_file(void);
private:
    Ui::Update_page *ui;
};

#endif // UPDATE_PAGE_H
