#!/bin/sh

if [ -e test.db ]; then
	echo "# Suppression de la base existante";
	rm test.db;
fi;

echo "# Création des nouvelles tables";
cat SQLcreation.sql | while read i;
do
	sqlite3 test.db "$i";
done;
