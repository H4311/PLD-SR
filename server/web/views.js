var modelrooms = require("./model/rooms");

/*
 * VIEW Index
 */
function viewIndex(req, res) {
	res.render('index', {title: "Accueil"});
}

/*
 * VIEW Room
 */
function viewRoom(req, res) {
	data = req.param("id", null);
	
	// Get model data
	modelrooms.getRooms(data, function(result) {
		var roomDetails=result.hits[0];
		res.render('room', {title: "Chambre", roomDetails: roomDetails});
	});
}

exports.index = viewIndex;
exports.room = viewRoom;
