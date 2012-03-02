var squel = require("squel");
var logger = require("../logger");
var sql = require("./nodesql");

function sqlConnect() {
	return sql.createClient("localhost", "rithm", "rithm", "pld");
}

/*
 * REQUEST :
 * ============================================================================
 * {
 * 	"nom" : "Règle froid",
 *	"createsAlert" : 1,
 *  
 * 	"idCapteur" : 23,
 * 	"typeMesure": 1,
 * 	"debIT" : -10,
 * 	"finIT" :18,
 * 
 * 	"idActionneur" : 34,
 * 	"valeur" : 42,
 * 	"isActive" : 1
 * }
 * ============================================================================
 *
 * RESPONSE :
 * ============================================================================
 *	réponse normale avec hits
 * ============================================================================
 */

/*
curl -H 'content-type: application/json' -XPOST https://localhost:1337/rules -d "{\"nom\":\"12\", \"createsAlert\":\"Règle\"}" --cacert ../web/security/server.crt
curl -H 'content-type: application/json' -XPOST https://localhost:1337/rules -d "{\"idRegle\":\"12\", \"nom\":\"Règle\", \"createsAlert\":\"1\", \"idCapteur\":\"23\", \"debIT\":\"-10\", \"finIT\":\"18\", \"idActionneur\":\"42\", \"valeur\":\"12\", \"isActive\":\"1\"}" --cacert ../web/security/server.crt
*/

/*
 * Ajout d'une regle en entier : création de la règle, et lien entre le capteur et l'actionneur.
 * On peut considérer l'ajout d'actionneurs éventuels pour un capteur
 */

function addRule(param, callback) {
	
	if(!param.nom) {
		logger.warn("[Service rules] Unnamed rule");
		callback({});
		return;
	}
	logger.info("Adding rule " + param.nom + "...");
	
	var db = sqlConnect();
	
	var sql_req1 = "SELECT id FROM regles WHERE nom = '"+param.nom+"';";
	
	sql.query(db, sql_req1.toString(), function(result) {

		var sql_req = "";
	
		if (param.createsAlert != null) { 
			//Insertion d'une règle
			if (result.count < 1) {
				sql_req = "INSERT INTO regles(nom, createsAlert) ";
				sql_req += "VALUES('"+param.nom+"',"+param.createsAlert+");";
			}
		}
		if(param.idCapteur && param.typeMesure && param.debIT && param.finIT) {
			//Insertion d'un règle/capteur
			logger.info("Insertion regleCapteur");
			sql_req += "INSERT INTO regleCapteur (idRegle, idCapteur, typeMesure, debutIntervalle, finIntervalle) ";
			sql_req += "VALUES((SELECT id FROM regles WHERE nom='" + param.nom + "'), " + param.idCapteur + ", " + param.typeMesure + ", " + param.debIT + ", " + param.finIT + ");";
		}
		if(param.idActionneur && param.valeur && param.isActive) {
			//Insertion d'un règle/actionneur
			logger.info("Insertion regleActionneur");
			sql_req += "INSERT INTO regleActionneur (idRegle, idActionneur, valeur, isActive) ";
			sql_req += "VALUES((SELECT id FROM regles WHERE nom='" + param.nom + "'), " + param.idActionneur + ", " + param.valeur + ", " + param.isActive + ");";
		}
		//TODO: gérer les erreurs
		/*else {
			logger.error("[Services rules] params nom & createsAlert");
			callback({});
			return;
		}*/

		sql.query(db, sql_req.toString(), function(result) {
			// Call the record with json response :
			logger.info("Rule added !");
			callback(result);
			sql.close(db);
			
		});

	});
	
}

function getRules(callback) {
	logger.info("Getting rules...");
	// Construct the SQL query :
	var sql_req = squel.select()
		.from("regles");
	
	// Send the query to SQL DB :
	var db = sqlConnect();
	sql.query(db, sql_req.toString(), function(result) {
		// Call the record with json response :
		logger.info("Rules gotten !");
		callback(result);
		sql.close(db);
	});
}

function getRulesSensors(callback) {
	// Construct the SQL query :
	var sql_req = squel.select()
		.from("regleCapteur");
	
	// Send the query to SQL DB :
	var db = sqlConnect();
	sql.query(db, sql_req.toString(), function(result) {
		// Call the record with json response :
		callback(result);
		sql.close(db);
	});
}

function getRulesActuators(callback) {
	// Construct the SQL query :
	var sql_req = squel.select()
		.from("regleActionneur");
	
	// Send the query to SQL DB :
	var db = sqlConnect();
	sql.query(db, sql_req.toString(), function(result) {
		// Call the record with json response :
		callback(result);
		sql.close(db);
	});
}


exports.addRule = addRule;
exports.getRules = getRules;
exports.getRulesSensors = getRulesSensors;
exports.getRulesActuators = getRulesActuators;
