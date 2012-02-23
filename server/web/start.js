var server = require("./httpserver");
var services = require("./services");

htmlHandler = {};

serviceHandler = {};
serviceHandler["/sensors"] = services.sensors;
serviceHandler["/actuators"] = services.actuators;
serviceHandler["/list_sensors"] = services.list_sensors;
serviceHandler["/list_actuators"] = services.list_actuators;
serviceHandler["/admin_devices"] = services.admin_devices;
serviceHandler["/patients"] = services.patients;
serviceHandler["/rooms"] = services.rooms;
serviceHandler["/alerts"] = services.alerts;
serviceHandler["/murs"] = services.murs;

// Start HTML Web Server :
server.start(8080, htmlHandler, server.routeHttp);

// Start REST Web Service :
server.start(1337, serviceHandler, server.routeService);
