var fs = require("fs");
var path = require("path");

var htmlPath = "html";
var includePath = "include";

// callback(exists, error, content)
/* This function loads all the subfiles included in a file, replacing
 * one at a call (this is a recursive function). */
function nextReplacement(content, results, i, callback) {
	
	// If we are at the end of the matches, we just have to stop.
	if (i >= results.length) {
		callback(1, 0, content);
		return;
	}
	
	// Else, retrieves the file name, includes the file and loops to 
	// the next one.
	var subRegex = /{{include (.*)}}/;
	var fileName = results[i].match(subRegex)[1];
	getStaticContent("/" + includePath + "/" + fileName, function(exists, error, subcontent) {
		if (exists && !error) {
			content = content.toString().replace("{{include " + fileName + "}}", subcontent);
		} // if the file doesn't exist or there is an error on lecture,
		  // we just skip to the next inclusion.
		nextReplacement(content, results, i+1, callback); // recursive call
	});
}

// callback(exists, error, content)
/* Renders the includes into a file */
function renderInclude(content, callback) {
	var regex = /{{include ([a-zA-Z]*).html}}/g;
	var results = content.toString().match(regex);
	
	if (results) {
		nextReplacement(content, results, 0, callback);	
	} else {
		callback(1, 0, content);
	}
}

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
				if (!error) {
					renderInclude(content, callback);
				}
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
