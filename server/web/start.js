var express = require("express");
var fs = require("fs");

var config = require("./config");
var services = require("./services");
var views = require("./views");
var authModule = require("./auth").authModule;


// Catch for all exception
process.on('uncaughtException', function (error) {
   console.log(error.stack);
});

var securityActivated = config.getProperty("security.auth");
var sslActivated = config.getProperty("security.ssl");

// REST Server config
var rest;
if(sslActivated) {
	rest = express.createServer({
		key: fs.readFileSync('security/server.key'),
		cert: fs.readFileSync('security/server.crt')
	});
} else {
	rest = express.createServer();
}
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
serviceHandler["/murs"] = services.murs;
serviceHandler["/bondsActuators"] = services.bondsActuators;
serviceHandler["/add_device"] = services.admin_add_devices;
serviceHandler["/remove_device"] = services.admin_remove_devices;
serviceHandler["/rules"] = services.rules;

for (var url in serviceHandler) {
	rest.post(url, serviceHandler[url]);
}

rest.listen(1337);

// HTML Server config
var html;
if(sslActivated) {
	html = express.createServer({
		key: fs.readFileSync('security/server.key'),
		cert: fs.readFileSync('security/server.crt')
	});
} else {
	html = express.createServer();
}

html.configure(function() {
	html.use(express.bodyParser());
	html.use(express.static(__dirname + '/public'));
	html.set('views', __dirname + '/views');
	html.set('view engine', 'ejs');
	
	// Stuff needed for sessions
	html.use(express.cookieParser());
	html.use(express.session(
		{ secret: "One does not simply walk into website." }));
});

// Different views of the HTML server :
viewHandler = {};
viewHandler["/(index)?"] = views.index;
viewHandler["/room"] = views.room;
viewHandler["/patient"] = views.patient;
viewHandler["/login"] = views.login;
viewHandler["/help"] = views.help;
viewHandler["/alerts"] = views.notif;
viewHandler["/add_sensor_patient"] = views.add_sensor_patient;
viewHandler["/add_rule"] = views.add_rule;
viewHandler["/actuators"] = views.actuators;
viewHandler["/rules"] = views.rules;
viewHandler["/set_actuator"] = views.set_actuator;

// Need to be put before * otherwise the star rule catches all the
// requests !
html.post("/auth", authModule.auth);
html.get("/logout", authModule.logout);

viewHandler["*"] = views.notfound;

// handler, user, password
authModule.init(viewHandler);

for (var url in viewHandler) {
	(securityActivated) ? html.get(url, authModule.checkAuth(url))
						: html.get(url, viewHandler[url]);
}

html.listen(8080);
