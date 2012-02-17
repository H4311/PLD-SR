
INSERT INTO actionneurs (numeroActionneur, type) VALUES (1337, 42);

INSERT INTO regles (id, nom, createsAlert) VALUES (100, 'chauffageON', true);
INSERT INTO regles (id, nom, createsAlert) VALUES (101, 'chauffageOFF', true);

INSERT INTO regleEvent (idRegle, idEvent) VALUES (100, 10);
INSERT INTO regleEvent (idRegle, idEvent) VALUES (101, 5);

INSERT INTO regleCapteur (idRegle, idCapteur, debutIntervalle, finIntervalle) VALUES ((SELECT id FROM regles WHERE nom = 'chauffageON'), 1, -10, 18.5);
INSERT INTO regleCapteur (idRegle, idCapteur, debutIntervalle, finIntervalle) VALUES ((SELECT id FROM regles WHERE nom = 'chauffageOFF'), 1, 18.5, 50);

INSERT INTO regleActionneur (idRegle, idActionneur, valeur, isActive) VALUES ((SELECT id FROM regles WHERE nom = 'chauffageOFF'), 1, 123456789, true);
