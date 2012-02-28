var modelrooms = require("./model/rooms");
var modelpatients = require("./model/patients");

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
    var id = req.param("id", null);
    var req = {"id":id};
   
    // Get rooms details
    modelrooms.getRooms(req, function(result) {
        var roomDetails=result.hits[0];
        var req = {"roomId":id};
       
        // Get patients list
        modelpatients.getPatients(req, function(result) {
            var patients = result.hits;
            res.render('room', {title: "Chambre", roomDetails: roomDetails, patients: patients});
        });
    });
}

exports.room = viewRoom;
