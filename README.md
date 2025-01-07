# TP5 Qt : Communication avec une BDD MySQL

Ce projet montre comment utiliser Qt pour créer une interface graphique dynamique permettant de communiquer avec une base de données MySQL sous Linux.

## Objectifs pédagogiques

- Configurer une application Qt avec un accès MySQL sous Linux.
- Créer une interface utilisateur dynamique pour lire et modifier les données d'une base MySQL.

## Sommaire

1. [Création de la base de données](#1-création-de-la-base-de-données)
2. [Accès à la BDD](#2-accès-à-la-bdd)
3. [Affichage graphique](#3-affichage-graphique)
4. [Configuration Qt et MySQL sous Ubuntu](#4-configuration-qt-et-mysql-sous-ubuntu)

---

## 1. Création de la base de données

### Créez une base de données MySQL :

Utilisez la ligne de commande MySQL ou un outil comme MySQL Workbench.

### Ajoutez une table :

Table `jeu` avec :

- Une clé primaire `id` (int).
- Colonnes : `Nom` (varchar), `club` (varchar), `note` (int).

### Insérez des données :

```sql
INSERT INTO `jeu`(`id`, `Nom`, `club`, `note`) VALUES 
(1, 'Ronaldo', 'Madrid', 5),
(2, 'Griezmann', 'Barca', 4),
(3, 'Messi', 'Paris', 5),
(4, 'Mbappe', 'Paris', 4),
(5, 'Ozil', 'Madrid', 5),
(6, 'Arda Guler', 'Madrid', 4);
```

## 2. Accès à la BDD

### Préparation du projet Qt

Ajoutez les modules nécessaires dans le fichier `.pro` :

```pro
QT += core gui sql
CONFIG += c++17
```
# Connexion à MySQL

### Exemple de code pour se connecter à la base de données :

```cpp
QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
db.setDatabaseName("jeu");
db.setHostName("127.0.0.1");
db.setPort(3306);
db.setUserName("etudiant");
db.setPassword("Passciel2");

if (!db.open()) {
    qDebug() << "Erreur de connexion : " << db.lastError().text();
}
```
# 3. Affichage graphique

## Interface utilisateur

La fenêtre principale contient :
- Un tableau (`QTableWidget`) pour afficher les données de la base de données.
- Des champs de saisie pour modifier les données directement dans l'interface.

---

## Connexion des données à l'interface

Exemple pour remplir le tableau avec les données de la BDD :

```cpp
QTableWidget *tableWidget = new QTableWidget;
tableWidget->setColumnCount(3);
tableWidget->setHorizontalHeaderLabels(QStringList() << "Nom" << "Club" << "Note");

QSqlQuery query("SELECT * FROM jeu");
int row = 0;
while (query.next()) {
    tableWidget->insertRow(row);
    tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(1).toString()));
    tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(2).toString()));
    tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(3).toString()));
    row++;
}
```
# Mise à jour des données

Exemple pour modifier une note dans la base de données via l'interface :

```cpp
QObject::connect(tableWidget, &QTableWidget::cellChanged, [&](int row, int column) {
    if (column == 2) {
        QString nom = tableWidget->item(row, 0)->text();
        int newNote = tableWidget->item(row, column)->text().toInt();

        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE jeu SET note = :note WHERE Nom = :nom");
        updateQuery.bindValue(":note", newNote);
        updateQuery.bindValue(":nom", nom);
        updateQuery.exec();
    }
});
```
# 4. Configuration Qt et MySQL sous Ubuntu

## Installez les dépendances

```bash
sudo apt update
sudo apt install libmysqlclient-dev
```
## Assurez la disponibilité du pilote MySQL

Le pilote MySQL est inclus avec Qt si les dépendances sont correctement configurées.

---

# Structure du projet

```bash
TP_Qt_MySQL/
├── widget.ui       # Interface graphique
├── widget.h        # Classe Widget (déclarations)
├── widget.cpp      # Classe Widget (implémentations)
└── main.cpp        # Point d’entrée du programme
```
