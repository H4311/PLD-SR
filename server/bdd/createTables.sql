USE pld;

DROP TABLE IF EXISTS actionneurs, actionneurSujet, pieces, patients, mesures, capteurs ;

CREATE TABLE actionneurs (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	type INTEGER
);

CREATE TABLE actionneurSujet (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	nom VARCHAR(32),
	description VARCHAR(64),
	isGlobal BOOLEAN,
	idSujet INTEGER
);

CREATE TABLE pieces (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	nom VARCHAR(32),
	description VARCHAR(64)
);

CREATE TABLE patients (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	nom VARCHAR(32),
	isMan BOOLEAN,
	raisonHospitalisation VARCHAR(32),
	idPiece INTEGER,
	FOREIGN KEY (idPiece) REFERENCES pieces (id)
);

CREATE TABLE capteurs (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	type INTEGER,
	numeroCapteur INTEGER,
	isGlobal BOOLEAN,
	idSujet INTEGER,
	UNIQUE (type, numeroCapteur),
	FOREIGN KEY (idSujet) REFERENCES patients (id) 
);

CREATE TABLE mesures (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	idCapteur INTEGER,
	time BIGINT,
	typeMesure INTEGER,
	mesure REAL,
	FOREIGN KEY (idCapteur) REFERENCES capteurs (id)
);
