var http = require("http");
var url = require("url");

function startServer(route, handle) {
	function onRequest(req, resp) {
		var urlParsed = url.parse(req.url, true);
		var pathname = urlParsed.pathname;
		var parameters = urlParsed.query;

		req.setEncoding("utf8");
		var postData = "";
		req.addListener("data", function(chunk) {
			postData += chunk;
		});
		req.addListener("end", function() {
			route(handle, pathname, resp, parameters, postData);
		});
	}
	
	http.createServer(onRequest).listen(1337);
	console.log("[SERVER] Webserver launched");
}

exports.start = startServer;
