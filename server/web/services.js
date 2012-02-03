var squel = require("squel");
var sql = require("./nodesql");

function sqlConnect() {
	return sql.createClient("localhost", "root", "root", "test");
}

function error(code, resp) {
	var result = {};
	result.error = {};
	result.error.code = code;
	
	switch(code) {
		case 0:
			result.error.msg = "Couldn't parse the JSON";
			break;
		default:
			result.error.msg = "Unknow error";
	}
	
	var jsonResult = JSON.stringify(result);
	resp.end(jsonResult);
}

/*
 * SERVICE Sensors
 * Gets records from sensors, allows to specify an interval.
 *
 * REQUEST :
 * ============================================================================
 *	{
 *		“sensors” : [
 *		    {
 *		        “id” : “11111111”,
 *		        “from” : “yyyy/MM/dd HH:mm:ss”,
 *		        “to” : “yyyy/MM/dd HH:mm:ss”
 *		    },
 *			{
 *		        “id” : “222AAA1”,
 *		        “from” : “yyyy/MM/dd HH:mm:ss”
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
 *					“time” : “yyyy/MM/dd HH:mm:ss”,
 *					“value” : “121122”
 *				},
 *				{
 *					“time” : “yyyy/MM/dd HH:mm:ss”,
 *					“value” : “121122”
 *				}
 *			],
 *			“222AAA1” : [
 *				{
 *					“time” : “yyyy/MM/dd HH:mm:ss”,
 *					“value” : “TESTEST”
 *				}
 *			]
 *		}
 *	}
 * ============================================================================
 */
function serviceSensors(query, post, resp) {
	resp.writeHead(200, {"Content-type" : "application/json"});
	
	// Parse the json request in POST data :
	request = JSON.parse(post);
	if(!request) {
		error(0, resp);
		return;
	}
	
	// Construct the SQL query :
	var sql_req = squel.select()
		.field("idCapteur")
		.field("time")
		.field("mesure")
		.from("mesures");
	var sql_cond = squel.expr();
	if(request.sensors) {
		for(var i in request.sensors) {
			var sensor = request.sensors[i];
			if(!sensor.id) break;
			if(!sensor.from) break;
			
			var from = Date.parse(sensor.from);
			if(!from) break;
			
			sql_cond.or_begin()
				.and("idCapteur = '"+sensor.id+"'")
				.and("time > '"+from+"'");
			
			if(sensor.to) {
				var to = Date.parse(sensor.to);
				if(!to) break;
				sql_cond.and("time < '"+to+"'");
			}
			
			sql_cond.end();
		}
	}
	sql_req.where(sql_cond);
	
	// Send the query to SQL DB :
	var db = sqlConnect();
	sql.query(db, sql_req.toString(), function(result) {
		console.log("Took : "+result.took+"ms\nHits : "+result.count);
		
		// Construct json response :
		var response = {};
		response.records = {};
		for(var i in result.hits) {
			var hit	= result.hits[i];
			var id	= hit["idCapteur"];
			if(!response.records[id])
				response.records[id] = [];
			var record = {};
				record.time	= new Date(hit["time"])
					.toString("yyyy/MM/dd HH:mm:ss");
				record.value = hit[mesure];
			response.records[id].push(record);
		}
		
		// Send the stringified json to client :
		var jsonResponse = JSON.stringify(response);
		resp.end(jsonResponse);
		sql.close(db);
	});
}

/*
 * SERVICE Actuators
 * Allows to pass values to actuators.
 *
 */
function serviceActuators(query, post, resp) {
	resp.writeHead(200, {"Content-type" : "application/json"});
	
	// Parse the json POST request
	request = JSON.parse(post);
	
	var result = {};
	
	var jsonResult = JSON.stringify(result);
	resp.end(jsonResult);
}

exports.sensors = serviceSensors;
exports.actuators = serviceActuators;
