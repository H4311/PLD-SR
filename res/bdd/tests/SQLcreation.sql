CREATE TABLE capteurs (id INTEGER PRIMARY KEY, type INTEGER, numeroCapteur INTEGER)

CREATE TABLE mesures (id INTEGER PRIMARY KEY, idCapteur INTEGER, timestamp INTEGER, typeMesure INTEGER, mesure REAL, FOREIGN KEY(idCapteur) REFERENCES capteurs(id))

SELECT * FROM sqlite_master
