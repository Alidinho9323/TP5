#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtDebug>
#include <QtSql/QSqlQuery>
#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    w.resize(500, 200);

    // crée un QTableWidget pour afficher les résultats
    QTableWidget *tableWidget = new QTableWidget(&w);
    tableWidget->setGeometry(10, 10, 500, 300);  // position et taille du tableau
    tableWidget->setColumnCount(3);  // nombre de colonnes (3 : Nom, Club et Note)
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Nom" << "Club" << "Note");  // en-têtes de colonnes

    // connexion à la base de données MySQL
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("jeu");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("etudiant");
    db.setPassword("Passciel2");

    // vérifie si la connexion est réussie
    if(db.open())
    {
        qDebug() << "vous êtes maintenant connecté à " << db.hostName();

        // exécute la requête SQL pour récupérer les données
        QSqlQuery query;
        query.exec("SELECT * FROM `jeu`");

        int row = 0;
        while (query.next()) {
            QString Nom = query.value(1).toString();  // récupère le Nom (colonne 1)
            QString club = query.value(2).toString(); // récupère le Club (colonne 2)
            int note = query.value(3).toInt();        // récupère la Note (colonne 3)

            // ajouter une nouvelle ligne dans le tableau
            tableWidget->insertRow(row);

            // ajouter les données dans la ligne et les colonnes
            tableWidget->setItem(row, 0, new QTableWidgetItem(Nom));
            tableWidget->setItem(row, 1, new QTableWidgetItem(club));
            tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(note)));  // convertir 'note' en QString

            row++;  // passer à la ligne suivante
            qDebug() << Nom << club << note;
        }
        qDebug() << "requête ok ! :)";

        // connecte l'événement de modification de cellule (lorsque l'utilisateur modifie la note)
        QObject::connect(tableWidget, &QTableWidget::cellChanged, [&](int row, int column) {
            if (column == 2) {  // vérifier que la modification concerne la colonne "Note" (colonne 2)
                bool ok;
                // récupérer la nouvelle valeur de la cellule modifiée (la note)
                int newNote = tableWidget->item(row, column)->text().toInt(&ok);

                if (ok) {
                    // si la conversion de la note en entier réussit, mettre à jour la base de données
                    QString nom = tableWidget->item(row, 0)->text();
                    QSqlQuery updateQuery;
                    updateQuery.prepare("UPDATE jeu SET note = :note WHERE Nom = :nom");
                    updateQuery.bindValue(":note", newNote);
                    updateQuery.bindValue(":nom", nom);  // identifier le joueur par son nom
                    if (updateQuery.exec()) {
                        qDebug() << "note mise à jour pour " << nom << ": " << newNote << " étoiles.";
                    } else {
                        // si l'exécution de la requête échoue, afficher un message d'erreur
                        qDebug() << "erreur lors de la mise à jour de la note pour " << nom;
                        QMessageBox::critical(&w, "Erreur", "Échec de la mise à jour de la base de données.");
                    }
                } else {
                    // si la conversion échoue (si la note n'est pas un entier valide), afficher une erreur
                    QMessageBox::critical(&w, "Erreur", "La note doit être un nombre entier.");
                }
            }
        });

    }
    else
    {
        // si la connexion échoue, afficher un message d'erreur
        qDebug() << "la connexion a échoué, désolé";
    }

    w.show();
    return a.exec();
}
