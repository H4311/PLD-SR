USE pld;

DROP TABLE IF EXISTS capteurs;

CREATE TABLE capteurs (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	type INTEGER,
	numeroCapteur INTEGER,
	UNIQUE (type, numeroCapteur) 
);

DROP TABLE IF EXISTS mesures;


CREATE TABLE mesures (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	idCapteur INTEGER,
	time BIGINT,
	typeMesure INTEGER,
	mesure REAL,
	FOREIGN KEY (idCapteur) REFERENCES capteurs (id)
);
