var exec = require("child_process").exec;
var qs = require("querystring");
var getStaticContent = require("./staticserve").getStaticContent;

function start(resp, post) {
	console.log("Start");

	var content = "empty";
	exec("ls -lah", function (error, stdout, stderr) {
		content = stdout;
		resp.writeHead(200, {"Content-type":"text/plain"});
		resp.end(content);
	});
}

function upload(resp, post) {
	console.log("Upload");
	resp.writeHead(200, {"Content-type":"text/html"});
	getStaticContent("/text.html", function(error, exists, content) {
		text = content.toString().replace("{{response}}", qs.parse(post).text);
		resp.end(text);
	});
}

exports.start = start;
exports.upload = upload;
