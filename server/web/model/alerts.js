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
	sql_req += "SELECT time, idRegle ";
	sql_req += "FROM alertes ";
	sql_req += "WHERE time > " + from*1000 + " ";
	if(param.to) {
		sql_req += "AND time < " + Date.parse(param.to)*1000;
	}	
	
	var db = sqlConnect();
	sql.query(db, sql_req, function(result) {
		console.log("A Took : "+result.took+"ms - Hits : "+result.count);
		
		// Construct json response
		var response = {};
		response.alerts = [];
		
		var nbResponseReceived = 0;
		for(var i in result.hits) {
			var hit = result.hits[i];
			var _alert = {};
			// Add the alert to the result
			response.alerts.push(_alert);
			response.alerts[i].time = hit["time"];
			//_alert.name = hit["name"];
			response.alerts[i].id = hit["idRegle"];
			response.alerts[i].sensors = [];
			
			// Retrieve des capteurs impliqués dans l'alerte
			sql_req = "";
			sql_req += "SELECT idCapteur, idRegle ";
			sql_req += "FROM regleCapteur ";
			sql_req += "WHERE idRegle = " + hit.idRegle;

			sql.query(db, sql_req, function(result2) {
				console.log("Took : "+result2.took+"ms - Hits : "+result2.count);
				
				for(var j in result2.hits) {
					response.alerts[nbResponseReceived].sensors.push(result2.hits[j].idCapteur);
				}

				nbResponseReceived++;
				// For the last alert
				if(nbResponseReceived === result.count) {
					// Call the record with json response
					callback(response);
					console.log(response);
					sql.close(db);
				}
				
			});
		}
	});

}

exports.getAlerts = getAlerts;
