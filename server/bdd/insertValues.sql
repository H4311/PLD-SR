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
DELETE FROM murs;

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

INSERT INTO pieces(nom) VALUES ('Ch111');
INSERT INTO pieces(nom) VALUES ('Ch112');
INSERT INTO pieces(nom) VALUES ('Ch113');
INSERT INTO pieces(nom) VALUES ('Ch114');
INSERT INTO pieces(nom) VALUES ('Ch115');
INSERT INTO pieces(nom) VALUES ('Ch116');
INSERT INTO pieces(nom) VALUES ('Ch117');
INSERT INTO pieces(nom) VALUES ('Ch118');
INSERT INTO pieces(nom) VALUES ('Ch119');
INSERT INTO pieces(nom) VALUES ('Ch120');
INSERT INTO pieces(nom) VALUES ('Ch121');
INSERT INTO pieces(nom) VALUES ('Ch122');
INSERT INTO pieces(nom) VALUES ('Bl11');
INSERT INTO pieces(nom) VALUES ('Bl12');
INSERT INTO pieces(nom) VALUES ('Dep11');

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch111'), 10, 10, 100, 100, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch111'), 100, 10, 100, 100, 2, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch111'), 100, 40, 100, 60, 3, true);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch111'), 100, 60, 100, 100, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch111'), 100, 100, 10, 100, 5, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch111'), 10, 100, 10, 10, 6, false);


INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch112'), 10, 100, 100, 100, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch112'), 100, 100, 100, 150, 2, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch112'), 100, 150, 100, 170, 3, true);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch112'), 100, 170, 100, 240, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch112'), 100, 240, 10, 240, 5, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch112'), 10, 240, 10, 100, 6, false);

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch113'), 10, 240, 100, 240, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch113'), 100, 240, 100, 270, 2, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch113'), 100, 270, 100, 290, 3, true);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch113'), 100, 290, 100, 370, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch113'), 100, 370, 10, 370, 5, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch113'), 10, 370, 10, 240, 6, false);

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch114'), 130, 10, 270, 10, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch114'), 270, 10, 270, 100, 2, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch114'), 270, 100, 130, 100, 3, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch114'), 130, 100, 130, 60, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch114'), 130, 40, 130, 10, 6, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch114'), 130, 60, 130, 40, 5, true);

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch115'), 130, 130, 300, 130, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch115'), 300, 130, 300, 240, 2, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch115'), 300, 240, 130, 240, 3, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch115'), 130, 240, 130, 180, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch115'), 130, 160, 130, 130, 6, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch115'), 130, 180, 130, 160, 5, true);

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch116'), 130, 240, 300, 240, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch116'), 300, 240, 300, 340, 2, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch116'), 300, 340, 130, 340, 3, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch116'), 130, 340, 130, 300, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch116'), 130, 280, 130, 240, 6, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch116'), 130, 300, 130, 280, 5, true);

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch117'), 360, 10, 530, 10, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch117'), 360, 100, 360, 10, 2, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch117'), 530, 100, 360, 100, 3, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch117'), 530, 60, 530, 100, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch117'), 530, 10, 530, 40, 6, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch117'), 530, 40, 530, 60, 5, true);

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch118'), 330, 130, 530, 130, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch118'), 330, 240, 330, 130, 2, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch118'), 530, 240, 330, 240, 3, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch118'), 530, 180, 530, 240, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch118'), 530, 130, 530, 160, 6, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch118'), 530, 160, 530, 180, 5, true);

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch119'), 330, 240, 530, 240, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch119'), 330, 340, 330, 240, 2, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch119'), 530, 340, 330, 340, 3, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch119'), 530, 300, 530, 340, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch119'), 530, 240, 530, 280, 6, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch119'), 530, 280, 530, 300, 5, true);

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch120'), 560, 10, 660, 10, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch120'), 560, 40, 560, 10, 6, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch120'), 560, 60, 560, 40, 5, true);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch120'), 560, 100, 560, 60, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch120'), 660, 100, 560, 100, 3, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch120'), 660, 10, 660, 100, 2, false);

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch121'), 560, 100, 660, 100, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch121'), 560, 150, 560, 100, 6, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch121'), 560, 170, 560, 150, 5, true);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch121'), 560, 240, 560, 170, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch121'), 660, 240, 560, 240, 3, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch121'), 660, 100, 660, 240, 2, false);

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch122'), 560, 240, 660, 240, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch122'), 560, 280, 560, 240, 6, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch122'), 560, 300, 560, 280, 5, true);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch122'), 560, 370, 560, 300, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch122'), 660, 370, 560, 370, 3, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch122'), 660, 240, 660, 370, 2, false);

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl11'), 10, 370, 110, 370, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl11'), 130, 370, 300, 370, 3, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl11'), 300, 370, 300, 380, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl11'), 300, 400, 300, 420, 6, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl11'), 300, 420, 260, 420, 7, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl11'), 260, 420, 260, 440, 8, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl11'), 260, 440, 10, 400, 9, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl11'), 10, 400, 10, 370, 10, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl11'), 110, 370, 130, 370, 2, true);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl11'), 300, 380, 300, 400, 5, true);

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl12'), 330, 380, 330, 370, 10, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl12'), 330, 400, 330, 380, 9, true);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl12'), 330, 420, 330, 400, 8, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl12'), 370, 420, 370, 420, 7, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl12'), 370, 440, 370, 420, 6, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl12'), 660, 400, 370, 440, 5, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl12'), 660, 370, 660, 400, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl12'), 430, 370, 660, 370, 3, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl12'), 410, 370, 430, 370, 2, true);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl12'), 330, 370, 410, 370, 1, false);

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Dep11'), 270, 10, 360, 10, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Dep11'), 360, 10, 360, 100, 2, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Dep11'), 360, 100, 330, 100, 3, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Dep11'), 300, 100, 270, 100, 5, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Dep11'), 270, 100, 270, 10, 6, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Dep11'), 330, 100, 300, 100, 4, true);
