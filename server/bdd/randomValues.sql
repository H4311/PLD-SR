USE pld;

DELETE FROM mesures;
DELETE FROM capteurs;
DELETE FROM patients;
DELETE FROM pieces;
DELETE FROM actionneurs;

INSERT INTO actionneurs(id, type)
VALUES(1, 0x1070901);

INSERT INTO pieces(id, nom, description)
VALUES(1, "Salle 1", "Chambre 1"),
	  (2, "Salle 2", "Chambre 2");

INSERT INTO patients(id, nom, isMan, raisonHospitalisation, idPiece)
VALUES (1, "Lhaache", false, "Changement de sexe", 1),
	   (2, "Benjamin", true, "Dédoublage de personnalité", 2),
	   (3, "Tibalt", true, "Découpage des pieds gelés", 1),
	   (4, "Benjamin", true, "Dédoublage de personnalité", 1),
	   (5, "Jeremy", true, "Déprime ordonnanceur", 1),
	   (6, "Dan", true, "Chef de projet PLD SI... Franssement, c'est ssaud, mon frère !", 2);

-- INSERT INTO actionneurSujet(idd, nom, description, isGlobal, idSujet) VALUES ()

INSERT INTO capteurs(id, type, numeroCapteur, isGlobal, idSujet)
VALUES (1, 0x0070205, 42, true, 1),
	   (2, 0x0070205, 1337, false, 2);

INSERT INTO mesures(id, idCapteur, time, typeMesure, mesure)
VALUES (1, 1, 1328817902000, 3, 36),
	   (2, 1, 1328818243000, 3, 39),
	   (3, 2, 1328824670000, 3, 37);
