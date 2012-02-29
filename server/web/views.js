var modelrooms = require("./model/rooms");
var modelpatients = require("./model/patients");
var modelalerts = require("./model/alerts");

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
	res.render('login', {title: "Login", next: next});
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


/*
 * VIEW Notifications
 */
function viewNotif(req, res) {
	//TODO: Get the last 24h notifs
	var before = new Date(0);
	var data = {"from":  dateToString(before)};
	
	// Get model data
	modelalerts.getAlerts(data, function(result) {
		var notifs = result;
		res.render('alerts', {title: "Notifications", notifs: notifs });
	});
}


function dateToString(date) {
	var s = "";
	s += date.getFullYear();
	s += "/";
	s += twoDigits(date.getMonth()+1);
	s += "/";
	s += twoDigits(date.getDate());
	s += " ";
	s += twoDigits(date.getHours());
	s += ":";
	s += twoDigits(date.getMinutes());
	s += ":";
	s += twoDigits(date.getSeconds());
	return s;
}

function twoDigits(nb) {
	var retour = nb < 10 ? "0" + nb : "" + nb;
	return retour;
}


exports.index = viewIndex;
exports.room = viewRoom;
exports.patient = viewPatient;
exports.login = viewLogin;
exports.notif = viewNotif;
