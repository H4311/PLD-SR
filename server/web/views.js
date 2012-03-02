var config = require("./config");

var modelrooms = require("./model/rooms");
var modelpatients = require("./model/patients");
var modelalerts = require("./model/alerts");
var modelsensors = require("./model/sensors");
var modeladmin = require("./model/admin");
var modelrules = require("./model/rules");

var logger = require("./logger");

var rest = config.getProperty("security.ssl") ? "https://" : "http://";
rest += config.getProperty("rest.url");

/*
 * VIEW Index
 */
function viewIndex(req, res) {
	logger.debug("Viewing index.");
	var req = {};
	
    // Get rooms details
    modelrooms.getRooms(req, function(result) {
        var rooms=result.hits;
        res.render('index', {title: "Accueil", rest: rest, rooms: rooms});
	});
}

/*
 * VIEW Room
 */
function viewRoom(req, res) {
    var id = req.param("id", null);
	logger.info("Viewing room (id = " + id + ") page.");
    var req = {"id":id};
   
    // Get rooms details
    modelrooms.getRooms(req, function(result) {
        var roomDetails=result.hits[0];
        if(!roomDetails) {
        	res.render('404', {title: "Erreur", rest: rest});
        	return;
        }
        
        var req = {"roomId":id};
       
        // Get patients list
        modelpatients.getPatients(req, function(result) {
            var patients = result.hits;
            res.render('room', {title: "Chambre", rest: rest, roomDetails: roomDetails, patients: patients});
        });
    });
}


/*
 * VIEW Login
 */
function viewLogin(req, res) {
	next = req.param("next", null);
	logger.info("Viewing login page. Next is : " + next);
	res.render('login', {title: "Login", rest: rest, next: next, error: null});
}

/*
 * VIEW Patient
 */
function viewPatient(req, res) {
	var id = req.param("id", null);
	logger.info("Viewing patient (id = " + id + " page");
	var req = {"id":id};
	
	// Get model data
	modelpatients.getPatients(req, function(result) {
		var patientDetails=result.hits[0];
		if(!patientDetails) {
        	res.render('404', {title: "Erreur", rest: rest});
        	return;
        }
		
		modelsensors.getSensorsListByPatient(id, function(result) {
            var sensors = result.hits;
            var measures = [];
            
            for(var i in sensors) {
            	var sensor = sensors[i];
            	var types = modelsensors.getRecordtypesBySensortype(sensor.type);
            	for(var j in types) {
            		var measure = {
            			sensorId : sensor.id,
            			sensorType : sensor.type,
            			recordType : types[j],
            			name : modelsensors.recordtypeToString(types[j])
            		};
            		measures.push(measure);
            	}
            }
            var typeLabels = modelsensors.getSensorsLabels();
            res.render('patient', {title: "Patient "+patientDetails.nom, rest: rest, patientDetails: patientDetails, measures: measures, typeLabels: typeLabels});
        });
	});
}

/*
 * VIEW Notifications
 */
function viewNotif(req, res) {
	logger.info("Viewing notification page");
	//TODO: Get the last 24h notifs
	var now = new Date();
	var d = (now.getTime() - 3600*24*1000);
	var before = new Date(d);
	var data = {"from":  dateToString(before)};
	
	// Get model data
	modelalerts.getAlerts(data, function(result) {
		var notifs = result;
		res.render('alerts', {title: "Notifications", rest: rest, notifs: notifs });
	});
}


function dateToString(date) {
	var s = "";
	s += date.getFullYear();
	s += "/";
	s += twoDigits(date.getMonth()+1);
	s += "/";
	s += twoDigits(date.getDate());
	s += " ";
	s += twoDigits(date.getHours());
	s += ":";
	s += twoDigits(date.getMinutes());
	s += ":";
	s += twoDigits(date.getSeconds());
	return s;
}

function twoDigits(nb) {
	var retour = nb < 10 ? "0" + nb : "" + nb;
	return retour;
}


function viewNotfound(req, res) {
	logger.warn("View not found : " + req.url);
	res.render('404', {title: "Page non trouvée", rest: rest});
}

function viewHelp(req, res) {
	logger.info("Viewing help page.");
	res.render('help', {title: "Aide", rest: rest});
}

/*
 * VIEW addSensorPatient
 */
function addSensorPatient(req, res){
	var patientId = parseInt(req.param("id", null));
	var sensorId = parseInt(req.param("sensorId", null));
	var sensorType = parseInt(req.param("sensorType", null));
	logger.info("Adding sensor page");
	
	var data={};
	data.id = sensorId;
	data.type = sensorType;
	data.subject = {
		i: patientId,
		g: 0
	};
	
	modeladmin.addDevice(data, function() {
		viewPatient(req, res);
	});
}

/*
 * VIEW getActuatorsList
 */
function viewActuators(req, res){
	logger.info("Viewing actuators page.");
		modelsensors.getActuatorsList(function(result){
			res.render('actuators', {title: "Actionneurs", rest: rest, actuators: result.hits });
		});
}

function doActuator(req, res){
	logger.info("Setting actuator page.");
	var data={};
	data.id = parseInt(req.param("id", null));
	data.type = parseInt(req.param("type", null));
	data.value = parseFloat(req.param("value", null));
	data.active = parseInt(req.param("active", null));

	modeladmin.setActuator(data, function(result){
			viewActuators(req, res);
	});
}

/*
 * VIEW viewRules
 */
function viewRules(req, res){
	logger.info("Viewing rules page.");
	modelrules.getRules(function(result){
		modelrules.getRulesSensors(function(dataRulesSensors){
			modelrules.getRulesActuators(function(dataRulesActuators){
				modelsensors.getSensorsList(function(dataSensors){
					modelsensors.getActuatorsList(function(dataActuators){
						res.render('rules', {title: "Règles", rest: rest, rules: result.hits, sensors: dataSensors.hits, actuators: dataActuators.hits, rulesSensors: dataRulesSensors.hits, rulesActuators: dataRulesActuators.hits});
					});
				});
			});
		});
		
	});

}

function addRule(req, res){
	logger.info("Adding rule page.");
	
	var idRegle = req.param("idRegle", null);
	var nom = req.param("nom", null);
	var createsAlert = req.param("createsAlert", null);
	
	var idCapteur = req.param("idCapteur", null);
	var typeMesure = req.param("typeMesure", null);
	var debIT = req.param("debIT", null);
	var finIT = req.param("finIT", null);
	
	var idActionneur = req.param("idActionneur", null);
	var valeur = req.param("valeur", null);
	var isActive = req.param("isActive", null);
	
	var data={};
	data.idRegle = idRegle;
	data.nom = nom;
	data.createsAlert = createsAlert;
	data.idCapteur = idCapteur;
	data.typeMesure = typeMesure;
	data.debIT = debIT;
	data.finIT = finIT;
	data.idActionneur = idActionneur;
	data.valeur = valeur;
	data.isActive = isActive;
	
	modelrules.addRule(data, function() {
		viewRules(req, res);
	});
}


exports.index = viewIndex;
exports.room = viewRoom;
exports.patient = viewPatient;
exports.login = viewLogin;
exports.notif = viewNotif;
exports.notfound = viewNotfound;
exports.help = viewHelp;
exports.add_sensor_patient = addSensorPatient;
exports.actuators = viewActuators;
exports.set_actuator = doActuator;
exports.rules = viewRules;
exports.add_rule = addRule;

