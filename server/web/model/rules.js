var squel = require("squel");
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
 * 	"debutIntervalle" : -10
 * 	"finIntervalle" :18
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
 * Ajout d'une regle en entier : création de la règle, et lien entre le capteur et l'actionneur.
 * On peut considérer l'ajout d'actionneurs éventuels pour un capteur
 */

function addRule(param, callback) {
	if(!param.nom) {
		console.log("[Service rules] Warning : Regle sans nom");
		return;
	}
	
	var sql_req;
	
	/* Très simpliste pour l'instant */
	if (!param.idRegle && param.nom && param.idCapteur && param.debutIntervalle && param.finIntervalle && 
		param.idActionneur && param.valeur && param.isActive) {
			sql_req = "INSERT INTO regles(nom, createAlert)";
			sql_req += "VALUES("+param.nom+","+param.createAlert+");";
			
			sql_req += "INSERT INTO regleCapteur(idRegle, idCapteur, debutIntervalle, finIntervalle)";
			sql_req += "VALUES(+"param.idRegle+","+param.idCapteur+","+param.debutIntervalle+","+param.finIntervalle+");";
			
			sql_req += "INSERT INTO regleActionneur(idRegle, idActionneur, valeur, isActive)";
			sql_req += "VALUES("+param.idRegle+","+param.idActionneur+","+param.valeur+","+param.isActive+");";
			
	} else {
		console.log("[Services rules] Erreur : Passage de parametres incorrect, insertion annulée");
	}
	
	// Send the query to SQL DB :
	var db = sqlConnect();
	sql.query(db, sql_req.toString(), function(result) {
		console.log("Took : "+result.took+"ms\nHits : "+result.count);
		
		// Call the record with json response :
		callback(result);
		sql.close(db);
	});
}

exports.addRule = addRule;
