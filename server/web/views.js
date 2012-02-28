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


/*
 * VIEW Login
 */
function viewLogin(req, res) {
	next = req.param("next", null);
	res.render('login', {title: "Login", next: next, error: null});
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
exports.login = viewLogin;
