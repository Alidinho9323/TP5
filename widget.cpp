#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)  // constructeur de la classe Widget, parent est l'objet QWidget principal
    , ui(new Ui::Widget)  // initialisation de l'interface utilisateur (UI)
{
    ui->setupUi(this);  // configure l'interface utilisateur à partir du fichier .ui
}

Widget::~Widget()
{
    delete ui;  // libère la mémoire allouée pour l'interface utilisateur (UI)
}
