var modelsensors = require("./sensors");
var modelpatients = require("./patients");
var modeladmin = require("./admin");

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
	
	var result = {};
	
	var strResult = JSON.stringify(result);
	resp.end(strResult);
}

/*
 * SERVICE Admin
 * Allows to add/remove sensors/actuators.
 */
function serviceAdmin(method, query, data, resp) {
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
		case "POST":
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
 * Allows to add/remove sensors/actuators.
 */
function servicePatients(method, query, data, resp) {
	writeHeaders(resp);
	
	// Parse the json DATA request
	/*
	request = JSON.parse(data);
	if(!request) {
		error(0, resp);
		return;
	}
	* */
	
	modelpatients.getPatients(function(result) {
		var strResult = JSON.stringify(result);
		resp.end(strResult);
	});
}

exports.sensors = serviceSensors;
exports.actuators = serviceActuators;
exports.patients = servicePatients;
