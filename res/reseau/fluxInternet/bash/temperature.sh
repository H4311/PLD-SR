#!/bin/sh

curl -s http://www.google.fr/ig/api?weather=`echo $1 | sed "s/ /%20/g"` | LANG=UTF-8 sed "s/.*temp_c data=\"\([0-9]*\).*/\1/" > temperature.today

echo "La température actuelle à $1 est de `cat temperature.today` degres celcius."
