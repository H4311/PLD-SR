var squel = require("squel");
var sql = require("./nodesql");

function sqlConnect() {
	return sql.createClient("localhost", "rithm", "rithm", "pld");
}

/*
 * REQUEST :
 * ============================================================================
 * {} // in order to get all the rooms
 * {"id":1} // in order to retrieve infos on room
 * ============================================================================
 *
 * RESPONSE :
 * ============================================================================
 *	to be documented
 * ============================================================================
 */
function getRooms(param, callback) {

	// Construct the SQL query :
	var sql_req = squel.select()
		.field("id")
		.field("nom")
		.field("description")
		.from("pieces");
		
	if (param.id != null) {
		sql_req.where("id = '" + param.id + "'");
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

exports.getRooms = getRooms;

