var http = require("http");
var url = require("url");

function startServer(route, handle) {
	function onRequest(req, resp) {
		var pathname = url.parse(req.url).pathname;
		console.log("Request received for " + pathname);
		req.setEncoding("utf8");

		var postData = "";
		req.addListener("data", function(chunk) {
			postData += chunk;
		});

		req.addListener("end", function() {
			route(handle, pathname, resp, postData);
		});
	}
	
	http.createServer(onRequest).listen(1337);
	console.log("Webserver launched");
}

exports.start = startServer;
