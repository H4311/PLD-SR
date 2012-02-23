var express = require("express");

var services = require("./services");

// REST Server config
var rest = express.createServer();
rest.configure(function() {
	rest.use(express.bodyParser()); // retrieves automatically req bodies
	rest.use(rest.router); // manually defines the routes
});

serviceHandler = {};
serviceHandler["/sensors"] = services.sensors;
serviceHandler["/actuators"] = services.actuators;
serviceHandler["/list_sensors"] = services.list_sensors;
serviceHandler["/list_actuators"] = services.list_actuators;
serviceHandler["/patients"] = services.patients;
serviceHandler["/rooms"] = services.rooms;
serviceHandler["/alerts"] = services.alerts;

for (var url in serviceHandler) {
	rest.post(url, serviceHandler[url]);
}
rest.put("/admin_devices", services.admin_add_devices);
rest.delete("/admin_devices", services.admin_remove_devices);

rest.listen(1337);

// HTML Server config
var html = express.createServer();

html.configure(function() {
	html.use(express.static(__dirname + '/public'));
	html.set('views', __dirname + '/views');
	html.set('view engine', 'ejs');
});

// Different views of the HTML server :

html.get('/(index)?', function(req, res) {
	res.render('index', {layout: false});
});

html.get('/room', function(req, res) {
	var roomId = req.param("id", null);
	res.render('room', {layout: false, roomId: roomId});
});

html.listen(8080);
