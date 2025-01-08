# TP5 Qt : Communication avec une BDD MySQL

Ce projet illustre comment utiliser Qt pour créer une interface graphique interactive et communiquer avec une base de données MySQL sous Linux.

## Objectifs

- Configurer une application Qt pour accéder à une base MySQL.
- Créer une interface utilisateur qui permet de lire et modifier les données de manière simple.

## Table des matières

1. [Préparation de la base de données](#1-préparation-de-la-base-de-données)
2. [Connexion à la base de données](#2-connexion-à-la-base-de-données)
3. [Création de l'interface graphique](#3-création-de-linterface-graphique)
4. [Configuration de Qt et MySQL](#4-configuration-de-qt-et-mysql)

---

## 1. Préparation de la base de données

Avant de commencer, configure une base de données MySQL. Voici les étapes :

### Crée la base de données et la table

1. Connecte-toi à MySQL depuis le terminal ou un outil comme MySQL Workbench.
2. Exécute les commandes suivantes pour créer une base de données et une table :

```sql
CREATE DATABASE jeu;
USE jeu;

CREATE TABLE jeu (
    id INT AUTO_INCREMENT PRIMARY KEY,
    Nom VARCHAR(50),
    Club VARCHAR(50),
    Note INT
);
```
### Insère des données d'exemple

Ajoute des données pour tester l'application :

```sql
INSERT INTO jeu (Nom, Club, Note) VALUES
('Ronaldo', 'Madrid', 5),
('Griezmann', 'Barca', 4),
('Messi', 'Paris', 5),
('Mbappe', 'Paris', 4),
('Ozil', 'Madrid', 5),
('Arda Guler', 'Madrid', 4);
```
## 2. Connexion à la base de données

### Préparation du projet Qt

1. Crée un nouveau projet Qt.
2. Ajoute les modules nécessaires dans le fichier `.pro` :

```pro
QT += core gui sql
CONFIG += c++17
```
### Code de connexion

Ajoute ce code dans ton projet pour te connecter à la base de données :

```cpp
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
db.setDatabaseName("jeu");
db.setHostName("127.0.0.1");
db.setPort(3306);
db.setUserName("etudiant");
db.setPassword("Passciel2");

if (!db.open()) {
    qDebug() << "Erreur de connexion : " << db.lastError().text();
} else {
    qDebug() << "Connexion réussie à la base de données.";
}
```
Teste ce code pour vérifier que la connexion fonctionne.

## 3. Création de l'interface graphique

### Ajoute un tableau pour afficher les données

Dans l'interface utilisateur, ajoute un `QTableWidget` et utilise ce code pour afficher les données de la base de données :

```cpp
QTableWidget *tableWidget = new QTableWidget;
tableWidget->setColumnCount(3);
tableWidget->setHorizontalHeaderLabels(QStringList() << "Nom" << "Club" << "Note");

QSqlQuery query("SELECT * FROM jeu");
int row = 0;
while (query.next()) {
    tableWidget->insertRow(row);
    tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("Nom").toString()));
    tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("Club").toString()));
    tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("Note").toString()));
    row++;
}
```
### Permet de modifier les données

Ajoute une fonctionnalité pour modifier les notes directement dans le tableau :

```cpp
QObject::connect(tableWidget, &QTableWidget::cellChanged, [&](int row, int column) {
    if (column == 2) {  // La colonne "Note"
        QString nom = tableWidget->item(row, 0)->text();
        int newNote = tableWidget->item(row, column)->text().toInt();

        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE jeu SET Note = :note WHERE Nom = :nom");
        updateQuery.bindValue(":note", newNote);
        updateQuery.bindValue(":nom", nom);
        if (!updateQuery.exec()) {
            qDebug() << "Erreur lors de la mise à jour : " << updateQuery.lastError().text();
        }
    }
});
```
## 4. Configuration de Qt et MySQL

### Installe les dépendances sur Ubuntu

Assure-toi que les bibliothèques nécessaires sont installées :

```bash
sudo apt update
sudo apt install libmysqlclient-dev
```
### Vérifie la disponibilité du pilote MySQL

Le pilote MySQL est inclus avec Qt si les dépendances sont correctement configurées. Si tu rencontres des problèmes, vérifie que Qt a été compilé avec le support MySQL.

---

### Structure du projet

Voici la structure typique du projet :

```bash
TP_Qt_MySQL/
├── widget.ui       # Interface graphique
├── widget.h        # Déclarations de la classe Widget
├── widget.cpp      # Implémentation de la classe Widget
└── main.cpp        # Point d'entrée du programme
```
