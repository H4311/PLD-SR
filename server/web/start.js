var server = require("./httpserver");
var services = require("./services");

htmlHandler = {};

serviceHandler = {};
serviceHandler["/sensors"] = services.sensors;
serviceHandler["/actuators"] = services.actuators;

// Start HTML Web Server :
server.start(8080, htmlHandler);

// Start REST Web Service :
server.start(1337, serviceHandler);
