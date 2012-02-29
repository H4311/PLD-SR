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
	for (var i in data.hits) {
		var sensor = data.hits[i];
		for (var j = 0; j < sensor.length; j++)  {
			Sensors[i].setMeasure(sensor[j]);
		}
	}
}

function UpdateMeasures() {
	for (var i in Sensors) {
		var jqXHRRooms = $.ajax({
			type: 'POST',
			url: rest+'/sensors',
			data: {"sensors" : [ { "id" : i, "from" : /*TODO*/ 0}]},
			success: function(data) {
				var sensor = data.hits[0];
				for (var j = 0; j < sensor.length; j++)  {
					Sensors[i].setMeasure(sensor[j]);
				}
			},
			dataType: 'json',
			async:true
		});
	}
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
	//getSensorValues(idSensor, callback, from, to)
	//$.ajax({
	//	type: 'POST',
	//	url: rest+'/sensors',
	//	data: '{}',
	//	success: function(data) {
	//		// Waiting for the Patients & Rooms & Actuators request to finished (we need their values) :
	//		$.when(jqXHRSensors).then(InitializeMeasures(data) /* if success */, function() { alert('Loading Failed');} /* if failure */);
	//	},
	//	dataType: 'json',
	//	async:true
	//});		
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
	
	colorArrays: { "3" : [ {red:0,green:0,blue:255}, {red:0,green:255,blue:255}, {red:0,green:255,blue:0}, {red:255,green:255,blue:0}, {red:255,green:0,blue:0}], "4" :[ {red:214,green:178,blue:52}, {red:255,green:255,blue:255}, {red:56,green:148,blue:186}], "5" : [ {red:69,green:57,blue:138}, {red:255,green:244,blue:61}], "7":[ {red:172,green:255,blue:255}, {red:100,green:90,blue:84}]},
	
	unitArrays: { "3" : "°c", "4" : "%", "5" : "lx", "7":"pm"},
	
	minArrays: { "3" : 0, "4" : 0, "5" : 0, "7": 300},
	maxArrays: { "3" : 40, "4" : 100, "5" : 3000, "7": 2000},
	
	// draw : function() {
		// for (var i = 0; i < this.rooms.length; i++) {
			// rooms[i].draw();
		// }
	// }

	
	// ---------------------
	// 	     FUNCTION
	// ---------------------
	
	setStage : function SetStage(canvasId, width, height, offsetL, offsetT) {
		this.stage = new Kinetic.Stage(canvasId, width, height);
		this.leftOffset = offsetL;
		this.topOffset = offsetT;
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
	

// TEST :
	function draw() {
		// canvas = document.getElementById('buildingContainer');
		// canvas.width = window.innerWidth-120;
		// canvas.height = window.innerHeight-84;
		// var ctx = canvas.getContext('2d'); 
		
		
		
		var wall1 = new RithmObjects.Wall(10, 10, 100, 10);
		var wall21 = new RithmObjects.Wall(100, 10, 100, 40);
		var door = new RithmObjects.Door(100, 40, 100, 60);
		var wall22 = new RithmObjects.Wall(100, 60, 100, 100);
		var wall3 = new RithmObjects.Wall(100, 100, 10, 100);
		var wall4 = new RithmObjects.Wall(10, 100, 10, 10);

		door.isOpen = true;
		var walls = [wall1, wall21, door, wall22, wall3, wall4];

		var room = new RithmObjects.Room("Ch111", walls);
		
		var wall1_10 = new RithmObjects.Wall(10, 100, 100, 100);
		var wall21_10 = new RithmObjects.Wall(100, 100, 100, 150);
		var door_10 = new RithmObjects.Door(100, 150, 100, 170);
		var wall22_10 = new RithmObjects.Wall(100, 170, 100, 240);
		var wall3_10 = new RithmObjects.Wall(100, 240, 10, 240);
		var wall4_10 = new RithmObjects.Wall(10, 240, 10, 100);

		door_10.isOpen = false;
		var walls_10 = [wall1_10, wall21_10, door_10, wall22_10, wall3_10, wall4_10];

		var room10 = new RithmObjects.Room("Ch112", walls_10);
		
		var wall1_11 = new RithmObjects.Wall(10, 240, 100, 240);
		var wall21_11 = new RithmObjects.Wall(100, 240, 100, 270);
		var door_11 = new RithmObjects.Door(100, 270, 100, 290);
		var wall22_11 = new RithmObjects.Wall(100, 290, 100, 370);
		var wall3_11 = new RithmObjects.Wall(100, 370, 10, 370);
		var wall4_11 = new RithmObjects.Wall(10, 370, 10, 240);

		door_11.isOpen = true;
		var walls_11 = [wall1_11, wall21_11, door_11, wall22_11, wall3_11, wall4_11];

		var room11 = new RithmObjects.Room("Ch113", walls_11);
		
		var wall1_2 = new RithmObjects.Wall(130, 10, 270, 10);
		var wall2_2 = new RithmObjects.Wall(270, 10, 270, 100);
		var wall3_2 = new RithmObjects.Wall(270, 100, 130, 100);
		var wall41_2 = new RithmObjects.Wall(130, 100, 130, 60);
		var wall42_2 = new RithmObjects.Wall(130, 40, 130, 10);
		var door_2 = new RithmObjects.Door(130, 60, 130, 40);

		door_2.isOpen = true;
		var walls2 = [wall1_2, wall2_2, wall3_2, wall41_2, door_2, wall42_2];

		var room2 = new RithmObjects.Room("Ch114", walls2);
		
		var wall1_21 = new RithmObjects.Wall(130, 130, 300, 130);
		var wall2_21 = new RithmObjects.Wall(300, 130, 300, 240);
		var wall3_21 = new RithmObjects.Wall(300, 240, 130, 240);
		var wall41_21 = new RithmObjects.Wall(130, 240, 130, 180);
		var wall42_21 = new RithmObjects.Wall(130, 160, 130, 130);
		var door_21 = new RithmObjects.Door(130, 180, 130, 160);

		door_21.isOpen = true;
		var walls21 = [wall1_21, wall2_21, wall3_21, wall41_21, door_21, wall42_21];

		var room21 = new RithmObjects.Room("Ch115", walls21);
		
		var wall1_22 = new RithmObjects.Wall(130, 240, 300, 240);
		var wall2_22 = new RithmObjects.Wall(300, 240, 300, 340);
		var wall3_22 = new RithmObjects.Wall(300, 340, 130, 340);
		var wall41_22 = new RithmObjects.Wall(130, 340, 130, 300);
		var wall42_22 = new RithmObjects.Wall(130, 280, 130, 240);
		var door_22 = new RithmObjects.Door(130, 300, 130, 280);

		door_22.isOpen = true;
		var walls22 = [wall1_22, wall2_22, wall3_22, wall41_22, door_22, wall42_22];
		var room22 = new RithmObjects.Room("Ch116", walls22);
		
		var wall1_23 = new RithmObjects.Wall(360, 10, 530, 10);
		var wall2_23 = new RithmObjects.Wall(360, 100, 360, 10);
		var wall3_23 = new RithmObjects.Wall(530, 100, 360, 100);
		var wall41_23 = new RithmObjects.Wall(530, 60, 530, 100);
		var wall42_23 = new RithmObjects.Wall(530, 10, 530, 40);
		var door_23 = new RithmObjects.Door(530, 40, 530, 60);

		door_23.isOpen = true;
		var walls23 = [wall1_23, wall42_23, door_23, wall41_23, wall3_23, wall2_23];

		var room23 = new RithmObjects.Room("Ch117", walls23);
		
		var wall1_24 = new RithmObjects.Wall(330, 130, 530, 130);
		var wall2_24 = new RithmObjects.Wall(330, 240, 330, 130);
		var wall3_24 = new RithmObjects.Wall(530, 240, 330, 240);
		var wall41_24 = new RithmObjects.Wall(530, 180, 530, 240);
		var wall42_24 = new RithmObjects.Wall(530, 130, 530, 160);
		var door_24 = new RithmObjects.Door(530, 160, 530, 180);

		door_24.isOpen = true;
		var walls24 = [wall1_24, wall42_24, door_24, wall41_24, wall3_24, wall2_24];

		var room24 = new RithmObjects.Room("Ch118", walls24);
		
		var wall1_25 = new RithmObjects.Wall(330, 240, 530, 240);
		var wall2_25 = new RithmObjects.Wall(330, 340, 330, 240);
		var wall3_25 = new RithmObjects.Wall(530, 340, 330, 340);
		var wall41_25 = new RithmObjects.Wall(530, 300, 530, 340);
		var wall42_25 = new RithmObjects.Wall(530, 240, 530, 280);
		var door_25 = new RithmObjects.Door(530, 280, 530, 300);

		door_25.isOpen = true;
		var walls25 = [wall1_25, wall42_25, door_25, wall41_25, wall3_25, wall2_25];

		var room25 = new RithmObjects.Room("Ch119", walls25);
		
		
		var wall1_14 = new RithmObjects.Wall(560, 10, 660, 10);
		var wall21_14 = new RithmObjects.Wall(560, 40, 560, 10);
		var door_14 = new RithmObjects.Door(560, 60, 560, 40);
		var wall22_14 = new RithmObjects.Wall(560, 100, 560, 60);
		var wall3_14 = new RithmObjects.Wall(660, 100, 560, 100);
		var wall4_14 = new RithmObjects.Wall(660, 10, 660, 100);

		door_14.isOpen = true;
		var walls_14 = [wall1_14, wall4_14, wall3_14, wall22_14, door_14, wall21_14];

		var room14 = new RithmObjects.Room("Ch120", walls_14);
		
		var wall1_15 = new RithmObjects.Wall(560, 100, 660, 100);
		var wall21_15 = new RithmObjects.Wall(560, 150, 560, 100);
		var door_15 = new RithmObjects.Door(560, 170, 560, 150);
		var wall22_15 = new RithmObjects.Wall(560, 240, 560, 170);
		var wall3_15 = new RithmObjects.Wall(660, 240, 560, 240);
		var wall4_15 = new RithmObjects.Wall(660, 100, 660, 240);

		door_15.isOpen = true;
		var walls_15 = [wall1_15, wall4_15, wall3_15, wall22_15, door_15, wall21_15];

		var room15 = new RithmObjects.Room("Ch121", walls_15);
		
		var wall1_16 = new RithmObjects.Wall(560, 240, 660, 240);
		var wall21_16 = new RithmObjects.Wall(560, 280, 560, 240);
		var door_16 = new RithmObjects.Door(560, 300, 560, 280);
		var wall22_16 = new RithmObjects.Wall(560, 370, 560, 300);
		var wall3_16 = new RithmObjects.Wall(660, 370, 560, 370);
		var wall4_16 = new RithmObjects.Wall(660, 240, 660, 370);

		door_16.isOpen = false;
		var walls_16 = [wall1_16, wall4_16, wall3_16, wall22_16, door_16, wall21_16];

		var room16 = new RithmObjects.Room("Ch122", walls_16);

		
		var wall11_3 = new RithmObjects.Wall(10, 370, 110, 370);
		var wall12_3 = new RithmObjects.Wall(130, 370, 300, 370);
		var wall21_3 = new RithmObjects.Wall(300, 370, 300, 380);
		var wall22_3 = new RithmObjects.Wall(300, 400, 300, 420);
		var wall3_3 = new RithmObjects.Wall(300, 420, 260, 420);
		var wall4_3 = new RithmObjects.Wall(260, 420, 260, 440);
		var wall5_3 = new RithmObjects.Wall(260, 440, 10, 400);
		var wall6_3 = new RithmObjects.Wall(10, 400, 10, 370);
		var door_31 = new RithmObjects.Door(110, 370, 130, 370);
		var door_32 = new RithmObjects.Door(300, 380, 300, 400);

		door_31.isOpen = false;
		door_32.isOpen = true;
		var walls3 = [wall11_3, door_31, wall12_3, wall21_3, door_32, wall22_3, wall3_3, wall4_3, wall5_3, wall6_3];

		var room3 = new RithmObjects.Room("Bl11", walls3);
		
		var wall1_31 = new RithmObjects.Wall(330, 380, 330, 370);
		var door_312 = new RithmObjects.Door(330, 400, 330, 380);
		var wall11_3 = new RithmObjects.Wall(330, 420, 330, 400);
		var wall2_3 = new RithmObjects.Wall(370, 420, 330, 420);
		var wall3_3 = new RithmObjects.Wall(370, 440, 370, 420);
		var wall4_3 = new RithmObjects.Wall(660, 400, 370, 440);
		var wall5_3 = new RithmObjects.Wall(660, 370, 660, 400);
		var wall6_3 = new RithmObjects.Wall(430, 370, 660, 370);
		var door_311 = new RithmObjects.Door(410, 370, 430, 370);
		var wall7_3 = new RithmObjects.Wall(330, 370, 410, 370);		

		door_311.isOpen = true;
		door_312.isOpen = true;
		var walls31 = [wall7_3, door_311, wall6_3, wall5_3, wall4_3, wall3_3, wall2_3, wall11_3, door_312, wall1_31];

		var room31 = new RithmObjects.Room("Bl12", walls31);

		var wall1_90 = new RithmObjects.Wall(270, 10, 360, 10);
		var wall2_90 = new RithmObjects.Wall(360, 10, 360, 100);
		var wall31_90 = new RithmObjects.Wall(360, 100, 330, 100);
		var wall32_90 = new RithmObjects.Wall(300, 100, 270, 100);
		var wall4_90 = new RithmObjects.Wall(270, 100, 270, 10);
		var door_90 = new RithmObjects.Door(330, 100, 300, 100);

		door_90.isOpen = false;
		var walls90 = [wall1_90, wall2_90, wall31_90,door_90, wall32_90, wall4_90];

		var room90 = new RithmObjects.Room("Dep11", walls90);		

		BuildingGenerator.addRoom(1, room);
		BuildingGenerator.addRoom(2, room2);
		BuildingGenerator.addRoom(3, room3);
		BuildingGenerator.addRoom(4, room31);
		//BuildingGenerator.addRoom(4, couloir);
		BuildingGenerator.addRoom(5, room10);
		BuildingGenerator.addRoom(6, room11);
		BuildingGenerator.addRoom(7, room21);
		BuildingGenerator.addRoom(8, room22);
		BuildingGenerator.addRoom(9, room23);
		BuildingGenerator.addRoom(10, room24);
		BuildingGenerator.addRoom(11, room25);
		BuildingGenerator.addRoom(12, room14);
		BuildingGenerator.addRoom(13, room15);
		BuildingGenerator.addRoom(14, room16);
		BuildingGenerator.addRoom(15, room90);
		
		//~ room.measures["3"] = 23;
		//~ room2.measures["3"] = 24;
		//~ room3.measures["3"] = 26;
		//~ room31.measures["3"] = 25;
		//~ room10.measures["3"] = 15;
		//~ room11.measures["3"] = 18;
		//~ room21.measures["3"] = 23;
		//~ room22.measures["3"] = 24;
		//~ room23.measures["3"] = 27;
		//~ room24.measures["3"] = 25;
		//~ room25.measures["3"] = 19;
		//~ room14.measures["3"] = 30;
		//~ room15.measures["3"] = 34;
		//~ room16.measures["3"] = 23;
		//~ room90.measures["3"] = 12;
		
		//~ room.measures["4"] = 23;
		//~ room2.measures["4"] = 60;
		//~ room3.measures["4"] = 70;
		//~ room31.measures["4"] = 50;
		//~ room10.measures["4"] = 55;
		//~ room11.measures["4"] = 68;
		//~ room21.measures["4"] = 45;
		//~ room22.measures["4"] = 40;
		//~ room23.measures["4"] = 27;
		//~ room24.measures["4"] = 80;
		//~ room25.measures["4"] = 85;
		//~ room14.measures["4"] = 60;
		//~ room15.measures["4"] = 50;
		//~ room16.measures["4"] = 55;
		//~ room90.measures["4"] = 56;
		
		//~ room.measures["5"] = 230;
		//~ room2.measures["5"] = 2400;
		//~ room3.measures["5"] = 260;
		//~ room31.measures["5"] = 2005;
		//~ room10.measures["5"] = 900;
		//~ room11.measures["5"] = 800;
		//~ room21.measures["5"] = 2230;
		//~ room22.measures["5"] = 1500;
		//~ room23.measures["5"] = 1000;
		//~ room24.measures["5"] = 1200;
		//~ room25.measures["5"] = 600;
		//~ room14.measures["5"] = 650;
		//~ room15.measures["5"] = 2700;
		//~ room16.measures["5"] = 800;
		//~ room90.measures["5"] = 890;
		
		//~ room.measures["7"] = 500;
		//~ room2.measures["7"] = 1000;
		//~ room3.measures["7"] = 1500;
		//~ room31.measures["7"] = 1200;
		//~ room10.measures["7"] = 300;
		//~ room11.measures["7"] = 800;
		//~ room21.measures["7"] = 600;
		//~ room22.measures["7"] = 350;
		//~ room23.measures["7"] = 980;
		//~ room24.measures["7"] = 800;
		//~ room25.measures["7"] = 1200;
		//~ room14.measures["7"] = 700;
		//~ room15.measures["7"] = 740;
		//~ room16.measures["7"] = 800;
		//~ room90.measures["7"] = 890;
		
		
		// AJOUT DE WARNINGS :
		var warning = new RithmObjects.Warning(BuildingGenerator.roomShapes[1].room, 'Danger!');
		BuildingGenerator.addWarning(1, warning);	
		var warning2 = new RithmObjects.Warning(BuildingGenerator.roomShapes[2].room, 'Patient #42 - Fatal Error!');
		BuildingGenerator.addWarning(2, warning2);	
		var warning3 = new RithmObjects.Warning(BuildingGenerator.roomShapes[3].room, 'L\'opération tourne mal !');
		BuildingGenerator.addWarning(3, warning3);	
		var warning4 = new RithmObjects.Warning(BuildingGenerator.roomShapes[3].room, 'Trop tard ...');
		BuildingGenerator.addWarning(4, warning4);
		
		// AJOUT DE PATIENTS :
		//~ var pat1 = new RithmObjects.Patient("Arnaud", true, "Cuite sévère", 1);
		//~ room.addPatient(pat1);
		//~ var pat2 = new RithmObjects.Patient("Thibaut", true, "Idem", 1);
		//~ room.addPatient(pat2);
		//~ var pat3 = new RithmObjects.Patient("Jérémy", true, "Idem", 1);
		//~ room.addPatient(pat3);
		//~ var pat4 = new RithmObjects.Patient("Daniel", true, "Idem", 1);
		//~ room.addPatient(pat4);
		//~ var pat5 = new RithmObjects.Patient("Boule", true, "Idem", 2);
		//~ room2.addPatient(pat5);
		//~ var pat6 = new RithmObjects.Patient("Bill", true, "Idem", 2);
		//~ room2.addPatient(pat6);
		//~ var pat7 = new RithmObjects.Patient("Jeanne", false, "Tronchage", 3);
		//~ room3.addPatient(pat7);
		//~ var pat8 = new RithmObjects.Patient("Jeannette", false, "Idem", 6);
		//~ room10.addPatient(pat8);
		//~ var pat9 = new RithmObjects.Patient("Arnaud", true, "Idem", 5);
		//~ room11.addPatient(pat9);
		//~ var pat10 = new RithmObjects.Patient("Arnaud", true, "Idem", 5);
		//~ room11.addPatient(pat10);
		
		
		// AJOUT DE CAPTEURS :
		//~ var sen1 = new RithmObjects.Sensor("3");
		//~ sen1.setSubject(1, true);
		//~ sen1.setMeasure({type: "3", time: new Date(), value: 30});
		//~ room.addSensor(sen1);
		//~ var sen2 = new RithmObjects.Sensor("3");
		//~ sen2.setSubject(1, true);
		//~ sen2.setMeasure({type: "3", time: new Date(), value: 10});
		//~ room.addSensor(sen2);
		var numC=0;
		$('body').html("<p></p>");
		for (var i in BuildingGenerator.roomShapes) {
			// Temp & Hum sensor :
			var s = new RithmObjects.Sensor("3");
			s.setSubject(i, true);
			s.setMeasure({type: "3", time: new Date(), value: Math.round(Math.random()*40)});
			s.setMeasure({type: "4", time: new Date(), value: Math.round(Math.random()*100)});
			BuildingGenerator.roomShapes[i].room.addSensor(s);
			
			// Hum sensor :
			s = new RithmObjects.Sensor("4");
			s.setSubject(i, true);
			s.setMeasure({type: "4", time: new Date(), value: Math.round(Math.random()*100)});
			BuildingGenerator.roomShapes[i].room.addSensor(s);
			
			// Lum sensor :
			s = new RithmObjects.Sensor("5");
			s.setSubject(i, true);
			s.setMeasure({type: "5", time: new Date(), value: Math.round(Math.random()*3000)});
			BuildingGenerator.roomShapes[i].room.addSensor(s);
			
			// CO2 sensor :
			s = new RithmObjects.Sensor("7");
			s.setSubject(i, true);
			s.setMeasure({type: "7", time: new Date(), value: Math.round(Math.random()*1700+300)});
			BuildingGenerator.roomShapes[i].room.addSensor(s);
			
			for (var j in BuildingGenerator.roomShapes[i].room.walls) {
				var wall = BuildingGenerator.roomShapes[i].room.walls[j];
				if (wall.isOpen != null) { wall.isOpen = true; }
			}
			
			$("body p").append('INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES ('+0x0070401+','+(1048599+numC)+', 1, (SELECT id FROM pld.pieces WHERE nom="'+BuildingGenerator.roomShapes[i].room.name+'"));<br\>');
			numC++;
			$("body p").append('INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES ('+0x0070801+','+(1048599+numC)+', 1, (SELECT id FROM pld.pieces WHERE nom="'+BuildingGenerator.roomShapes[i].room.name+'"));<br\>');
			numC++;
			$("body p").append('INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES ('+0x0060001+','+(1048599+numC)+', 1,(SELECT id FROM pld.pieces WHERE nom="'+BuildingGenerator.roomShapes[i].room.name+'"));<br\>');
			numC++;
			$("body p").append('INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES ('+0x0050201+','+(1048599+numC)+', 1, (SELECT id FROM pld.pieces WHERE nom="'+BuildingGenerator.roomShapes[i].room.name+'"));<br\>');
			numC++;
			$("body p").append('INSERT INTO capteurs(type, numeroCapteur, isGlobal, idSujet) VALUES ('+0x0070901+','+(1048599+numC)+', 1, (SELECT id FROM pld.pieces WHERE nom="'+BuildingGenerator.roomShapes[i].room.name+'"));<br\>');
			numC++;
		}
		
		

		// BuildingGenerator.roomLayer.setScale(window.innerWidth/850, (window.innerHeight-130)/480);
		// BuildingGenerator.pathLayer.setScale(window.innerWidth/850, (window.innerHeight-130)/480);
		BuildingGenerator.scale( window.innerWidth*0.8/670, (window.innerHeight-130)/450);
		BuildingGenerator.stage.add(BuildingGenerator.roomLayer);
		BuildingGenerator.stage.add(BuildingGenerator.pathLayer);
		BuildingGenerator.stage.add(BuildingGenerator.warningLayer);
		
		drawGradient(document.getElementById('scale'), BuildingGenerator.minArrays["3"], BuildingGenerator.maxArrays["3"], BuildingGenerator.colorArrays["3"], 8, BuildingGenerator.unitArrays["3"], '');
		
		// room.draw(ctx, "rgb(255,165,0)", "black", 2, "red", 1);
		// room2.draw(ctx, "rgb(155,165,0)", "black", 2, "red", 1);
		// room3.draw(ctx, "rgb(0,200,0)", "black", 2, "red", 1);

	}
