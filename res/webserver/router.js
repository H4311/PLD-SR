var serveStatic = require("./staticserve").serve;
var captors = require("./requestHandlers").captors;

function route(handle, pathname, resp, postData) {
	console.log("Route received : " + pathname);
	var captorName = "/captors";

	if (typeof handle[pathname] === 'function') {
		handle[pathname](resp, postData);
	} else if (pathname.substr(0, captorName.length) === captorName) {
		var id = pathname.substr(captorName.length+1, pathname.length - captorName.length);
		console.log("Read captor " + id);
		captors(resp, postData, id);
	} else	{
		console.log("No route found for " + pathname + ". Trying static serving...");
		//resp.writeHead(404, {"Content-type":"text/plain"});
		//resp.end("404, not found");
		serveStatic(pathname, resp);
	}
}

exports.route = route;
