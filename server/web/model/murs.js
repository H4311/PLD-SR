var squel = require("squel");
var sql = require("./nodesql");

function sqlConnect() {
	return sql.createClient("localhost", "rithm", "rithm", "pld");
}

/*
 * REQUEST :
 * ============================================================================
 * {"id":1} // in order to retrieve the murs of room of id 1
 * ============================================================================
 *
 * RESPONSE :
 * ============================================================================
 *	to be documented
 * ============================================================================
 */
function getMurs(param, callback) {
	if(!param.id) {
		console.log("[Service murs] Erreur : pas d'id spécifié");
		return;
	}
	
	// Construct the SQL query :
	var sql_req = "SELECT id, idPiece, x1, y1 ,x2 ,y2 ,ordre, isPorte FROM murs ";
	sql_req += "WHERE idPiece = " + param.id;
	
	// Send the query to SQL DB :
	var db = sqlConnect();
	sql.query(db, sql_req.toString(), function(result) {
		console.log("Took : "+result.took+"ms\nHits : "+result.count);
		
		// Call the record with json response :
		callback(result);
		sql.close(db);
	});
}

exports.getMurs = getMurs;
