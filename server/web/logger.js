var config = require("./config");

var levels = {
	"error"	: 0,
	"warn"	: 1,
	"info"	: 2,
	"debug"	: 3
};

var currentLevel = getLevel(config.getProperty("logger.level"));
var printDate = config.getProperty("logger.printDate");

/* int getLevel(String strLevel)
 * Converts the String to the code that identifies the level
 */
function getLevel(strLevel) {
	return levels[strLevel.toLowerCase()];
}

/* void display(String strLevel, String message)
 * Displays the message only if his level is <= to the current level
 */
function display(strLevel, message) {
	var level = getLevel(strLevel);
	if(level > currentLevel) return;
	var date = printDate ? "[" + new Date() + "]" : "";
	console.log("["+strLevel+"]" + date + "\t"+message);
}

/* These functions generate different levels of logs...
 */
function error(message) {
	display("error", message);
}
function warn(message) {
	display("warn", message);
}
function info(message) {
	display("info", message);
}
function debug(message) {
	display("debug", message);
}

exports.error = error;
exports.warn = warn;
exports.info = info;
exports.debug = debug;
