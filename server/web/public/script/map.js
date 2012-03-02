// GLOBAL VARS :
var Rooms = new Array();
var Patients = new Array();
var Sensors = new Array();
var Actuators = new Array();


// FUNCTIONS TO INITIALIZE :
function InitializeRooms(data) {
	var rooms = data.hits;
	for (var i = 0; i < rooms.length; i++) {
		// Load walls & create Room :
		$.ajax({
			type: 'POST',
			url: rest+'/murs',
			data: {"id": rooms[i].id},
			success: function(data) {
				var walls = new Array();
				for (var j = 0; j<data.hits.length; j++) {
					if (data.hits[j].isPorte) {
						walls[j] = new RithmObjects.Door(data.hits[j].x1, data.hits[j].y1, data.hits[j].x2, data.hits[j].y2);
					}
					else {
						walls[j] = new RithmObjects.Wall(data.hits[j].x1, data.hits[j].y1, data.hits[j].x2, data.hits[j].y2);
					}
				}
				Rooms[rooms[i].id] = new RithmObjects.Room(rooms[i].nom, walls); 	// Create Room
				BuildingGenerator.addRoom(rooms[i].id, Rooms[rooms[i].id]);	// Add to the canvas drawer
			},
			dataType: 'json',
			async:false
		});
	}
	BuildingGenerator.scale(BuildingGenerator.width/670, BuildingGenerator.height/450);
}

function InitializePatients(data) {
	var patients = data.hits;
	for (var i = 0; i < patients.length; i++) {
		Patients[patients[i].id] = new RithmObjects.Patient(patients[i].name, patients[i].isMan, patients[i].reasonHosp, patients[i].idRoom);
		Rooms[patients[i].idPiece].addPatient(Patients[patients[i].id]);
	}
}

function InitializeSensors(data) {
	var sensors = data.hits;
	var yesterday = new Date();
	yesterday.setDate(yesterday.getDate() - 1);
	for (var i = 0; i < sensors.length; i++) {
		// Creating the sensor :
		Sensors[sensors[i].id] = new RithmObjects.Sensor(sensors[i].type);
		// Creating the bonds with its subject :
		if (sensors[i].isGlobal != 0) { // Subject == Room
			Sensors[sensors[i].id].setSubject(sensors[i].idSujet, sensors[i].isGlobal);
			Rooms[sensors[i].idSujet].addSensor(Sensors[sensors[i].id]);
		}
		else { // Subject == Patient
			Sensors[sensors[i].id].setSubject(sensors[i].idSujet, sensors[i].isGlobal);
			Patients[sensors[i].idSujet].addSensor(Sensors[sensors[i].id]);		
		}
		// Seeking the values of the sensor :
		getSensorValues(sensors[i].id, InitializeMeasures, yesterday)
	}
}

function InitializeActuators(data) {
	var actuators = data.hits;
	for (var i = 0; i < actuators.length; i++) {
		Actuators[actuators[i].id] = new RithmObjects.Actuator(actuators[i].type);
	}
}

function InitializeBondsActuators(data) {
	var bonds = data.hits;
	for (var i = 0; i < bonds.length; i++) {
		// Creating the bonds with its subject :
		if (bonds[i].isGlobal != 0) { // Subject == Room
			Actuators[bonds[i].idActuator].addSubject(Rooms[bonds[i].idSujet].id, bonds[i].isGlobal);
			Rooms[bonds[i].idSubject].addActuator(Actuators[bonds[i].idActuator]);
		}
		else { // Subject == Patient
			Actuators[bonds[i].idActuator].addSubject(Patients[bonds[i].idSujet].id, bonds[i].isGlobal);
			Patients[bonds[i].idSubject].addActuator(Sensors[bonds[i].idActuator]);		
		}
	}
}

function InitializeMeasures(data) {
	for (var i in data.records) {
		var sensor = data.records[i];
		for (var j = 0; j < sensor.length; j++)  {
			Sensors[i].setMeasure(sensor[j]);
		}
	}
	BuildingGenerator.draw();
}

function UpdateMeasures() {
	
}

function Initialize() {
	// Load Rooms :
	var jqXHRRooms = $.ajax({
		type: 'POST',
		url: rest+'/rooms',
		data: {},
		success: InitializeRooms,
		dataType: 'json',
		async:false
	});
	// Load Patients :
	var jqXHRPatients = $.ajax({
		type: 'POST',
		url: rest+'/patients',
		data: {},
		success:  function(data) {
			// Waiting for the Patients & Rooms requests to finished (we need their values) :
			$.when(jqXHRRooms).then(InitializePatients(data) /* if success */, function() { alert('Loading Failed');} /* if failure */);
		},
		dataType: 'json',
		async:true
	});
	
	// Load Sensors :
	var jqXHRSensors = $.ajax({
		type: 'POST',
		url: rest+'/list_sensors',
		data: {},
		success: function(data) {
			// Waiting for the Patients & Rooms requests to finished (we need their values) :
			$.when(jqXHRRooms, jqXHRPatients).then(InitializeSensors(data) /* if success */, function() { alert('Loading Failed');} /* if failure */);
		},
		dataType: 'json',
		async:true
	});
	
	// Load Actuators :
	var jqXHRActuators = $.ajax({
		type: 'POST',
		url: rest+'/list_actuators',
		data: {},
		success: InitializeActuators,
		dataType: 'json',
		async:true
	});
	
	// Load Bonds between actuators and subjects :
	$.ajax({
		type: 'POST',
		url: rest+'/bondsActuators',
		data: {},
		success: function(data) {
			// Waiting for the Patients & Rooms & Actuators request to finished (we need their values) :
			$.when(jqXHRRooms, jqXHRPatients, jqXHRActuators).then(InitializeBondsActuators(data) /* if success */, function() { alert('Loading Failed');} /* if failure */);
		},
		dataType: 'json',
		async:true
	});	
	
	// Load Measures :
	$.ajax({
		type: 'POST',
		url: rest+'/sensors',
		data: {},
		success: function(data) {
			// Waiting for the Patients & Rooms & Actuators request to finished (we need their values) :
			$.when(jqXHRSensors).then(InitializeMeasures(data) /* if success */, function() { alert('Loading Failed');} /* if failure */);
		},
		dataType: 'json',
		async:true
	});		
	
	// Keep the measures up to date :
	function getLastMeasures() {
		var toDate = new Date();
		var strDate = getLastMeasures.lastUpdate.getTime();
		var req = {};
		req["sensors"] = [];
		for (var i in Sensors) {
			req["sensors"].push({ "id" : i, "from" : strDate});
		}
		getLastMeasures.lastUpdate = toDate; // Using the fact that JS functions can have attributes to store the last date.
		
		$.ajax({
			type: 'POST',
			url: rest+'/sensors',
			data: req,
			success: InitializeMeasures,
			dataType: 'json',
			async:true
		});	
	};
	getLastMeasures.lastUpdate = new Date(0);
	setInterval(getLastMeasures,2000);
}


// MOTOR :

var BuildingGenerator = {

	author : "Aldream - Benjamin Planche",
	version : "0.0.1",

	// ---------------------
	// 		ATTRIBUTES
	// ---------------------
	roomLayer : new Kinetic.Layer(),
	pathLayer : new Kinetic.Layer(),
	warningLayer : new Kinetic.Layer(),
	roomShapes : {},
	warningShapes : {},
	wantedMeasure : "3",
	leftOffset : 0,
	topOffset : 0,
	
	// ---------------------
	// 		   STYLE
	// ---------------------
	lineWidthWall : 2,
	lineWidthDoor : 1,
	colorWall : "#000",
	colorDoor : "brown",
	lineWidthWallWarning : 5,
	colorWallWarning : "red",
	
	colorArrays: { "3" : [ {red:0,green:0,blue:255}, {red:0,green:255,blue:255}, {red:0,green:255,blue:0}, {red:255,green:255,blue:0}, {red:255,green:0,blue:0}], "4" :[ {red:214,green:178,blue:52}, {red:255,green:255,blue:255}, {red:56,green:148,blue:186}], "5" : [ {red:69,green:57,blue:138}, {red:255,green:244,blue:61}], "8":[ {red:172,green:255,blue:255}, {red:100,green:90,blue:84}]},
	
	unitArrays: { "3" : "°c", "4" : "%", "5" : "lx", "8":"pm"},
	
	minArrays: { "3" : -1, "4" : -1, "5" : -1, "8": 299},
	maxArrays: { "3" : 41, "4" : 101, "5" : 3001, "8": 2001},
	
	// draw : function() {
		// for (var i = 0; i < this.rooms.length; i++) {
			// rooms[i].draw();
		// }
	// }

	
	// ---------------------
	// 	     FUNCTION
	// ---------------------
	
	setStage : function SetStage(canvasId, width, height) {
		this.stage = new Kinetic.Stage(canvasId, width, height);
		this.width = width;
		this.height = height;
		this.leftOffset = $('#'+canvasId).offset().left+4;
		this.topOffset = $('#'+canvasId).offset().top+12;

		this.stage.add(this.roomLayer);
		this.stage.add(this.pathLayer);
		this.stage.add(this.warningLayer);
		
		drawGradient(document.getElementById('scale'), this.minArrays["3"], this.maxArrays["3"], this.colorArrays["3"], 8, this.unitArrays["3"], '');
	},
	
	addRoom : function AddRoom(id, room) {
		this.roomShapes[id] = new RithmViews.RoomShape(id, room);
		var p = new RithmViews.RoomPath(room);
		this.roomLayer.add(this.roomShapes[id]);
		this.pathLayer.add(p);
	},
	
	addWarning : function AddWarning(id, warning) {
		this.warningShapes[id] = [new RithmObjects.WarningCircle(id, warning), new RithmObjects.WarningMark(id, warning)];
		this.warningLayer.add(this.warningShapes[id][0]);
		this.warningLayer.add(this.warningShapes[id][1]);
	},
	
	removeWarning : function RemoveWarning(id) {
		this.warningLayer.remove(this.warningShapes[id][0]);
		this.warningLayer.remove(this.warningShapes[id][1]);
		this.warningShapes[id][1].warning.room.warning--;
		this.warningShapes[id][1] = 0;
		this.warningShapes[id][2] = 0;
		this.warningShapes[id] = 0;
		this.warningLayer.draw();
		this.pathLayer.draw();
	},
	
	draw : function Draw() {
		this.roomLayer.draw();
		this.pathLayer.draw();
		this.warningLayer.draw();
	},
	
	scale : function Scale(scaX, scaY) {
		for (var i in this.roomShapes) {
			this.roomShapes[i].room.scale(scaX, scaY);
		}
	}
	
};

