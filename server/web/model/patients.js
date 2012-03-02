var squel = require("squel");
var logger = require("../logger");
var sql = require("./nodesql");

function sqlConnect() {
	return sql.createClient("localhost", "rithm", "rithm", "pld");
}

/*
 * REQUEST :
 * ============================================================================
 * {} // in order to get all the patients
 * {"id":1} // in order to retrieve infos on patient 1
 * {"roomId":3} // in order to retrieve infos on patient which are on room 3
 * ============================================================================
 *
 * RESPONSE :
 * ============================================================================
 *	{
	“fields”: [“id”, “nom”, “isMan”, “raisonHospitalisation”, “idPiece”],
	“count”: 1,
	“took”: 53,
	“hits”: [
		{
			“id”:1,
			“nom”: “Lhaache”,
			“isMan”: false,
			“raisonHospitalisation”: “Changement de sexe”,
			“idPiece”: 42
		}
		]
	}
 * ============================================================================
 */
function getPatients(param, callback) {
	logger.debug("Gettings patients...");
	
	// Construct the SQL query :
	var sql_req = squel.select()
		.field("id")
		.field("nom")
		.field("isMan")
		.field("raisonHospitalisation")
		.field("idPiece")
		.from("patients");
		
	if (param.roomId != null) {
		sql_req.where("idPiece = '" + param.roomId + "'");
	}
		
	if (param.id != null) {
		sql_req.where("id = '" + param.id + "'");
	}
	
	// Send the query to SQL DB :
	var db = sqlConnect();
	sql.query(db, sql_req.toString(), function(result) {
		// Call the record with json response :
		logger.info("Patients gotten !");
		callback(result);
		sql.close(db);
	});
}

exports.getPatients = getPatients;
