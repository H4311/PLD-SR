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
	res.render('login', {title: "Login", next: next});
}

exports.index = viewIndex;
exports.room = viewRoom;
exports.login = viewLogin;
