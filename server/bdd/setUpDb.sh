#!/bin/sh

echo "Création de la bdd. Mot de passe root requis."
mysql -u root -p < creationDB.sql
echo "Création de l'utilisateur. Mot de passe root requis."
mysql -u root -p < createUser.sql
echo "Création des tables. Mot de passe rithm requis."
mysql -u rithm -p pld < createTables.sql
echo "Insertion des valeurs dans les tables. Mot de passe rithm requis."
mysql -u rithm -p pld < insertValues.sql
