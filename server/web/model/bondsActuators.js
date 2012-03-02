var squel = require("squel");
var sql = require("./nodesql");
var logger = require("../logger");

function sqlConnect() {
	return sql.createClient("localhost", "rithm", "rithm", "pld");
}

/*
 * REQUEST :
 * ============================================================================
 * {} // in order to get all the connections
 * {"id":1} // in order to retrieve the connections with the actuator #1
 * {"subjectId":3} //  in order to retrieve the connections with the subject #3
 * ============================================================================
 *
 * RESPONSE :
 * ============================================================================
 *	{
	“fields”: [“id”, “nom”, “description”, “isGlobal”, “idSujet”],
	“count”: 1,
	“took”: 53,
	“hits”: [
		{
			“id”:1,
			“nom”: “Hop”,
			“description”: "Température corporelle",
			“isGlobal”: false,
			“idSujet”: 42
		}
		]
	}
 * ============================================================================
 */
function getBondsActuators(param, callback) {
	logger.debug("Getting bonds actuators...");
	// Construct the SQL query :
	var sql_req = squel.select()
		.field("id")
		.field("nom")
		.field("description")
		.field("isGlobal")
		.field("idSujet")
		.from("actionneurSujet");
		
	if (param.subjectId) {
		sql_req.where("idSujet = '" + param.subjectId + "'");
	}
		
	if (param.id) {
		sql_req.where("id = '" + param.id + "'");
	}
	
	// Send the query to SQL DB :
	var db = sqlConnect();
	sql.query(db, sql_req.toString(), function(result) {
		// Call the record with json response :
		log.info("Bonds actuators gotten !");
		callback(result);
		sql.close(db);
	});
}

exports.getBondsActuators = getBondsActuators;
