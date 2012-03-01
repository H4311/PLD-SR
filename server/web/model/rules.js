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
	"idRegle" : 12 // pour modifier une règle existante
 * 	"nom" : Règle froid
 *	"createsAlert" : 1
 *  
 * 	"idCapteur" : 23
 * 	"debIT" : -10
 * 	"finIT" :18
 * 
 * 	"idActionneur" : 34
 * 	"valeur" : 42
 * 	"isActive" : 1
 * 
 * } // TODO
 * ============================================================================
 *
 * RESPONSE :
 * ============================================================================
 *	TODO
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
		callback(null);
	}
	
	var sql_req = "";
	
	/* Très simpliste pour l'instant */
	if (param.nom && param.createsAlert) {
		sql_req = "INSERT INTO regles(nom, createsAlert)";
		//sql_req += "VALUES("+param.nom+","+param.createsAlert+");";
		sql_req += "VALUES('truc', '1');";
		
	} else {
		logger.error("[Services rules] params nom & createsAlert");
	}
	
	/*
	if (param.idRegle && param.nom && param.idCapteur && param.debIT && param.finIT && 
		param.idActionneur && param.valeur && param.isActive) {
			sql_req = "INSERT INTO regles(nom, createsAlert)";
			sql_req += "VALUES("+param.nom+","+param.createsAlert+");";

			sql_req += "INSERT INTO regleCapteur(idRegle, idCapteur, debutIntervalle, finIntervalle)";
			sql_req += "VALUES("+param.idRegle+","+param.idCapteur+","+param.debIT+","+param.finIT+");";
			
			sql_req += "INSERT INTO regleActionneur(idRegle, idActionneur, valeur, isActive)";
			sql_req += "VALUES("+param.idRegle+","+param.idActionneur+","+param.valeur+","+param.isActive+");";
			
			console.log("Formatage de sql_req terminé");
			
	} else {
		console.log("[Services rules] Erreur : Passage de parametres incorrect, insertion annulée");
	}
	*/
	
	// Send the query to SQL DB
	var db = sqlConnect();
	sql.query(db, sql_req.toString(), function(result) {
		// Call the record with json response :
		callback(result);
		sql.close(db);
	});
	
}

exports.addRule = addRule;
