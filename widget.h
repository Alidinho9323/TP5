#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>  // inclut la classe QWidget pour créer des interfaces utilisateur

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;  // déclaration de la classe Widget générée par le fichier .ui
}
QT_END_NAMESPACE

// Définition de la classe Widget, qui hérite de QWidget
class Widget : public QWidget
{
    Q_OBJECT  // macro pour permettre l'utilisation de fonctionnalités Qt (comme les signaux et les slots)

public:
    // constructeur de la classe Widget, prend un paramètre parent (par défaut nullptr)
    explicit Widget(QWidget *parent = nullptr);
    // destructeur de la classe Widget
    ~Widget();

private:
    Ui::Widget *ui;  // pointeur vers l'interface utilisateur (UI) générée par Qt Designer
};

#endif // WIDGET_H
