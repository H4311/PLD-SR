var squel = require("squel");
var sql = require("./nodesql");

function sqlConnect() {
	return sql.createClient("localhost", "rithm", "rithm", "pld");
}

/*
 * REQUEST :
 * ============================================================================
 *	empty
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
function getPatients(callback) {

	// Construct the SQL query :
	var sql_req = squel.select()
		.field("id")
		.field("nom")
		.field("isMan")
		.field("raisonHospitalisation")
		.field("idPiece")
		.from("patients");
	
	// Send the query to SQL DB :
	var db = sqlConnect();
	sql.query(db, sql_req.toString(), function(result) {
		console.log("Took : "+result.took+"ms\nHits : "+result.count);
		
		// Call the record with json response :
		callback(result);
		sql.close(db);
	});

}

exports.getPatients = getPatients;
