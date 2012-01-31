var qs = require("querystring");
var staticserve = require("./staticserve");

function start(resp, post) {
	console.log("Start");
	staticserve.serve("/index.html", resp);
}

function upload(resp, post) {
	console.log("Upload");
	resp.writeHead(200, {"Content-type":"text/html"});
	staticserve.getStaticContent("/text.html", function(error, exists, content) {
		text = content.toString().replace("{{response}}", qs.parse(post).text);
		resp.end(text);
	});
}

function Sensor(id) {
	this.id = id;
	this.value = Math.random();
}

function captorsError(resp, post) {
	resp.writeHead(500, {"Content-type" : "text/plain"});
	resp.end("No id was given.");
}

function captors(resp, post, id) {
	resp.writeHead(200, {"Content-type" : "application/json"});
	sensor = new Sensor(id); 
	var jsonSensor = JSON.stringify(sensor);
	resp.end(jsonSensor);
}

exports.start = start;
exports.upload = upload;
exports.captorsError = captorsError;
exports.captors = captors;
