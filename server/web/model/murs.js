var squel = require("squel");
var logger = require("../logger");
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
	logger.info("Gettings walls with id = " + param.id + "...");
	
	if(!param.id) {
		logger.error("[Service murs] no id specified");
		return;
	}
	
	// Construct the SQL query :
	var sql_req = "SELECT id, idPiece, x1, y1 ,x2 ,y2 ,ordre, isPorte FROM murs ";
	sql_req += "WHERE idPiece = " + param.id;
	sql_req += " ORDER BY ordre";
	
	// Send the query to SQL DB :
	var db = sqlConnect();
	sql.query(db, sql_req.toString(), function(result) {
		// Call the record with json response :
		logger.info("Wall gotten !");
		callback(result);
		sql.close(db);
	});
}

exports.getMurs = getMurs;
