#!/bin/bash

echo "Suppression des serveurs et ssh..."
for line in $(cat pids); do
    kill "$line"
done
echo "Arrêt de MySQL..."
sudo service mysql stop
#echo "Suppression du fichier de PIDs..."
#rm pids
echo "Everything is OK."
