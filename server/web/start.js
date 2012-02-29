var express = require("express");

var services = require("./services");
var views = require("./views");
var authModule = require("./auth").authModule;

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
serviceHandler["/murs"] = services.murs;
serviceHandler["/bondsActuators"] = services.bondsActuators;

for (var url in serviceHandler) {
	rest.post(url, serviceHandler[url]);
}
rest.put("/admin_devices", services.admin_add_devices);
rest.delete("/admin_devices", services.admin_remove_devices);

rest.listen(1337);

// HTML Server config
var html = express.createServer();

html.configure(function() {
	html.use(express.bodyParser());
	html.use(express.static(__dirname + '/public'));
	html.set('views', __dirname + '/views');
	html.set('view engine', 'ejs');
	html.use(express.cookieParser()); // for session
	html.use(express.session({ secret: "One does not simply walk into website." }));
});

// Different views of the HTML server :
viewHandler = {};
viewHandler["/(index)?"] = views.index;
viewHandler["/room"] = views.room;
viewHandler["/patient"] = views.patient;
viewHandler["/login"] = views.login;
viewHandler["/alerts"] = views.notif;

// handler, user, password
// authModule.init(viewHandler, "rithm", "th!$_!$_th3_rythm_0f_th3_n!ght");

for (var url in viewHandler) {
	// html.get(url, authModule.checkAuth(url));
	html.get(url, viewHandler[url]);
}
//html.post("/auth", authModule.auth);
//html.get("/logout", authModule.logout);

html.listen(8080);
