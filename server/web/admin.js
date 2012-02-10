
var net = require('net');

function connectClient() {
	return net.createConnection(1234, "localhost");
}

/*
 * REQUEST :
 * ============================================================================
{
    “id” : “111111”,
    “type” : “1ZJU928”
} ============================================================================
 *
 * RESPONSE :
 * ============================================================================
{
    “state” : “ok”
} ============================================================================
 */
function addDevice(param, callback) {
	// Construct the query :
	var query = {};
		query.a = 1;
		query.i = param.id;
		query.t = param.type;
		
	// Send the query :
	var client = connectClient();
	client.on("connect", function() {
		console.log("[addDevice] Connected to the server");
		client.write(JSON.stringify(query), function() {
			console.log("[removeDevice] message sent to the server");
			// Construct json response :
			var response = {};
			response.status = "ok";
			callback(response);
			client.end();
		});
	});
}

/*
 * REQUEST :
 * ============================================================================
{
    “id” : “111111”,
    “type” : “1ZJU928”
} ============================================================================
 *
 * RESPONSE :
 * ============================================================================
{
    “state” : “ok”
} ============================================================================
 */
function removeDevice(param, callback) {
	// Construct the query :
	var query = {};
		query.a = 2;
		query.i = param.id;
		
	// Send the query :
	var client = connectClient();
	client.on("connect", function() {
		console.log("[removeDevice] Connected to the server");
		client.write(JSON.stringify(query), function() {
			console.log("[removeDevice] message sent to the server");
			// Construct json response :
			var response = {};
			response.status = "ok";
			callback(response);
			client.end();
		});
	});
}

/*
 * REQUEST :
 * ============================================================================
{
    “id” : “11111111”,
    "type" : "12321",
    “active” : “true”,
    “value” : 1.1
} ============================================================================
 *
 * RESPONSE :
 * ============================================================================
{
    “state” : “ok”
} ============================================================================
 */
function setActuator(param, callback) {
	// Construct the query :
	var query = {};
		query.a = 3;
		query.i = param.id;
		query.t = param.type;
		query.e = param.active ? 1 : 0;
		query.v = param.value;
		
	// Send the query :
	var client = connectClient();
	client.on("connect", function() {
		console.log("[setActuator] Connected to the server");
		client.write(JSON.stringify(query), function() {
			console.log("[setActuator] message sent to the server");
			// Construct json response :
			var response = {};
			response.status = "ok";
			callback(response);
			client.end();
		});
	});
}

exports.addDevice = addDevice;
exports.removeDevice = removeDevice;
exports.setActuator = setActuator;
