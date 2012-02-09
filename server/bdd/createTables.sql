USE pld;

DROP TABLE IF EXISTS capteurs, mesures, pieces, patients, actionneurs, actionneurSujet;

CREATE TABLE capteurs (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	type INTEGER,
	numeroCapteur INTEGER,
	idPatient INTEGER,
	isGlobal BOOLEAN,
	idSujet INTEGER,
	UNIQUE (type, numeroCapteur),
	FOREIGN KEY (idPatient) REFERENCES patients (id) 
);

CREATE TABLE mesures (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	idCapteur INTEGER,
	time BIGINT,
	typeMesure INTEGER,
	mesure REAL,
	FOREIGN KEY (idCapteur) REFERENCES capteurs (id)
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
