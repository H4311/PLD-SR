#!/bin/bash

if [ $# -ne 1 ]
then
	echo "Usage :"
	echo "$0 userName"
	exit
fi

echo "Lancement de MySQL..."
sudo service mysql start
echo "Connexion au serveur EnOcean..."
ssh -f -L 6543:134.214.105.28:5000 -N $1@iftpserv2.insa-lyon.fr
echo "Lancement du serveur C++..."
./controller/Debug/EnOcean2 > enocean.log &
echo "Lancement des serveurs Web et REST..."
(cd web/ && (node start.js > ../rithm.log 2> ../rithm.log &))
echo "L'ensemble des composants est lancé... Sauvegarde des PIDs..."
ps aux | grep "node start" | grep -v grep | cut -d" " -f 6 >> pids
ps aux | grep "ssh -f -L 6543" | grep -v grep | cut -d" " -f 6 >> pids
ps aux | grep "EnOcean2" | grep -v grep | cut -d" " -f 6 >> pids
echo "Enjoy!"
