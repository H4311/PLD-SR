var modelsensors = require("./model/sensors");
var modelpatients = require("./model/patients");
var modelrooms = require("./model/rooms");
var modeladmin = require("./model/admin");
var modelalerts = require("./model/alerts");
var modelmurs = require("./model/murs");
var modelbondsActuators = require("./model/bondsActuators");
var modelrules = require("./model/rules");

var logger = require("./logger");

function error(code, resp) {
	var result = {};
	result.error = {};
	result.error.code = code;
	
	switch(code) {
		case 0:
			result.error.msg = "Couldn't parse the JSON";
			break;
		case 1:
			result.error.msg = "Unsupported HTTP/1.1 method for this service";
			break;
		default:
			result.error.msg = "Unknow error";
	}
	
	logger.error("Error function with message : " + result.error.msg);
	var jsonResult = JSON.stringify(result);
	resp.end(jsonResult);
}

// Adds the header indicating all went sucessfully.
function writeHeaders(resp) {
	resp.header("Access-Control-Allow-Origin","*");
}

function parseRequest(req, names) {
	console.log(req.body);
	request = {}
	for (var n in names) {
		request[names[n]] = req.param(names[n], null);
	}
	console.log("Request : " + JSON.stringify(request))
	return request;
}

/*
 * SERVICE Sensors
 * Gets records from sensors, allows to specify an interval.
 */
function serviceSensors(req, resp) {
	logger.info("Service sensors.");
	writeHeaders(resp);
	
	data = parseRequest(req, ["sensors"]);
	// Get the response from the modelsensors layer :
	modelsensors.getSensorsRecords(data, function(result) {
		// Send the stringified json to client :
		resp.json(result);
	});
}

/*
 * SERVICE Actuators
 * Allows to pass values to actuators.
 */
function serviceActuators(req, resp) {
	logger.info("Service actuators.");
	writeHeaders(resp);
	
	request = parseRequest(req, ["id", "type", "active", "value"]);
	// Get the response from the modeladmin layer :
	modeladmin.setActuator(request, function(response) {
		// Send the stringified json to client :
		resp.json(response);
	});
}

/*
 * SERVICE list_sensors
 *
 * REQUEST :
 * ============================================================================
{
	“idPatient” : 112
}
OR
{
	“idRoom” : 112
}
OR
{
}
 * ============================================================================
 *
 * RESPONSE :
 * ============================================================================
{
	“sensors” : [
			{
				“...” : “...”,	// Cf. BDD
				“...” : “...”
			},
			{
				“...” : “...”,
				“...” : “...”
			}
	]
}
 * ============================================================================
 */
function serviceListSensors(req, resp) {
	logger.info("Service list sensors.");
	writeHeaders(resp);
	
	request = parseRequest(req, ["idPatient", "idRoom"]);
	
	if(request.idPatient) {
		logger.debug("Service list sensors : id patient = " + idPatient);
		// Get the response from the modelsensors layer :
		modelsensors.getSensorsListByPatient(request.idPatient, function(response) {
			// Send the stringified json to client :
			resp.json(response);
		});
	} else if(request.idRoom) {
		logger.debug("Service list sensors : id room = " + idRoom);
		// Get the response from the modelsensors layer :
		modelsensors.getSensorsListByRoom(request.idRoom, function(response) {
			// Send the stringified json to client :
			resp.json(response);
		});
	} else {
		logger.debug("Service list sensors : getting all sensors");
		// Get the response from the modelsensors layer :
		modelsensors.getSensorsList(function(response) {
			// Send the stringified json to client :
			resp.json(response);
		});
	}
}

/*
 * SERVICE list_actuators
 * Gets list of actuators.
 */
function serviceListActuators(req, resp) {
	logger.info("Service list actuators.");
	writeHeaders(resp);
	
	// Get the response from the modelsensors layer :
	modelsensors.getActuatorsList(function(response) {
		// Send the stringified json to client :
		resp.json(response);
	});
}

/*
 * SERVICE admin_devices
 * Allows to add/remove sensors/actuators.
 */
function serviceAdminAddDevices(req, resp) {
	logger.info("Service admin add devices.");
	writeHeaders(resp);
	
	request = parseRequest(req, ["id", "type"]);
	
	// Get the response from the modeladmin layer :
	modeladmin.addDevice(request, function(response) {
		// Send the stringified json to client :
		resp.json(response);
	});
}

function serviceAdminRemoveDevices(req, resp) {
	logger.info("Service admin remove devices.");
	writeHeaders(resp);
	
	request = parseRequest(req, ["id"]);
	
	// Get the response from the modeladmin layer :
	modeladmin.removeDevice(request, function(response) {
		// Send the stringified json to client :
		resp.json(response);
	});
}


/* SERVICE Rules
 */
function serviceAddRule(req, resp) {
	logger.info("Service add rules.");
	writeHeaders(resp);

	request = parseRequest(req, ["nom", "createsAlert", "idCapteur", "debIT", "finIT", "idActionneur", "valeur", "isActive"]);
	// Get the response from the modelrules layer :
	modelrules.addRule(request, function(response) {
		// Send the stringified json to client :
		resp.json(response);
	});
	
}


/*
 * SERVICE Patients
 * Allows to retrieve patients data.
 */
function servicePatients(req, resp) {
	logger.info("Service patients.");
	writeHeaders(resp);
	
	data = parseRequest(req, ["roomId", "id"]);
	
	modelpatients.getPatients(data, function(result) {
		resp.json(result);
	});
}

/*
 * SERVICE Rooms
 * Allows to retrieve rooms data.
 */
function serviceRooms(req, resp) {
	logger.info("Service rooms.");
	writeHeaders(resp);
	data = parseRequest(req, ["id"]);
	modelrooms.getRooms(data, function(result) {
		resp.json(result);
	});
}

/*
 * SERVICE Murs
 * Allows to retrieve murs data.
 */
function serviceMurs(req, resp) {
	logger.info("Service murs.");
	writeHeaders(resp);
	// Parse the json DATA request
	request = parseRequest(req, ["id"]);
	if(!request) {
		error(0, resp);
		return;
	}	
	
	modelmurs.getMurs(request, function(result) {
			var strResult = JSON.stringify(result);
			resp.end(strResult);
	});
}

/*
 * SERVICE Alerts
 * Allows to retrieve alerts from the database.
 */
function serviceAlerts(req, resp) {
	logger.info("Service alerts.");
	writeHeaders(resp);

	request = parseRequest(req, ["from", "to"]);
	
	modelalerts.getAlerts(request, function(result) {
		resp.json(result);
	});
}

/*
 * SERVICE BondsActuators
 * Allows to retrieve the connection between actuators and subjects from the database.
 */
function serviceBondsActuators(req, resp) {
	logger.info("Service bonds actuators.");
	writeHeaders(resp);

	// Parse the json DATA request
	request = parseRequest(req, ["id", "subjectId"]);
	if(!request) {
		error(0, resp);
		return;
	}
	
	modelbondsActuators.getBondsActuators(request, function(result) {
			var strResult = JSON.stringify(result);
			resp.end(strResult);
	});
}

exports.sensors = serviceSensors;
exports.actuators = serviceActuators;
exports.list_sensors = serviceListSensors;
exports.list_actuators = serviceListActuators;
exports.admin_add_devices = serviceAdminAddDevices;
exports.admin_remove_devices = serviceAdminRemoveDevices;
exports.patients = servicePatients;
exports.rooms = serviceRooms;
exports.murs = serviceMurs;
exports.alerts = serviceAlerts;
exports.bondsActuators = serviceBondsActuators;
exports.rules = serviceAddRule;
