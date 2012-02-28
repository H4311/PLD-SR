var modelrooms = require("./model/rooms");

function error(code, resp) {
	var result = {};
	result.error = {};
	result.error.code = code;
	
	switch(code) {
		case 0:
			result.error.msg = "Couldn't parse the JSON";
			break;
		case 1:
			result.error.msg = "Unsupported HTTP/1.1 method for this service";
			break;
		default:
			result.error.msg = "Unknow error";
	}
	
	var jsonResult = JSON.stringify(result);
	resp.end(jsonResult);
}

function parseRequest(req, names) {
	request = {}
	for (var n in names) {
		request[names[n]] = req.param(names[n], null);
	}
	console.log("Request : " + JSON.stringify(request))
	return request;
}

/*
 * VIEW Room
 */
function viewRoom(req, res) {
	data = parseRequest(req, ["id"]);
	// Get model data
	modelrooms.getRooms(data, function(result) {
		var roomDetails=result.hits[0];
		res.render('room', {title: "Chambre", roomDetails: roomDetails});
	});
}


/*
 * SERVICE Rooms
 * Allows to retrieve rooms data.
 */
/*function serviceRooms(req, resp) {
	writeHeaders(resp);
	data = parseRequest(req, ["id"]);
	modelrooms.getRooms(data, function(result) {
		resp.json(result);
	});
}*/


exports.room = viewRoom;
