var config = {
	"logger" : {
		"level" : "debug"
	}
};

/* Object getProperty(String name)
 * Get the property of an object by specifying the path (like
 * "logger.level")
 */
function getProperty(name) {
	var path = name.split('.');
	var obj = config;
	for(var i in path) {
		var elem = path[i];
		if(!obj[elem]) return undefined;
		obj=obj[elem];
	}
	return obj;
}

exports.getProperty = getProperty;

