var server = require("./server");
var router = require("./router");
var rh = require("./requestHandlers");

handle = {};
handle["/"] = rh.start;
handle["/captors"] = rh.captors;

server.start(router.route, handle);
