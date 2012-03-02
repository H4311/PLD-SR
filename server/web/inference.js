var squel = require("squel");
var sql = require("./model/nodesql");
var admin = require("./model/admin");
var logger = require("./logger");

var sqlConnect = function() {
	return sql.createClient("localhost", "rithm", "rithm", "pld");
}

var throwAlerts = function(regle) {
	logger.info("Throwing alerts.");
	var sqlRequest = "";
	sqlRequest += "SELECT id, createsAlert ";
	sqlRequest += "FROM regles ";
	sqlRequest += "WHERE id = " + regle;

	var db = sqlConnect();
	sql.query(db, sqlRequest, function(result) {
		logger.debug("Took : " + result.took + "ms\nHits : " + result.count);
		
		if(result.count != 1) {
			logger.error("[throwAlerts] E: problème pour trouver la règle demandée.");
		} else {
			if(result.hits[0].createsAlert) {
				logger.info("Lancement d'une alerte pour la règle " + result.hits[0].id);
				
				var sqlRequest = "";
				sqlRequest += "INSERT INTO alertes (time, idRegle) ";
				sqlRequest += "VALUES (" + new Date().getTime() * 1000 + ", " + result.hits[0].id + ")";

				var db = sqlConnect();
				sql.query(db, sqlRequest, function(result) {
					logger.debug("Took : " + result.took + "ms\nHits : " + result.count);
					logger.info("Alert done");
					sql.close(db);
				});
				
			}
		}
	
		sql.close(db);
	});
}

var triggerActionneurs = function(result) {
	logger.info("Triggering actuators...");
	for(var i in result.hits) {
	
		if(result.hits[0].nbFalse == 0) {
			logger.info("Règle " + result.hits[0].regle + " déclenchée");
		
			var sqlRequest = "";
			sqlRequest += "SELECT numeroActionneur AS id, type AS type, isActive AS active , valeur AS value ";
			sqlRequest += "FROM regleActionneur RA INNER JOIN actionneurs A ON RA.idActionneur = A.id ";
			sqlRequest += "WHERE idRegle = " + result.hits[0].regle;
		
			var db = sqlConnect();
			sql.query(db, sqlRequest, function(result) {
				logger.debug("Took : " + result.took + "ms\nHits : " + result.count);
				
				for(var j in result.hits) {
					//Récupérer les elem de la requete pour les mettre dans param !
					logger.info("Capteur " + result.hits[j].id + " de type " + result.hits[j].type + " est actif:" + result.hits[j].active + " de valeur " + result.hits[j].value + ".");
			
					admin.setActuator(result.hits[i], function(result) {
						logger.debug("Retour de function setActuator : " + result);
					});
				}
			
				sql.close(db);
			});
			
			throwAlerts(result.hits[0].regle);
		
		}
	}
}

var recomputeRules = function(result) {
	logger.info("Recomputing rules...");
	for(var i in result.hits) {
		//On compte le nombre de capteurs qui ne sont pas dans l'intervalle permettant de déclencher la règle
		logger.debug("Test de la règle " + result.hits[i].idRegle);
		
		var subReq = "(SELECT mesure FROM mesures WHERE idCapteur = r.idCapteur AND typeMesure = r.typeMesure ORDER BY time DESC LIMIT 1)";
		
		var sqlRequest = "";
		sqlRequest += "SELECT COUNT(*) nbFalse, " + result.hits[i].idRegle + " regle FROM (";
		sqlRequest += "SELECT (r.debutIntervalle < " + subReq + " AND " + subReq + " < r.finIntervalle) AS test, r.idRegle ";
		sqlRequest += "FROM regleCapteur r ";
		sqlRequest += "WHERE idRegle = " + result.hits[i].idRegle;
		sqlRequest += ") T WHERE T.test = 0";
		
		var db = sqlConnect();
		sql.query(db, sqlRequest, function(result) {
			if(result.count != 1) {
				logger.error("[recomputeRules] E: Count différent de 1");
			} else {
				triggerActionneurs(result);
			}
			sql.close(db);
		});
	}
}

var lastUpdate = 0;

var boucle = function() {
	logger.info("Moteur d'inférence appelé");
	//Selection des règles
	var sqlRequest = "SELECT DISTINCT idRegle FROM regleCapteur WHERE idCapteur IN ";
	sqlRequest += "(SELECT idCapteur FROM mesures WHERE time > " + lastUpdate + ")";
	
	var db = sqlConnect();
	sql.query(db, sqlRequest, function(result) {		
		lastUpdate = new Date().getTime() * 1000;
		
		recomputeRules(result);
		
		sql.close(db);
	});
}

var interval = null;

var run = function() {
	interval = setInterval(boucle, 1000);
}

var stop = function() {
	clearInterval(interval);
	process.exit(code=0);
}

run();
setTimeout(stop, 3500);

exports.runInference = run;
exports.stopInference = stop;
