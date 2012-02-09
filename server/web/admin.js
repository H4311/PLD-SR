
var net = require('net');

function connectClient() {
	return net.connect(1234, "localhost");
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
		console.log("[addDevice] Connected to server");
		client.write(JSON.stringify(query));
	});
}

function removeDevice(param, callback) {
	// Construct the query :
	var query = {};
		query.a = 2;
		query.i = param.id;
		
	// Send the query :
	var client = connectClient();
	client.on("connect", function() {
		console.log("[addDevice] Connected to server");
		client.write(JSON.stringify(query));
	});
}

exports.addDevice = addDevice;
exports.removeDevice = removeDevice;
