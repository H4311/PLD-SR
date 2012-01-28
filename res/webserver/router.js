var serveStatic = require("./staticserve").serve;

function route(handle, pathname, resp, postData) {
	console.log("Route received : " + pathname);
	if (typeof handle[pathname] === 'function') {
		return handle[pathname](resp, postData);
	} else {
		console.log("No route found for " + pathname + ". Trying static serving...");
		//resp.writeHead(404, {"Content-type":"text/plain"});
		//resp.end("404, not found");
		serveStatic(pathname, resp);
	}
}

exports.route = route;
