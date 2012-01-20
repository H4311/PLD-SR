CREATE TABLE capteurs (id INTEGER PRIMARY KEY, type INTEGER)

CREATE TABLE enocean (capteur INTEGER, timestamp INTEGER, mesure INTEGER)

CREATE TABLE sunspot (capteur INTEGER, timestamp INTEGER, temperature REAL, luminosite, REAL, accelerometre REAL)

CREATE TABLE rss (capteur INTEGER, timestamp INTEGER, temperature REAL, humidite REAL, date INTEGER, estPrevision INTEGER)

SELECT * FROM sqlite_master
