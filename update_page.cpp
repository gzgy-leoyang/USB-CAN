#include "update_page.h"
#include "ui_update_page.h"

#include "src_file.h"

Update_page::Update_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Update_page)
{
    ui->setupUi(this);
    connect(ui->pushButton_loadFile,SIGNAL(clicked(bool)),this,SLOT(loading_file()));
}

Update_page::~Update_page()
{
    delete ui;
}

void Update_page::
loading_file()
{
    Src_file* src = new Src_file(this);
    src->extraFile("tt.s19.txt");
}
