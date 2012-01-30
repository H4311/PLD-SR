USE pld;

DROP TABLE IF EXISTS capteurs;

CREATE TABLE capteurs (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	type INTEGER,
	numeroCapteur INTEGER
);

DROP TABLE IF EXISTS mesures;


CREATE TABLE mesures (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	idCapteur INTEGER,
	time TIMESTAMP,
	typeMesure INTEGER,
	mesure REAL,
	FOREIGN KEY (idCapteur) REFERENCES capteurs (id)
);
