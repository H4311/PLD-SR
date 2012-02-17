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
// Indicates the place where are the static files
html.configure(function() {
	html.use(express.static(__dirname + '/html'));
	html.set('views', __dirname + '/views');
});

html.get('/room', function(req, res) {
	res.render('rooms.ejs', {layout: false, roomId: req.param("id", null)});
});

html.listen(8080);
