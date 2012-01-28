var server = require("./server");
var router = require("./router");
var rh = require("./requestHandlers");

handle = {};
handle["/"] = rh.start;
handle["/start"] = rh.start;
handle["/upload"] = rh.upload;

server.start(router.route, handle);
