var squel = require("squel");
var sql = require("./nodesql");

var sqlConnect = function() {
	return sql.createClient("localhost", "rithm", "rithm", "pld");
}

var lastUpdate = 0;

var boucle = function() {
	console.log("Bonjour");
	
	//Selection des règles
	var sqlRequest = "SELECT idRegle FROM regleCapteur WHERE idCapteur IN ";
	sqlRequest += "(SELECT idCapteur FROM mesures WHERE time > " + lastUpdate + ")";
	
	var db = sqlConnect();
	sql.query(db, sqlRequest, function(result) {
		console.log("Took : " + result.took + "ms\nHits : " + result.count);
		
		lastUpdate = new Date().getTime() * 1000;
		
		console.log(result);
		sql.close(db);
	});

}

var interval = null;

var run = function() {
	interval = setInterval(boucle, 1000);
}

var stop = function() {
	clearInterval(interval);
}

run();
setTimeout(stop, 3500);

exports.runInference = run;
exports.stopInference = stop;
