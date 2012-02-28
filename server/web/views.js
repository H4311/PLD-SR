var modelrooms = require("./model/rooms");
var modelpatients = require("./model/patients");
var modelsensors = require("./model/sensors");

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
        if(!roomDetails) {
        	res.render('404', {title: "Erreur"});
        	return;
        }
        
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
	var id = req.param("id", null);
	var req = {"id":id};
	
	// Get model data
	modelpatients.getPatients(req, function(result) {
		var patientDetails=result.hits[0];
		if(!patientDetails) {
        	res.render('404', {title: "Erreur"});
        	return;
        }
		
		modelsensors.getSensorsListByPatient(id, function(result) {
            var sensors = result.hits;
            var measures = [];
            
            for(var i in sensors) {
            	var sensor = sensors[i];
            	var types = modelsensors.getRecordtypesBySensortype(sensor.type);
            	for(var j in types) {
            		var measure = {
            			sensorId : sensor.id,
            			sensorType : sensor.type,
            			recordType : types[j],
            			name : modelsensors.recordtypeToString(types[j])
            		};
            		measures.push(measure);
            	}
            }
            res.render('patient', {title: "Patient "+patientDetails.nom, patientDetails: patientDetails, measures: measures});
        });
	});
}

exports.index = viewIndex;
exports.room = viewRoom;
exports.patient = viewPatient;
exports.login = viewLogin;
