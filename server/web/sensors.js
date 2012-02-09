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
function getSensorsRecords(param, callback) {

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
				record.value = hit["mesure"];
			response.records[id].push(record);
		}
		
		// Call the record with json response :
		callback(response);
		sql.close(db);
	});

}

exports.getSensorsRecords = getSensorsRecords;
