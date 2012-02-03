var http = require("http");
var url = require("url");
var staticserve = require("./staticserve");

function route(handlers, pathname, query, postData, resp) {
	if (typeof handlers[pathname] === 'function') {
		console.log("Route received for : " + pathname);
		handlers[pathname](query, postData, resp);
	} else	{
		console.log("No route found for : " + pathname + ". Trying static serving...");
		staticserve.serve(pathname, resp);
	}
}

function httpStart(port, handlers) {
	function onRequest(req, resp) {
		var urlObj = url.parse(req.url, true);	// Parse the url AND the query
		var pathname = urlObj.pathname;
		var query = urlObj.query;
		
		console.log("Request received for " + pathname);
		req.setEncoding("utf8");

		var postData = "";
		req.addListener("data", function(chunk) {
			postData += chunk;
		});

		req.addListener("end", function() {
			route(handlers, pathname, query, postData, resp);
		});
	}
	
	http.createServer(onRequest).listen(port);
	console.log("Webserver launched on port "+port);
}

exports.start = httpStart;
