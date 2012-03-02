USE pld;

SET NAMES 'utf8';

DELETE FROM murs;
DELETE FROM	alertes; 
DELETE FROM	regleActionneur; 
DELETE FROM	regleCapteur; 
DELETE FROM	regles;
DELETE FROM	mesures;
DELETE FROM	capteurs; 
DELETE FROM	patients; 
DELETE FROM	pieces;
DELETE FROM	actionneurSujet; 
DELETE FROM	actionneurs ;

INSERT INTO pieces(id, nom) VALUES (1, 'Ch111');
INSERT INTO pieces(id, nom) VALUES (2, 'Ch112');
INSERT INTO pieces(id, nom) VALUES (3,'Ch113');
INSERT INTO pieces(id, nom) VALUES (4,'Ch114');
INSERT INTO pieces(id, nom) VALUES (5,'Ch115');
INSERT INTO pieces(id, nom) VALUES (6,'Ch116');
INSERT INTO pieces(id, nom) VALUES (7,'Ch117');
INSERT INTO pieces(id, nom) VALUES (8,'Ch118');
INSERT INTO pieces(id, nom) VALUES (9,'Ch119');
INSERT INTO pieces(id, nom) VALUES (10,'Ch120');
INSERT INTO pieces(id, nom) VALUES (11,'Ch121');
INSERT INTO pieces(id, nom) VALUES (12,'Ch122');
INSERT INTO pieces(id, nom) VALUES (13,'Bl11');
INSERT INTO pieces(id, nom) VALUES (14,'Bl12');
INSERT INTO pieces(id, nom) VALUES (15,'Dep11');

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch111'), 10, 10, 100, 10, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch111'), 100, 10, 100, 40, 2, false);
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
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch117'), 360, 100, 360, 10, 6, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch117'), 530, 100, 360, 100, 5, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch117'), 530, 60, 530, 100, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch117'), 530, 10, 530, 40, 2, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch117'), 530, 40, 530, 60, 3, true);

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch118'), 330, 130, 530, 130, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch118'), 330, 240, 330, 130, 6, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch118'), 530, 240, 330, 240, 5, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch118'), 530, 180, 530, 240, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch118'), 530, 130, 530, 160, 2, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch118'), 530, 160, 530, 180, 3, true);

INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch119'), 330, 240, 530, 240, 1, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch119'), 330, 340, 330, 240, 6, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch119'), 530, 340, 330, 340, 5, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch119'), 530, 300, 530, 340, 4, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch119'), 530, 240, 530, 280, 2, false);
INSERT INTO murs(idPiece, x1, y1, x2, y2, ordre, isPorte)
VALUES ((SELECT id FROM pieces WHERE nom = 'Ch119'), 530, 280, 530, 300, 3, true);

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
VALUES ((SELECT id FROM pieces WHERE nom = 'Bl12'), 370, 420, 330, 420, 7, false);
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


INSERT INTO patients(id, nom, isMan, raisonHospitalisation, idPiece)
VALUES (1001, "Arnal", false, "Changement de sexe", (SELECT id FROM pld.pieces WHERE nom="Ch111")),
	   (1002, "Benjamin", true, "D&eacute;doublage de personnalit&eacute;", (SELECT id FROM pld.pieces WHERE nom="Ch111")),
	   (1003, "Tibalt", true, "D&eacute;coupage des pieds gel&eacute;s", (SELECT id FROM pld.pieces WHERE nom="Ch111")),
	   (1004, "Benjamin", true, "D&eacute;doublage de personnalit&eacute;", (SELECT id FROM pld.pieces WHERE nom="Ch112")),
	   (1005, "Jeremy", true, "D&eacute;prime ordonnanceur", (SELECT id FROM pld.pieces WHERE nom="Ch112")),
	   (1006, "Dan", true, "Chef de projet PLD SI... Franssement, c est ssaud, mon fr&eacute;re !", (SELECT id FROM pld.pieces WHERE nom="Ch113")),
	   (1007, "Ren&eacute;e G&eacute;rard", false, "Hypocondrie", (SELECT id FROM pld.pieces WHERE nom="Ch113")),
	   (1008, "Daniel H&eacute;bonne", false, "Chirurgie esth&eacute;tique", (SELECT id FROM pld.pieces WHERE nom="Ch114")),
	   (1009, "J&eacute;r&eacute;my Fasollasi", true, "Op&eacute;ration du tympan droit", (SELECT id FROM pld.pieces WHERE nom="Ch115")),
	   (1010, "Thibalt Lon", false, "Entorse du genou simul&eacute;e", (SELECT id FROM pld.pieces WHERE nom="Ch115")),
	   (1011, "Arnal Ligator", true, "Extraction de dents", (SELECT id FROM pld.pieces WHERE nom="Ch116")),
	   (1012, "Bill At&eacute;ral", true, "Bipolarit&eacute; cervovaculaire", (SELECT id FROM pld.pieces WHERE nom="Ch117")),
	   (1013, "Boule Deun&eacute;geux", true, "Engelures aux doigts", (SELECT id FROM pld.pieces WHERE nom="Ch118")),
	   (1014, "Benjamin Tenancespie", true, "Overdose de SAP", (SELECT id FROM pld.pieces WHERE nom="Ch119")),
	   (1015, "Jeremy Lemeimeslipe", false, "Escar aux fesses", (SELECT id FROM pld.pieces WHERE nom="Ch120")),
	   (1025, "Arnaud Limite", false, "Overdose cocainoique", (SELECT id FROM pld.pieces WHERE nom="Ch121")),
	   (1016, "Thibaut Gausse", true, "Chirurgie esth&eacute;tique", (SELECT id FROM pld.pieces WHERE nom="Ch121")),
	   (1017, "Dan T&eacute;dan", true, "Traumatisme cranien s&eacute;v&eacute;re", (SELECT id FROM pld.pieces WHERE nom="Bl12")),
	   (1018, "J&eacute;remy Sa", true, "Double fracture ouverte du tibia", (SELECT id FROM pld.pieces WHERE nom="Bl11")),
	   (1019, "Benjamin Tenan-Oujam&eacute;", false, "Flemmingite aigue", (SELECT id FROM pld.pieces WHERE nom="Ch116")),
	   (1020, "Arnal Longetoa", true, "MST exotique", (SELECT id FROM pld.pieces WHERE nom="Ch120")),
	   (1021, "Bill Lingoualle", false, "Tourista", (SELECT id FROM pld.pieces WHERE nom="Ch121")),
	   (1022, "Thibaut Coudeukalein", true, "Cote 3-1 f&ecirc;l&eacute;e", (SELECT id FROM pld.pieces WHERE nom="Ch117")),
	   (1023, "Boul Lei", true, "Coma c&eacute;r&eacute;bral", (SELECT id FROM pld.pieces WHERE nom="Ch115")),
	   (1024, "Charlie", true, "En recherche", (SELECT id FROM pld.pieces WHERE nom="Ch119"));

INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (459777,1048599, 1, (SELECT id FROM pld.pieces WHERE nom="Ch111"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (460801,1048600, 1, (SELECT id FROM pld.pieces WHERE nom="Ch111"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (393217,1048601, 1,(SELECT id FROM pld.pieces WHERE nom="Ch111"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (328193,1048602, 1, (SELECT id FROM pld.pieces WHERE nom="Ch111"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (461057,1048603, 1, (SELECT id FROM pld.pieces WHERE nom="Ch111"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (459777,1048604, 1, (SELECT id FROM pld.pieces WHERE nom="Ch114"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (460801,1048605, 1, (SELECT id FROM pld.pieces WHERE nom="Ch114"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (393217,1048606, 1,(SELECT id FROM pld.pieces WHERE nom="Ch114"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (328193,1048607, 1, (SELECT id FROM pld.pieces WHERE nom="Ch114"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (461057,1048608, 1, (SELECT id FROM pld.pieces WHERE nom="Ch114"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (459777,1048609, 1, (SELECT id FROM pld.pieces WHERE nom="Bl11"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (460801,1048610, 1, (SELECT id FROM pld.pieces WHERE nom="Bl11"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (393217,1048611, 1,(SELECT id FROM pld.pieces WHERE nom="Bl11"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (328193,1048612, 1, (SELECT id FROM pld.pieces WHERE nom="Bl11"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (461057,1048613, 1, (SELECT id FROM pld.pieces WHERE nom="Bl11"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (459777,1048614, 1, (SELECT id FROM pld.pieces WHERE nom="Bl12"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (460801,1048615, 1, (SELECT id FROM pld.pieces WHERE nom="Bl12"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (393217,1048616, 1,(SELECT id FROM pld.pieces WHERE nom="Bl12"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (328193,1048617, 1, (SELECT id FROM pld.pieces WHERE nom="Bl12"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (461057,1048618, 1, (SELECT id FROM pld.pieces WHERE nom="Bl12"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (459777,1048619, 1, (SELECT id FROM pld.pieces WHERE nom="Ch112"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (460801,1048620, 1, (SELECT id FROM pld.pieces WHERE nom="Ch112"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (393217,1048621, 1,(SELECT id FROM pld.pieces WHERE nom="Ch112"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (328193,1048622, 1, (SELECT id FROM pld.pieces WHERE nom="Ch112"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (461057,1048623, 1, (SELECT id FROM pld.pieces WHERE nom="Ch112"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (459777,1048624, 1, (SELECT id FROM pld.pieces WHERE nom="Ch113"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (460801,1048625, 1, (SELECT id FROM pld.pieces WHERE nom="Ch113"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (393217,1048626, 1,(SELECT id FROM pld.pieces WHERE nom="Ch113"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (328193,1048627, 1, (SELECT id FROM pld.pieces WHERE nom="Ch113"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (461057,1048628, 1, (SELECT id FROM pld.pieces WHERE nom="Ch113"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (459777,1048629, 1, (SELECT id FROM pld.pieces WHERE nom="Ch115"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (460801,1048630, 1, (SELECT id FROM pld.pieces WHERE nom="Ch115"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (393217,1048631, 1,(SELECT id FROM pld.pieces WHERE nom="Ch115"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (328193,1048632, 1, (SELECT id FROM pld.pieces WHERE nom="Ch115"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (461057,1048633, 1, (SELECT id FROM pld.pieces WHERE nom="Ch115"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (459777,1048634, 1, (SELECT id FROM pld.pieces WHERE nom="Ch116"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (460801,1048635, 1, (SELECT id FROM pld.pieces WHERE nom="Ch116"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (393217,1048636, 1,(SELECT id FROM pld.pieces WHERE nom="Ch116"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (328193,1048637, 1, (SELECT id FROM pld.pieces WHERE nom="Ch116"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (461057,1048638, 1, (SELECT id FROM pld.pieces WHERE nom="Ch116"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (459777,1048639, 1, (SELECT id FROM pld.pieces WHERE nom="Ch117"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (460801,1048640, 1, (SELECT id FROM pld.pieces WHERE nom="Ch117"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (393217,1048641, 1,(SELECT id FROM pld.pieces WHERE nom="Ch117"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (328193,1048642, 1, (SELECT id FROM pld.pieces WHERE nom="Ch117"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (461057,1048643, 1, (SELECT id FROM pld.pieces WHERE nom="Ch117"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (459777,1048644, 1, (SELECT id FROM pld.pieces WHERE nom="Ch118"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (460801,1048645, 1, (SELECT id FROM pld.pieces WHERE nom="Ch118"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (393217,1048646, 1,(SELECT id FROM pld.pieces WHERE nom="Ch118"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (328193,1048647, 1, (SELECT id FROM pld.pieces WHERE nom="Ch118"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (461057,1048648, 1, (SELECT id FROM pld.pieces WHERE nom="Ch118"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (459777,1048649, 1, (SELECT id FROM pld.pieces WHERE nom="Ch119"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (460801,1048650, 1, (SELECT id FROM pld.pieces WHERE nom="Ch119"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (393217,1048651, 1,(SELECT id FROM pld.pieces WHERE nom="Ch119"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (328193,1048652, 1, (SELECT id FROM pld.pieces WHERE nom="Ch119"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (461057,1048653, 1, (SELECT id FROM pld.pieces WHERE nom="Ch119"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (459777,1048654, 1, (SELECT id FROM pld.pieces WHERE nom="Ch120"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (460801,1048655, 1, (SELECT id FROM pld.pieces WHERE nom="Ch120"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (393217,1048656, 1,(SELECT id FROM pld.pieces WHERE nom="Ch120"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (328193,1048657, 1, (SELECT id FROM pld.pieces WHERE nom="Ch120"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (461057,1048658, 1, (SELECT id FROM pld.pieces WHERE nom="Ch120"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (459777,1048659, 1, (SELECT id FROM pld.pieces WHERE nom="Ch121"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (460801,1048660, 1, (SELECT id FROM pld.pieces WHERE nom="Ch121"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (393217,1048661, 1,(SELECT id FROM pld.pieces WHERE nom="Ch121"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (328193,1048662, 1, (SELECT id FROM pld.pieces WHERE nom="Ch121"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (461057,1048663, 1, (SELECT id FROM pld.pieces WHERE nom="Ch121"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (459777,1048664, 1, (SELECT id FROM pld.pieces WHERE nom="Ch122"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (460801,1048665, 1, (SELECT id FROM pld.pieces WHERE nom="Ch122"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (393217,1048666, 1,(SELECT id FROM pld.pieces WHERE nom="Ch122"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (328193,1048667, 1, (SELECT id FROM pld.pieces WHERE nom="Ch122"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (461057,1048668, 1, (SELECT id FROM pld.pieces WHERE nom="Ch122"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (459777,1048669, 1, (SELECT id FROM pld.pieces WHERE nom="Dep11"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (460801,1048670, 1, (SELECT id FROM pld.pieces WHERE nom="Dep11"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (393217,1048671, 1,(SELECT id FROM pld.pieces WHERE nom="Dep11"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (328193,1048672, 1, (SELECT id FROM pld.pieces WHERE nom="Dep11"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (461057,1048673, 1, (SELECT id FROM pld.pieces WHERE nom="Dep11"));

INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001000, 0, 1001);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001001, 0, 1002);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001002, 0, 1003);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001003, 0, 1004);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001004, 0, 1005);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001005, 0, 1006);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001006, 0, 1007);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001007, 0, 1008);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001008, 0, 1009);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001009, 0, 1010);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001010, 0, 1011);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001011, 0, 1012);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001012, 0, 1013);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001013, 0, 1014);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001014, 0, 1015);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001015, 0, 1016);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001016, 0, 1017);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001017, 0, 1018);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001018, 0, 1019);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001019, 0, 1020);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001020, 0, 1021);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001021, 0, 1022);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001022, 0, 1023);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001023, 0, 1024);
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00001024, 0, 1025);

INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x0050201,0x0021CBE3, 1, (SELECT id FROM pld.pieces WHERE nom="Ch111"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x0070801,0x00054A7F, 1, (SELECT id FROM pld.pieces WHERE nom="Ch111"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x0060001,0x0001B596, 1, (SELECT id FROM pld.pieces WHERE nom="Ch111"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x0060001,0x0001B595, 1, (SELECT id FROM pld.pieces WHERE nom="Ch112"));
INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x0070205,0x00893378, 1, (SELECT id FROM pld.pieces WHERE nom="Ch111"));



INSERT INTO actionneurs(numeroActionneur, type ) VALUES (0xff9f1e06, 17105409);

INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001, 0x5620, 0, 1001);
/*INSERT INTO regles (nom, createsAlert) VALUES ('Prise On', true);*/
INSERT INTO regles (nom, createsAlert) VALUES ('Prise Off', true);

/*INSERT INTO regleCapteur (idRegle, idCapteur, typeMesure, debutIntervalle, finIntervalle) VALUES ((SELECT id FROM regles WHERE nom = 'Prise On'), (SELECT id FROM capteurs WHERE numeroCapteur=0x5620 AND type=0x00A0001), 5, 0, 9);*/
INSERT INTO regleCapteur (idRegle, idCapteur, typeMesure, debutIntervalle, finIntervalle) VALUES ((SELECT id FROM regles WHERE nom = 'Prise Off'), (SELECT id FROM capteurs WHERE numeroCapteur=0x5620 AND type=0x00A0001), 5, 10, 1000);

/*INSERT INTO regleActionneur (idRegle, idActionneur, valeur, isActive)
	VALUES ((SELECT id FROM regles WHERE nom = 'Prise On'), (SELECT id FROM actionneurs WHERE numeroActionneur = 0xff9f1e06 AND type = 17105409), 0, true);*/
INSERT INTO regleActionneur (idRegle, idActionneur, valeur, isActive)
	VALUES ((SELECT id FROM regles WHERE nom = 'Prise Off'), (SELECT id FROM actionneurs WHERE numeroActionneur = 0xff9f1e06 AND type = 17105409), 0, false);

INSERT INTO actionneurs(numeroActionneur, type ) VALUES (4288617991, 0x2000010);

INSERT INTO regles (nom, createsAlert) VALUES ('Music On', true);

INSERT INTO regleCapteur (idRegle, idCapteur, typeMesure, debutIntervalle, finIntervalle) VALUES ((SELECT id FROM regles WHERE nom = 'Music On'), (SELECT id FROM capteurs WHERE numeroCapteur=0x0021CBE3 AND type=0x0050201), 2, 0, 48);

INSERT INTO regleActionneur (idRegle, idActionneur, valeur, isActive)
	VALUES ((SELECT id FROM regles WHERE nom = 'Music On'), (SELECT id FROM actionneurs WHERE numeroActionneur = 4288617991 AND type = 0x2000010), 0, true);

/*
INSERT INTO regles (nom, createsAlert) VALUES ('Lumière On', true);
INSERT INTO regles (nom, createsAlert) VALUES ('Lumière Off', true);

INSERT INTO regleCapteur (idRegle, idCapteur, typeMesure, debutIntervalle, finIntervalle) VALUES ((SELECT id FROM regles WHERE nom = 'Lumière On'), (SELECT id FROM capteurs WHERE numeroCapteur=0x00054A7F AND type=0x0070801), 2, 0, 16);
INSERT INTO regleCapteur (idRegle, idCapteur, typeMesure, debutIntervalle, finIntervalle) VALUES ((SELECT id FROM regles WHERE nom = 'Lumière Off'), (SELECT id FROM capteurs WHERE numeroCapteur=0x00054A7F AND type=0x0070801), 2, 32, 48);

INSERT INTO regleActionneur (idRegle, idActionneur, valeur, isActive)
	VALUES ((SELECT id FROM regles WHERE nom = 'Lumière On'), (SELECT id FROM actionneurs WHERE numeroActionneur = 4288617991 AND type = 0x2000010), 0, true);
INSERT INTO regleActionneur (idRegle, idActionneur, valeur, isActive)
	VALUES ((SELECT id FROM regles WHERE nom = 'Lumière Off'), (SELECT id FROM actionneurs WHERE numeroActionneur = 4288617991 AND type = 0x2000010), 0, false);
*/

/*
INSERT INTO regleCapteur (idRegle, idCapteur, debutIntervalle, finIntervalle) VALUES ((SELECT id FROM regles WHERE nom = 'chauffageON'), 1, -10, 18.5);
INSERT INTO regleCapteur (idRegle, idCapteur, debutIntervalle, finIntervalle) VALUES ((SELECT id FROM regles WHERE nom = 'chauffageOFF'), 1, 18.5, 50);

INSERT INTO regles (id, nom, createsAlert) VALUES (100, 'chauffageON', true);
INSERT INTO regles (id, nom, createsAlert) VALUES (101, 'chauffageOFF', true);

INSERT INTO regleActionneur (idRegle, idActionneur, valeur, isActive) 
	VALUES ((SELECT id FROM regles WHERE nom = 'chauffageOFF'), 1, 123456789, true);		

INSERT INTO alertes(time, idRegle) VALUES (1, 100);
INSERT INTO alertes(time, idRegle) VALUES (10000000000, 101);
INSERT INTO alertes(time, idRegle) VALUES (100000000000000, 100);
*/
/*INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES (0x00A0001,0x00005620, 0, 1001);*/

