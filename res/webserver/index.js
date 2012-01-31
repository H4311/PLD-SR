var server = require("./server");
var router = require("./router");
var rh = require("./requestHandlers");

handle = {};
handle["/"] = rh.start;
handle["/start"] = rh.start;
handle["/upload"] = rh.upload;
handle["/captors"] = rh.captorsError;

server.start(router.route, handle);
