var modelrooms = require("./model/rooms");
var modelpatients = require("./model/patients");

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

/*
 * VIEW Patient
 */
function viewPatient(req, res) {
	data = req.param("id", null);
	
	// Get model data
	modelpatients.getPatients(data, function(result) {
		var patientDetails=result.hits[0];
		res.render('patient', {title: "Patient "+patientDetails.nom, patientDetails: patientDetails});
	});
}

exports.index = viewIndex;
exports.room = viewRoom;
exports.patient = viewPatient;
