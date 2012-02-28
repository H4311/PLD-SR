var squel = require("squel");
var sql = require("./nodesql");

function sqlConnect() {
	return sql.createClient("localhost", "rithm", "rithm", "pld");
}

/*
 * REQUEST :
 * ============================================================================
 *	{
 *		“sensors” : [
 *		    {
 *		        “id” : “11111111”,
 *		        “from” : 111202332122,
 *		        “to” : 111202332122,
 				"type" : 1
 *		    },
 *			{
 *		        “id” : “222AAA1”,
 *		        “from” : 111202332122
 *		    }
 *		]
 *	}
 * ============================================================================
 *
 * RESPONSE :
 * ============================================================================
 *	{
 *		“records” : {
 *			“1111111” : [
 *				{
 *					“time” : 111202332122,
 *					“value” : “121122”,
 *					"type" : 1
 *				},
 *				{
 *					“time” : 111202332122,
 *					“value” : “121122”,
 *					"type" : 1
 *				}
 *			],
 *			“222AAA1” : [
 *				{
 *					“time” : 111202332122,
 *					“value” : “TESTEST”,
 *					"type" : 1
 *				}
 *			]
 *		}
 *	}
 * ============================================================================
 */
function getSensorsRecords(param, callback) {

	// Construct the SQL query :
	var sql_req = squel.select()
		.field("idCapteur")
		.field("time")
		.field("mesure")
		.field("typeMesure")
		.from("mesures");
	var sql_cond = squel.expr();
	if(request.sensors) {
		for(var i in request.sensors) {
			var sensor = request.sensors[i];
			if(!sensor.id) continue;
			if(!sensor.from) continue;
			
			var from = sensor.from;
			
			sql_cond.or_begin()
				.and("idCapteur = '"+sensor.id+"'")
				.and("time > '"+from+"'")
			
			if(sensor.type) {
				sql_cond.and("typeMesure = '"+type+"'");
			}
			
			if(sensor.to) {
				var to = sensor.to;
				sql_cond.and("time < '"+to+"'");
			}
			
			sql_cond.end();
		}
	}
	sql_req.where(sql_cond);
	console.log(sql_req.toString());
	
	// Send the query to SQL DB :
	var db = sqlConnect();
	sql.query(db, sql_req.toString(), function(result) {
		console.log("Took : "+result.took+"ms - Hits : "+result.count);
		
		// Construct json response :
		var response = {};
		response.records = {};
		for(var i in result.hits) {
			var hit	= result.hits[i];
			var id	= hit["idCapteur"];
			if(!response.records[id])
				response.records[id] = [];
			var record = {};
				record.time	= new Date(hit["time"]).getTime();
				record.value = hit["mesure"];
				record.type = hit["typeMesure"];
			response.records[id].push(record);
		}
		
		// Call the record with json response :
		callback(response);
		sql.close(db);
	});

}

function getSensorsList(callback) {
	// Construct the SQL query :
	var sql_req = squel.select()
		.from("capteurs");
	
	// Send the query to SQL DB :
	var db = sqlConnect();
	sql.query(db, sql_req.toString(), function(result) {
		console.log("Took : "+result.took+"ms - Hits : "+result.count);
		
		// Call the record with json response :
		callback(result);
		sql.close(db);
	});
}

function getSensorsListByPatient(id, callback) {	
	// Construct the SQL query :
	var sql_req = squel.select()
		.from("capteurs")
		.where("isGlobal = FALSE AND idSujet = "+id);
	
	// Send the query to SQL DB :
	var db = sqlConnect();
	sql.query(db, sql_req.toString(), function(result) {
		console.log("Took : "+result.took+"ms - Hits : "+result.count);
		
		// Call the record with json response :
		callback(result);
		sql.close(db);
	});
}

function getSensorsListByRoom(id, callback) {	
	// Construct the SQL query :
	var sql_req = squel.select()
		.from("capteurs")
		.where("isGlobal = TRUE AND idSujet = "+id);
	
	// Send the query to SQL DB :
	var db = sqlConnect();
	sql.query(db, sql_req.toString(), function(result) {
		console.log("Took : "+result.took+"ms - Hits : "+result.count);
		
		// Call the record with json response :
		callback(result);
		sql.close(db);
	});
}

function getActuatorsList(callback) {
	// Construct the SQL query :
	var sql_req = squel.select()
		.from("actionneurs");
	
	// Send the query to SQL DB :
	var db = sqlConnect();
	sql.query(db, sql_req.toString(), function(result) {
		console.log("Took : "+result.took+"ms - Hits : "+result.count);
		
		// Call the record with json response :
		callback(result);
		sql.close(db);
	});
}

function getRecordtypesBySensortype(sensortype) {
	switch(sensortype) {
		case 0x0060001:
			return [1];
		case 0x0050201:
			return [2];
		case 0x0070205:
			return [3];
		case 0x0070401:
			return [3,4];
		case 0x0070801:
			return [5,6];
		case 0x0070901:
			return [8];
		case 0x0070A01:
			return [9];
		case 0x00A0001:
			return [3,5,7];
	}
}

function recordtypeToString(recordtype) {
	switch(recordtype) {
		case 1:
			return "contact";
		case 2:
			return "bouton";
		case 3:
			return "température";
		case 4:
			return "humidité";
		case 5:
			return "luminosité";
		case 6:
			return "présence";
		case 7:
			return "mouvement";
		case 8:
			return "niveau CO2";
		case 9:
			return "rythme cardiaque";
		default:
			return "inconnu";
	}
}

exports.getSensorsRecords = getSensorsRecords;
exports.getSensorsList = getSensorsList;
exports.getSensorsListByPatient = getSensorsListByPatient;
exports.getSensorsListByRoom = getSensorsListByRoom;
exports.getActuatorsList = getActuatorsList;
exports.getRecordtypesBySensortype = getRecordtypesBySensortype;
exports.recordtypeToString = recordtypeToString;
