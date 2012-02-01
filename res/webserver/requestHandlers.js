var qs = require("querystring");
var staticserve = require("./staticserve");

function start(resp, parameters, post) {
	console.log("Start");
	staticserve.serve("/index.html", resp);
}

function upload(resp, parameters, post) {
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

function captors(resp, parameters, post) {
	resp.writeHead(200, {"Content-type" : "application/json"});

	var ids = parameters["ids[]"]; // retrieves all the ids we wanna read 

	console.log("Get data received : " + parameters["ids[]"]);
	var tab = new Array();
	if (ids == undefined) {
		// returns all the sensor values
		console.log("Captors : reads all values");
		var j = 0;
		var tab = [2, 4, 8, 15, 16, 23, 42]; 
		for (var i in tab){
			tab[j++] = new Sensor(tab[i]);	
		}
	} else {
		console.log("Captors : reads particular values");
		for (var i in ids) {
			sensor = new Sensor(i);
			tab[i] = sensor;
		}
	}
	resp.write(JSON.stringify(tab));
	resp.end();
}

exports.start = start;
exports.upload = upload;
exports.captors = captors;
