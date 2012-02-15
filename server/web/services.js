var modelsensors = require("./model/sensors");
var modelpatients = require("./model/patients");
var modelrooms = require("./model/rooms");
var modeladmin = require("./model/admin");

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
	
	var jsonResult = JSON.stringify(result);
	resp.end(jsonResult);
}

// Adds the header indicating all went sucessfully.
function writeHeaders(resp) {
	resp.writeHead(200, {"Content-type" : "application/json", 
			     "Access-Control-Allow-Origin":"*"});
}

/*
 * SERVICE Sensors
 * Gets records from sensors, allows to specify an interval.
 */
function serviceSensors(method, query, data, resp) {
	writeHeaders(resp);
	
	// Parse the json request in data :
	request = JSON.parse(data);
	if(!request) {
		error(0, resp);
		return;
	}
	
	// Get the response from the modelsensors layer :
	modelsensors.getSensorsRecords(request, function(response) {
		// Send the stringified json to client :
		var strResponse = JSON.stringify(response);
		resp.end(strResponse);
	});
}

/*
 * SERVICE Actuators
 * Allows to pass values to actuators.
 */
function serviceActuators(method, query, data, resp) {
	writeHeaders(resp);
	
	// Parse the json DATA request
	request = JSON.parse(data);
	if(!request) {
		error(0, resp);
		return;
	}
	
	// Get the response from the modeladmin layer :
	modeladmin.setActuator(request, function(response) {
		// Send the stringified json to client :
		var strResponse = JSON.stringify(response);
		resp.end(strResponse);
	});
}

/*
 * SERVICE list_sensors
 *
 * REQUEST :
 * ============================================================================
{
	“id” : 112
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
function serviceListSensors(method, query, data, resp) {
	writeHeaders(resp);
	
	if(data.id) {
		// Get the response from the modelsensors layer :
		modelsensors.getSensorsListByPatient(data.id, function(response) {
			// Send the stringified json to client :
			var strResponse = JSON.stringify(response);
			resp.end(strResponse);
		});
	} else {
		// Get the response from the modelsensors layer :
		modelsensors.getSensorsList(function(response) {
			// Send the stringified json to client :
			var strResponse = JSON.stringify(response);
			resp.end(strResponse);
		});
	}
}

/*
 * SERVICE list_actuators
 * Gets list of actuators.
 */
function serviceListActuators(method, query, data, resp) {
	writeHeaders(resp);
	
	// Get the response from the modelsensors layer :
	modelsensors.getActuatorsList(function(response) {
		// Send the stringified json to client :
		var strResponse = JSON.stringify(response);
		resp.end(strResponse);
	});
}

/*
 * SERVICE admin_devices
 * Allows to add/remove sensors/actuators.
 */
function serviceAdminDevices(method, query, data, resp) {
	writeHeaders(resp);
	
	// Parse the json DATA request
	request = JSON.parse(data);
	if(!request) {
		error(0, resp);
		return;
	}
	
	var adminfct;
	switch(method) {
		case "PUT":
			adminfct = modeladmin.addDevice;
			break;
		case "DELETE":
			adminfct = modeladmin.removeDevice;
			break;
		default:
			error(1, resp);
			return;
	}
	
	// Get the response from the modeladmin layer :
	adminfct(request, function(response) {
		// Send the stringified json to client :
		var strResponse = JSON.stringify(response);
		resp.end(strResponse);
	});
}

/*
 * SERVICE Patients
 * Allows to retrieve patients data.
 */
function servicePatients(method, query, data, resp) {
	writeHeaders(resp);

	// Parse the json DATA request
	request = JSON.parse(data);
	if(!request) {
		error(0, resp);
		return;
	}	
	
	modelpatients.getPatients(request, function(result) {
			var strResult = JSON.stringify(result);
			resp.end(strResult);
	});
}

/*
 * SERVICE Rooms
 * Allows to retrieve rooms data.
 */
function serviceRooms(method, query, data, resp) {
	writeHeaders(resp);

	// Parse the json DATA request
	request = JSON.parse(data);
	if(!request) {
		error(0, resp);
		return;
	}	
	
	modelrooms.getRooms(request, function(result) {
			var strResult = JSON.stringify(result);
			resp.end(strResult);
	});
}

/*
 * SERVICE Alerts
 * Allows to retrieve alerts from the database.
 */
function serviceAlerts(method, query, data, resp) {
	writeHeaders(resp);

	// Parse the json DATA request
	request = JSON.parse(data);
	if(!request) {
		error(0, resp);
		return;
	}
	
	modelrooms.getAlerts(request, function(result) {
			var strResult = JSON.stringify(result);
			resp.end(strResult);
	});
}

exports.sensors = serviceSensors;
exports.actuators = serviceActuators;
exports.list_sensors = serviceListSensors;
exports.list_actuators = serviceListActuators;
exports.admin_devices = serviceAdminDevices;
exports.patients = servicePatients;
exports.rooms = serviceRooms;
exports.alerts = serviceAlerts;
