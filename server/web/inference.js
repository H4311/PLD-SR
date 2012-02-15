var squel = require("squel");
var sql = require("./model/nodesql");

var sqlConnect = function() {
	return sql.createClient("localhost", "rithm", "rithm", "pld");
}

var recomputeRules = function(result) {
	for(var i in result.hits) {
		//On compte le nombre de capteurs qui ne sont pas dans l'intervalle permettant de déclencher la règle
		console.log("Test de la règle " + result.hits[i].idRegle);
		
		var subReq = "(SELECT mesure FROM mesures WHERE idCapteur = r.idCapteur ORDER BY time DESC LIMIT 1)";
		
		var sqlRequest = "";
		sqlRequest += "SELECT COUNT(*) nbFalse, " + result.hits[i].idRegle + " regle FROM (";
		sqlRequest += "SELECT (r.debutIntervalle < " + subReq + " AND " + subReq + " < r.finIntervalle) AS test, r.idRegle ";
		sqlRequest += "FROM regleCapteur r ";
		sqlRequest += "WHERE idRegle = " + result.hits[i].idRegle;
		sqlRequest += ") T WHERE T.test = 0";
		
		var db = sqlConnect();
		sql.query(db, sqlRequest, function(result) {
			//console.log("Took : " + result.took + "ms\nHits : " + result.count);
			//console.log(result);
			
			if(result.count != 1) {
				console.log("[recomputeRules] E: Count différent de 1");
			}
			
			if(result.hits[0].nbFalse == 0) {
				console.log("Règle " + result.hits[0].regle + " déclenchée");
			}
			
			sql.close(db);
		});
	}
}

var lastUpdate = 0;

var boucle = function() {
	console.log("Moteur d'inférence appelé");
	//Selection des règles
	var sqlRequest = "SELECT DISTINCT idRegle FROM regleCapteur WHERE idCapteur IN ";
	sqlRequest += "(SELECT idCapteur FROM mesures WHERE time > " + lastUpdate + ")";
	
	var db = sqlConnect();
	sql.query(db, sqlRequest, function(result) {
		//console.log("Took : " + result.took + "ms\nHits : " + result.count);
		
		lastUpdate = new Date().getTime() * 1000;
		
		recomputeRules(result);
		
		sql.close(db);
	});
}

var interval = null;

var run = function() {
	interval = setInterval(boucle, 1000);
}

var stop = function() {
	clearInterval(interval);
	process.exit(code=0);
}

run();
setTimeout(stop, 3500);

exports.runInference = run;
exports.stopInference = stop;
