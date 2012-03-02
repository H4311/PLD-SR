USE pld;

DROP TABLE IF EXISTS murs, 
	alertes, 
	regleActionneur, 
	regleCapteur, 
	regles, 
	mesures, 
	capteurs, 
	patients, 
	pieces, 
	actionneurSujet, 
	actionneurs ;
-- regleEvent, events ?

CREATE TABLE actionneurs (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	numeroActionneur INTEGER UNSIGNED,
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
	raisonHospitalisation VARCHAR(64),
	idPiece INTEGER,
	FOREIGN KEY (idPiece) REFERENCES pieces (id)
);

CREATE TABLE capteurs (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	type INTEGER,
	numeroCapteur INTEGER UNSIGNED,
	isGlobal BOOLEAN,
	idSujet INTEGER,
	UNIQUE (type, numeroCapteur)
);

CREATE TABLE mesures (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	idCapteur INTEGER,
	time BIGINT,
	typeMesure INTEGER,
	mesure REAL,
	FOREIGN KEY (idCapteur) REFERENCES capteurs (id)
);

-- Moteur d'inférence

CREATE TABLE regles (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	nom VARCHAR(32),
	createsAlert BOOLEAN,
	UNIQUE(nom)
);

CREATE TABLE regleCapteur (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	idRegle INTEGER,
	idCapteur INTEGER,
	typeMesure INTEGER NOT NULL,
	debutIntervalle REAL,
	finIntervalle REAL,
	FOREIGN KEY (idRegle) REFERENCES regles (id),
	FOREIGN KEY (idCapteur) REFERENCES capteurs (id)
);

CREATE TABLE regleActionneur (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	idRegle INTEGER,
	idActionneur INTEGER,
	valeur REAL,
	isActive BOOLEAN,
	FOREIGN KEY (idRegle) REFERENCES regles (id),
	FOREIGN KEY (idActionneur) REFERENCES actionneurs (id)
);

CREATE TABLE alertes (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	time BIGINT,
	idRegle INTEGER,
	FOREIGN KEY (idRegle) REFERENCES regles (id)
);

-- Plan de l'hopital

CREATE TABLE murs (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	idPiece INTEGER,
	x1 INTEGER,
	y1 INTEGER,
	x2 INTEGER,
	y2 INTEGER,
	ordre INTEGER,
	isPorte BOOLEAN,
	FOREIGN KEY (idPiece) REFERENCES pieces (id)
);
