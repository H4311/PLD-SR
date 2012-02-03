var fs = require("fs");
var path = require("path");

var htmlPath = "html";

// callback(exists, error, content)
function getStaticContent(pathname, callback) {
	
	pathname = htmlPath + pathname;
	
	// If this is a directory name without /, adds "/"
	if (path.basename(pathname).indexOf("/") == -1 && path.basename(pathname).indexOf(".") == -1) {
		pathname += "/";
	}

	if (pathname.substr(-1) === "/") {
		console.log("Directory found, serving index.html in this directory");
		pathname += "index.html";
	}
	
	path.exists(pathname, function(exists) {
		if (exists) {
			console.log("File " + pathname + " exists.");
			fs.readFile(pathname, function (error, content) {
				callback(exists, error, content);
			});
		} else {
			console.log("Path " + pathname + " not found.");
			callback(exists, null, null);
		}
	});	
}

function serveStatic(pathname, resp) {
	getStaticContent(pathname, function(exists, error, content) {
		if (!exists) {
			resp.writeHead(404);
			resp.end();
		} else {
			if (error) {
				console.log("Error 500 with file " + pathname);
				resp.writeHead(500);
				resp.end();
			} else {
				var extname = path.extname(pathname);
				switch(extname) {
				case '.js':
					contentType = "text/javascript";
					break;
				case '.css':
					contentType = "text/css";
					break;
				default:
					contentType = "text/html";
					break;
				}
				console.log("Static file " + pathname + " found");
				resp.writeHead(200, {"Content-type":contentType});
				resp.end(content, "utf-8");
			}
		}
	});
}

exports.serve = serveStatic;
exports.getStaticContent = getStaticContent;
