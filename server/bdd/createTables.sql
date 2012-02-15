USE pld;

DROP TABLE IF EXISTS alertes, regleCapteur, regles, regleEvent, events, actionneurs, actionneurSujet, pieces, patients, mesures, capteurs ;

CREATE TABLE actionneurs (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	numeroActionneur INTEGER,
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

CREATE TABLE events (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	idActionneur INTEGER,
	valeur REAL,
	FOREIGN KEY (idActionneur) REFERENCES actionneurs (id)
);

CREATE TABLE regles (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	nom VARCHAR(32),
	createsAlert BOOLEAN
);

CREATE TABLE regleEvent (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	idRegle INTEGER,
	idEvent INTEGER,
	FOREIGN KEY (idEvent) REFERENCES events (id),
	FOREIGN KEY (idRegle) REFERENCES regles (id)
);

CREATE TABLE regleCapteur (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	idRegle INTEGER,
	idCapteur INTEGER,
	debutIntervalle REAL,
	finIntervalle REAL,
	FOREIGN KEY (idRegle) REFERENCES regles (id),
	FOREIGN KEY (idCapteur) REFERENCES capteurs (id)
);

CREATE TABLE alertes (
	id INTEGER PRIMARY KEY AUTO_INCREMENT,
	time BIGINT,
	idRegle INTEGER,
	FOREIGN KEY (idRegle) REFERENCES regles (id)
);
