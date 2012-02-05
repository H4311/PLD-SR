var mysql = require("mysql-native");

function sqlCreateClient(address, user, passwd, dbname) {
	var db = mysql.createTCPClient(address);
	db.auto_prepare = true;
	db.auth(dbname, user, passwd);
	return db;
}

function sqlClose(db) {
	db.close();
}

function sqlAsyncQuery(db, query, callbackAsync, callbackEnd) { 
	var timestamp = new Date().getTime();
	var result={};
	result.fields = [];
	result.count = 0;
	result.hits = [];
	console.log("Query : " + query.toString());
	db.query(query)
		.on('field', function(f) {
			result.fields.push(f.name);
		})
		.on('row', function(hit) {
			result.hits.push(hit);
			result.count++;
			if(callbackAsync != null) callbackAsync(hit);
		})
		.on('end', function() {
			result.took = new Date().getTime() - timestamp;
			callbackEnd(result);
		});
}

function sqlQuery(db, query, callback) {
	sqlAsyncQuery(db, query, null, callback);
}

function sqlDumpResult(result) {
	console.log("Took : "+result.took+"ms\nHits : "+result.count);
	var strFields = "";
	for(var i in result.fields) strFields+=result.fields[i]+"\t";
	console.log("Fields : "+strFields);
	for(var i in result.hits) {
		var hit = result.hits[i];
		console.log("================================");
		console.log("Hit n°"+i);
		for(var field in hit) console.log(field+":\t"+hit[field]);
	}

}

exports.createClient = sqlCreateClient;
exports.close = sqlClose;
exports.asyncQuery = sqlAsyncQuery;
exports.query = sqlQuery;
exports.dumpResult = sqlDumpResult;

// Utilisation :
//var db = sqlCreateClient("localhost", "rithm", "rithm", "pld");
//sqlQuery(db, "select 1+1,2,3,'4',length('hello')", function(result) {sqlDumpResult(result);});
//sqlClose(db);
