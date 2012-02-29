#!/bin/sh

echo "Création de la bdd. Mot de passe root requis."
mysql -u root -p < creationDB.sql
echo "Création de l'utilisateur. Mot de passe root requis."
mysql -u root -p < createUser.sql
mysql -u rithm -prithm pld < createTables.sql
mysql -u rithm -prithm pld < insertValues.sql
