USE pld;

DELETE FROM alertes;
DELETE FROM regleCapteur;
DELETE FROM regleActionneur;
DELETE FROM regles;
DELETE FROM actionneurs;
DELETE FROM actionneurSujet;
DELETE FROM pieces;
DELETE FROM patients;
DELETE FROM mesures;
DELETE FROM capteurs;

INSERT INTO actionneurs(numeroActionneur, type)
VALUES(1, 0x1070901);
INSERT INTO actionneurs (numeroActionneur, type) VALUES (1337, 42);

INSERT INTO pieces(id, nom, description)
VALUES(1, "Salle 1", "Chambre 1"),
	  (2, "Salle 2", "Chambre 2");

INSERT INTO patients(id, nom, isMan, raisonHospitalisation, idPiece)
VALUES (1, "Lhaache", false, "Changement de sexe", 1),
	   (2, "Benjamin", true, "Dédoublage de personnalité", 2),
	   (3, "Tibalt", true, "Découpage des pieds gelés", 1),
	   (4, "Benjamin", true, "Dédoublage de personnalité", 1),
	   (5, "Jeremy", true, "Déprime ordonnanceur", 1),
	   (6, "Dan", true, "Chef de projet PLD SI... Franssement, c est ssaud, mon frère !", 2);

INSERT INTO regles (id, nom, createsAlert) VALUES (100, 'chauffageON', true);
INSERT INTO regles (id, nom, createsAlert) VALUES (101, 'chauffageOFF', true);

INSERT INTO regleCapteur (idRegle, idCapteur, debutIntervalle, finIntervalle) VALUES ((SELECT id FROM regles WHERE nom = 'chauffageON'), 1, -10, 18.5);
INSERT INTO regleCapteur (idRegle, idCapteur, debutIntervalle, finIntervalle) VALUES ((SELECT id FROM regles WHERE nom = 'chauffageOFF'), 1, 18.5, 50);

INSERT INTO regleActionneur (idRegle, idActionneur, valeur, isActive) VALUES ((SELECT id FROM regles WHERE nom = 'chauffageOFF'), 1, 123456789, true);

INSERT INTO capteurs(id, type, numeroCapteur, isGlobal, idSujet)
VALUES (1, 0x0070205, 42, true, 1),
	   (2, 0x0070205, 1337, false, 2);

INSERT INTO mesures(id, idCapteur, time, typeMesure, mesure)
VALUES (1, 1, 1328817902000, 3, 36),
	   (2, 1, 1328818243000, 3, 39),
	   (3, 2, 1328824670000, 3, 37),
	   (4, 2, 1399999999999, 3, 1337);
	   
INSERT INTO alertes(time, idRegle) VALUES (1, 100);
INSERT INTO alertes(time, idRegle) VALUES (10000000000, 101);
INSERT INTO alertes(time, idRegle) VALUES (100000000000000, 100);
INSERT INTO alertes(time, idRegle) VALUES (1000000000000000, 101);
