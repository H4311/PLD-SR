var squel = require("squel");
var sql = require("./nodesql");

function sqlConnect() {
	return sql.createClient("localhost", "rithm", "rithm", "pld");
}

/*
 * REQUEST :
 * ============================================================================
{
	“from” : “yyyy/MM/dd HH:mm:ss”,
	“to” : “yyyy/MM/dd HH:mm:ss”
}
 * ============================================================================
 *
 * RESPONSE :
 * ============================================================================
{
	“alerts” : [
		{
			“time” : “yyyy/MM/dd HH:mm:ss”,
			"name" : "patient convulse",
			“sensors" : [
				{
					"id" : 123,
					"type" : 12,
					"isGlobal" : true,
					"..." : 1
				}
			]
		}
	]
}
 * ============================================================================
 */
function getAlerts(param, callback) {

	var from = Date.parse(param.from);
	// retrieve des alertes déclenchées
	var sql_req = "";
	sql_req += "SELECT time, idRegle, (SELECT nom FROM regles WHERE id = idRegle) nom ";
	sql_req += "FROM alertes ";
	sql_req += "WHERE time > " + from + " ";
	if(param.to) {
		sql_req += "AND time < " + Date.parse(param.to) + " ";
	}
	sql_req += "ORDER BY time DESC ";
	
	var db = sqlConnect();
	sql.query(db, sql_req, function(result) {
		// Construct json response
		var response = {};
		response.alerts = [];
		
		if(result.count == 0) {
			// Call the callback with json response
			callback(response);
			sql.close(db);
		}
		
		var nbResponseReceived = 0;
		for(var i in result.hits) {
			var hit = result.hits[i];
			var _alert = {};
			// Add the alert to the result
			response.alerts.push(_alert);
			response.alerts[i].time = hit["time"];
			response.alerts[i].nom = hit["nom"];
			response.alerts[i].id = hit["idRegle"];
			response.alerts[i].sensors = [];
			
			// Retrieve des capteurs impliqués dans l'alerte
			sql_req = "";
			sql_req += "SELECT rc.idCapteur, c.type, c.isGlobal ";
			sql_req += "FROM regleCapteur rc INNER JOIN capteurs c ON rc.idCapteur = c.id ";
			sql_req += "WHERE rc.idRegle = " + hit.idRegle;

			sql.query(db, sql_req, function(result2) {
				for(var j in result2.hits) {
					response.alerts[nbResponseReceived].sensors.push(result2.hits[j]);
				}

				nbResponseReceived++;
				
				// For the last alert
				if(nbResponseReceived === result.count) {
					// Call the callback with json response
					callback(response);
					sql.close(db);
				}
				
			});
		}
	});

}

exports.getAlerts = getAlerts;
