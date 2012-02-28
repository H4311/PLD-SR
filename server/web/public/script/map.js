// GLOBAL VARS :
var Rooms = new Array();
var Patients = new Array();
var Sensors = new Array();
var Actuators = new Array();

var rest = "http://localhost:1337";

function InitializeRooms(data) {
	var rooms = data.hits;
	for (var i = 0; i < rooms.length; i++) {
		// Load walls & create Room :
		$.ajax({
			type: 'POST',
			url: rest+'/murs',
			data: '{"id": '+rooms[i].id+'}',
			success: function(data) {
				var walls = new Array();
				for (var j = 0; j<data.hits.length; j++) {
					if (data.hits[j].isPorte) {
						walls[j] = new BuildingComponents.Door(data.hits[j].x1, data.hits[j].y1, data.hits[j].x2, data.hits[j].y2);
					}
					else {
						walls[j] = new BuildingComponents.Wall(data.hits[j].x1, data.hits[j].y1, data.hits[j].x2, data.hits[j].y2);
					}
				}
				Rooms[rooms[i].id] = new BuildingComponents.Room(rooms[i].nom, walls); 	// Create Room
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
		Patients[patients[i].id] = new BuildingComponents.Patient(patients[i].name, patients[i].isMan, patients[i].reasonHosp, patients[i].idRoom);
		Rooms[patients[i].idPiece].addPatient(Patients[patients[i].id]);
	}
}

function InitializeSensors(data) {
	var sensors = data.hits;
	var yesterday = new Date();
	yesterday.setDate(yesterday.getDate() - 1);
	for (var i = 0; i < sensors.length; i++) {
		// Creating the sensor :
		Sensors[sensors[i].id] = new BuildingComponents.Sensor(sensors[i].type);
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
		Actuators[actuators[i].id] = new BuildingComponents.Actuator(actuators[i].type);
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
			data: '{"sensors" : [ { "id" : "'+i+'", "from" : "'+ /*TODO*/ 0+'"}]}',
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
		data: '{}',
		success: InitializeRooms,
		dataType: 'json',
		async:false
	});
	// Load Patients :
	var jqXHRPatients = $.ajax({
		type: 'POST',
		url: rest+'/patients',
		data: '{}',
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
		data: '{}',
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
		data: '{}',
		success: InitializeActuators,
		dataType: 'json',
		async:true
	});
	
	// Load Bonds between actuators and subjects :
	$.ajax({
		type: 'POST',
		url: rest+'/bondsActuators',
		data: '{}',
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



// BUILDING COMPONENTS :
var BuildingComponents = {}

	// ---------------------
	// 		 SEGMENT
	// ---------------------
	BuildingComponents.Segment = function Segment(x1, y1, x2, y2) {
		this.x1 = x1;
		this.x2 = x2;
		this.y1 = y1;
		this.y2 = y2;
	};

	BuildingComponents.Segment.prototype.stroke = function SegmentStroke(ctx) {
		ctx.moveTo(this.x1,this.y1);  
		ctx.lineTo(this.x2,this.y2);  
	};

	BuildingComponents.Segment.prototype.scale = function SegmentScale(scaX, scaY) {
		this.x1 = this.x1*scaX;
		this.y1 = this.y1*scaY;
		this.x2 = this.x2*scaX;
		this.y2 = this.y2*scaY;
	};

	BuildingComponents.Segment.prototype.translate = function SegmentTranslate(x,y) {
		this.x1 += x;
		this.x2 += x;
		this.y1 += y;
		this.y2 += y;
	};
	
	BuildingComponents.Segment.prototype.copy = function SegmentCopy(seg) {
		this.x1 = seg.x1;
		this.x2 = seg.x2;
		this.y1 = seg.y1;
		this.y2 = seg.y2;
	};

	// ---------------------
	// 		   WALL
	// ---------------------

	BuildingComponents.Wall = function Wall(x1, y1, x2, y2) {
		this.segment = new BuildingComponents.Segment(x1, y1, x2, y2);
		this.segmentPlot = new BuildingComponents.Segment(x1, y1, x2, y2);
		this.scaleX = 1;
		this.scaleY = 1;
		this.origine = [0,0];
	};

	BuildingComponents.Wall.prototype.scale = function WallScale(scaX, scaY) {
		this.segmentPlot.scale(scaX/this.scaleX, scaY/this.scaleY);
		this.scaleX = scaX;
		this.scaleY = scaY;
	};

	BuildingComponents.Wall.prototype.translate = function WallTranslate(x,y) {
		this.segmentPlot.translate(x-this.origine[0], y-this.origine[1]);
		this.origine[1] = y;
		this.origine[0] = x;
	};

	BuildingComponents.Wall.prototype.stroke = function WallStroke(ctx) {
		this.segmentPlot.stroke(ctx);
	};

	BuildingComponents.Wall.prototype.fill = function WallFill(ctx) {
		ctx.lineTo(this.segmentPlot.x2, this.segmentPlot.y2);
	};

	// ---------------------
	// 		   DOOR
	// ---------------------
	
	BuildingComponents.Door = function Door(x1, y1, x2, y2) {
		this.plotClosed = new BuildingComponents.Wall(x1, y1, x2, y2);
		var d = Math.sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		var angle = Math.acos((x2-x1)/d);
		if (y2<y1) { angle = -angle; }
		
		this.plotOpen = new BuildingComponents.Wall(x1, y1, x1+d*Math.cos(0.785+angle), y1+d*Math.sin(0.785+angle));
		this.isOpen = false;
		this.roomIn = null;
		this.roomOut = null;
	};
	
	BuildingComponents.Door.prototype.scale = function DoorScale(scaX, scaY) {
		this.plotClosed.segmentPlot.scale(scaX, scaY);		
		this.plotOpen.segmentPlot.scale(scaX, scaY);
	};

	BuildingComponents.Door.prototype.stroke = function DoorStroke(ctx) {
		if (this.isOpen) {
			this.plotOpen.stroke(ctx);
			ctx.moveTo(this.plotClosed.segmentPlot.x2, this.plotClosed.segmentPlot.y2);
		}
		else {
			this.plotClosed.stroke(ctx);
		}
	};

	BuildingComponents.Door.prototype.fill = function DoorFill(ctx) {
		ctx.lineTo(this.plotClosed.segmentPlot.x2, this.plotClosed.segmentPlot.y2);
	};
	
	// ---------------------
	// 		   ROOM
	// ---------------------	

	BuildingComponents.Room = function Room(name, walls) {
		this.name = name;
		this.walls = walls;
		this.sensors = new Array();
		this.actuators = new Array();
		this.patients = new Array();
		this.measures = { "3" : 0, "4" : 0, "5" : 0, "7": 0};
		this.warning = 0;
	};
	
	BuildingComponents.Room.prototype.scale = function(scaX, scaY) {
		for (var i = 0; i < this.walls.length; i++) {
			if (this.walls[i].isOpen == null) {
				this.walls[i].scale(scaX, scaY);
			}
			else {
				this.walls[i].scale(scaX, scaY);
			}
		}
	};
	
	BuildingComponents.Room.prototype.getAverageValue = function(typeValue) {
		var avg = 0;
		var count = 0;
		for (var i = 0; i < this.sensors.length; i++) {
			if (this.sensors[i].measures[typeValue] != null) {
				avg += this.sensors[i].measures[typeValue]["value"];
				count++;
			}
		}
		if (count != 0) { return Math.round(avg/count*10)/10; }
		else { return null; }
	};
	
	BuildingComponents.Room.prototype.addSensor = function(sensor) {
		this.sensors.push(sensor);
	};

	BuildingComponents.Room.prototype.addActuator = function(actu) {
		this.actuators.push(actu);
	};

	BuildingComponents.Room.prototype.addPatient = function(pat) {
		this.patients.push(pat);
	};

	BuildingComponents.Room.prototype.fill = function(ctx, colorRoom) {
		ctx.beginPath();
		var x0, y0;
		if (this.walls[0].isOpen == null) {
			x0 = this.walls[0].segmentPlot.x1;
			y0 = this.walls[0].segmentPlot.y1;
		}
		else {
			x0 = this.walls[0].plotClosed.segmentPlot.x1;
			y0 = this.walls[0].plotClosed.segmentPlot.y1;
		}
		var previousStyle = ctx.fillStyle;
		
		// Updating the wanted value :
		this.measures[BuildingGenerator.wantedMeasure] = this.getAverageValue(BuildingGenerator.wantedMeasure);
		
		var color = ProportionalColor(this.measures[BuildingGenerator.wantedMeasure], BuildingGenerator.minArrays[BuildingGenerator.wantedMeasure], BuildingGenerator.maxArrays[BuildingGenerator.wantedMeasure], BuildingGenerator.colorArrays[BuildingGenerator.wantedMeasure]);
		
		ctx.fillStyle = 'rgb('+color.red+', '+color.green+','+color.blue+')';
		ctx.moveTo(x0, y0);
		for (var i = 0; i < this.walls.length; i++) {
			if (this.walls[i].isOpen == null) { // Wall
				this.walls[i].fill(ctx);
			}
			else { // Door
				this.walls[i].fill(ctx);
			}
		}
		ctx.closePath();
		ctx.fill();
		ctx.fillStyle = previousStyle;
	};
	
	BuildingComponents.Room.prototype.stroke = function(ctx) {
		var colorWall = (this.warning > 0)? BuildingGenerator.colorWallWarning : BuildingGenerator.colorWall;
		var lineWidthWall = (this.warning > 0)? BuildingGenerator.lineWidthWallWarning : BuildingGenerator.lineWidthWall;
		var previousWidth = ctx.lineWidth;
		var previousStyle = ctx.strokeStyle;
		ctx.lineWidth = lineWidthWall;
		ctx.strokeStyle = colorWall;  
		ctx.lineJoin = 'round';
		ctx.beginPath();
		for (var i = 0; i < this.walls.length; i++) {
			if (this.walls[i].isOpen == null) { // Wall
				this.walls[i].stroke(ctx);
			}
			else { // Door
				ctx.stroke();
				ctx.beginPath();
				ctx.lineWidth = BuildingGenerator.lineWidthDoor;
				ctx.strokeStyle = BuildingGenerator.colorDoor;  
				this.walls[i].stroke(ctx);
				ctx.stroke();
				ctx.beginPath();
				ctx.lineWidth = lineWidthWall;
				ctx.strokeStyle = colorWall;  
			}
		}
		ctx.closePath();
		ctx.stroke();
		ctx.lineWidth = previousWidth;
		ctx.strokeStyle = previousStyle;	
	};
	
	BuildingComponents.Room.prototype.printName = function(ctx, color, size) {
		previousFont = ctx.font;
		previousColor = ctx.fillStyle;
		ctx.font = size+"pt Calibri";
		ctx.fillStyle = color;
		ctx.fillText(this.name, this.walls[0].segmentPlot.x1+10, this.walls[0].segmentPlot.y1+12);
		ctx.font = previousFont;
		ctx.fillStyle = previousColor;
	};
	
	// ---------------------
	//		 SENSOR
	// ---------------------
	BuildingComponents.Sensor = function Sensor(type) {
		this.type = type;
		this.measures = new Array();
		this.subject = {
			id : 0,
			isGlobal : false
		};
	};
		
	BuildingComponents.Sensor.prototype.setSubject = function(s, glo) {
		this.subject.id = s;
		this.subject.isGlobal = glo;
	};
	
	BuildingComponents.Sensor.prototype.setMeasure = function(measure) {
		if ((this.measures[measure.type] == null) || (this.measures[measure.type]["time"] < measure.time)) {
			// Updating if it's a new value :
			this.measures[measure.type] = {"time" : measure.time, "value" : measure.value};
			// Updating the canvas :
			if (!this.subject.isGlobal) {
				BuildingGenerator.roomShapes[this.subject.id].draw();
			}
		}
	};
	
	// ---------------------
	// 		 ACTUATOR
	// ---------------------
	BuildingComponents.Actuator = function Actuator (type) {
		this.type = type;
		this.subjectID = new Array();
	};
		
	BuildingComponents.Actuator.prototype.addSubject = function(s, glo) {
		this.subjectID.push({ id : 0, isGlobal : false});
	};
	
	
	// ---------------------
	// 		 PATIENT
	// ---------------------	
	
	BuildingComponents.Patient = function Patient(name, isMan, reasonHosp, roomID) {
		this.name = name;
		this.isMan = isMan;
		this.reasonHosp = reasonHosp;
		this.idRoom = roomID;
		this.sensors = new Array();
		this.actuators = new Array();
	};
	
	BuildingComponents.Patient.prototype.addSensor = function(sensor) {
		this.sensors.push(sensor);
	};

	BuildingComponents.Patient.prototype.addActuator = function(actu) {
		this.actuators.push(actu);
	};
	

	// ---------------------
	// 		 ROOMSHAPE
	// ---------------------	
	BuildingComponents.RoomShape = function RoomShape (id, room) {
		var shape = new Kinetic.Shape(function() {
			var context = this.getContext();
			this.room.fill(context, this.color);
		});
		shape.on("mousemove", function Click(){
			$('#warningDesc').css('display', 'none');
            var s = BuildingGenerator.roomShapes[this.idRoom];
			$('#roomDesc p').text(s.room.name);
			$('#roomDesc table tr:nth-child(1) td:nth-child(2)').text(s.room.patients.length);
			$('#roomDesc table tr:nth-child(2) td:nth-child(2)').text(s.room.warning);
			$('#roomDesc table tr:nth-child(3) td:nth-child(1)').text(s.room.measures[BuildingGenerator.wantedMeasure]+BuildingGenerator.unitArrays[BuildingGenerator.wantedMeasure]);
			var mousePos = BuildingGenerator.stage.getMousePosition();
			$('#buildingContainer').css('cursor', 'pointer');
			$('#roomDesc').css('left', (mousePos.x+BuildingGenerator.leftOffset)+'px');
			$('#roomDesc').css('top', (mousePos.y+BuildingGenerator.topOffset)+'px');
			$('#roomDesc').css('display', 'block');
		});
		
		shape.on("click", function Click(){
			if($('#roomDesc').css('display') == 'none') {
				$('#warningDesc').css('display', 'none');
				var s = BuildingGenerator.roomShapes[this.idRoom];
				$('#roomDesc p').text(s.room.name);
				$('#roomDesc table tr:nth-child(1) td:nth-child(2)').text(s.room.patients.length);
				$('#roomDesc table tr:nth-child(2) td:nth-child(2)').text(s.room.warning);
				$('#roomDesc table tr:nth-child(3) td:nth-child(1)').text(s.room.measures[BuildingGenerator.wantedMeasure]+BuildingGenerator.unitArrays[BuildingGenerator.wantedMeasure]);
				var mousePos = BuildingGenerator.stage.getMousePosition();
				$('#buildingContainer').css('cursor', 'pointer');
				$('#roomDesc').css('left', (mousePos.x+BuildingGenerator.leftOffset)+'px');
				$('#roomDesc').css('top', (mousePos.y+BuildingGenerator.topOffset)+'px');
				$('#roomDesc').css('display', 'block');
			}
			else {
				$('#roomDesc').css('display', 'none');
			}
		});
			
		shape.on("mouseout", function Click(){
			$('#buildingContainer').css('cursor', 'auto');
			$('#roomDesc').css('display', 'none');
		});
		shape.on("dblclick", function Click(){
			location.href = 'room.html?id='+ this.idRoom;
		});
		shape.room = room;
		shape.idRoom = id;
		shape.color = "grey";
		return shape;
	};
	BuildingComponents.RoomShape.prototype = new Kinetic.Shape;
	BuildingComponents.RoomShape.prototype.constructor = this.RoomShape;
	BuildingComponents.RoomShape.prototype.parent = Kinetic.Shape.prototype;
	
	// ---------------------
	// 		 ROOMPATH
	// ---------------------	
	BuildingComponents.RoomPath = function RoomPath (room) {
		var shape = new Kinetic.Shape(function() {
			var context = this.getContext();
			this.room.stroke(context);
			this.room.printName(context, "black", 8);
		});
		shape.room = room;
		shape.color = "grey";
		return shape;
	};
	BuildingComponents.RoomPath.prototype = new Kinetic.Shape;
	BuildingComponents.RoomPath.prototype.constructor = this.RoomPath;
	BuildingComponents.RoomPath.prototype.parent = Kinetic.Shape.prototype;

	
	// ---------------------
	// 		 WARNING
	// ---------------------	
	BuildingComponents.Warning = function Warning (room, content) {
		this.room = room;
		room.warning++;
		this.content = content;
	};
	
	// ---------------------
	// 		 WARNINGCIRCLE
	// ---------------------	
	BuildingComponents.WarningCircle = function WarningCircle (id, warning) {
		var shapeW = new Kinetic.Shape(function() {
			var context = this.getContext();
			drawCircle(context, this.warning.room.walls[0].segmentPlot.x1+25, this.warning.room.walls[0].segmentPlot.y1+24, 10, 'rgb(200,50,50)');
		});
		
		shapeW.warning = warning;
		shapeW.idWarning = id;
		
		shapeW.on("mousemove", function(){
			$('#roomDesc').css('display', 'none');
			$('#buildingContainer').css('cursor', 'pointer');
			$('#warningDesc').text(this.warning.content);
			var mousePos = BuildingGenerator.stage.getMousePosition();
			$('#warningDesc').css('left', (mousePos.x+BuildingGenerator.leftOffset)+'px');
			$('#warningDesc').css('top', (mousePos.y+BuildingGenerator.topOffset-15)+'px');
			$('#warningDesc').css('display', 'block');
		});
		
		shapeW.on("click", function(){
			if ($('#warningDesc').css('display') == 'block') {
				$('#warningDesc').css('display', 'none');
			}
			else {
				$('#roomDesc').css('display', 'none');
				$('#buildingContainer').css('cursor', 'pointer');
				$('#warningDesc').text(this.warning.content);
				var mousePos = BuildingGenerator.stage.getMousePosition();
				$('#warningDesc').css('left', (mousePos.x+BuildingGenerator.leftOffset)+'px');
				$('#warningDesc').css('top', (mousePos.y+BuildingGenerator.topOffset-15)+'px');
				$('#warningDesc').css('display', 'block');			
			}
		});
		
		shapeW.on("mouseout ", function(){
			$('#buildingContainer').css('cursor', 'auto');
			$('#warningDesc').css('display', 'none');
		});

		shapeW.on("dblclick", function(){
			$('#buildingContainer').css('cursor', 'auto');
			$('#warningDesc').css('display', 'none');
			BuildingGenerator.removeWarning(this.idWarning);	
		});
		
		return shapeW;
	};
	BuildingComponents.WarningCircle.prototype = new Kinetic.Shape;
	BuildingComponents.WarningCircle.prototype.constructor = this.WarningCircle;
	BuildingComponents.WarningCircle.prototype.parent = Kinetic.Shape.prototype;
	
	// ---------------------
	// 		 WARNINGMARK
	// ---------------------	
	BuildingComponents.WarningMark = function WarningMark (id, warning) {
		var shapeW = new Kinetic.Shape(function() {
			var context = this.getContext();
			drawExclame(context, this.warning.room.walls[0].segmentPlot.x1+25, this.warning.room.walls[0].segmentPlot.y1+24, 10, 'rgb(255,255,255)');
		});
		
		shapeW.idWarning = id;
		shapeW.warning = warning;

		shapeW.on("mousemove", function(){
			$('#buildingContainer').css('cursor', 'pointer');
			$('#warningDesc').text(this.warning.content);
			var mousePos = BuildingGenerator.stage.getMousePosition();
			$('#warningDesc').css('left', (mousePos.x+BuildingGenerator.leftOffset)+'px');
			$('#warningDesc').css('top', (mousePos.y+BuildingGenerator.topOffset-15)+'px');
			$('#warningDesc').css('display', 'block');
		});
		
		shapeW.on("click", function(){
			if ($('#warningDesc').css('display') == 'block') {
				$('#warningDesc').css('display', 'none');
			}
			else {
				$('#warningDesc').text(this.warning.content);
				var mousePos = BuildingGenerator.stage.getMousePosition();
				$('#warningDesc').css('left', (mousePos.x+BuildingGenerator.leftOffset)+'px');
				$('#warningDesc').css('top', (mousePos.y+BuildingGenerator.topOffset-15)+'px');
				$('#warningDesc').css('display', 'block');		
			}
		});
		
		shapeW.on("mouseout ", function(){
			$('#buildingContainer').css('cursor', 'auto');
			$('#warningDesc').css('display', 'none');
		});

		shapeW.on("dblclick ", function(){
			$('#buildingContainer').css('cursor', 'auto');
			$('#warningDesc').css('display', 'none');
			BuildingGenerator.removeWarning(this.idWarning);
		});

		return shapeW;
	};
	BuildingComponents.WarningMark.prototype = new Kinetic.Shape;
	BuildingComponents.WarningMark.prototype.constructor = this.WarningMark;
	BuildingComponents.WarningMark.prototype.parent = Kinetic.Shape.prototype;
	
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
		this.roomShapes[id] = new BuildingComponents.RoomShape(id, room);
		var p = new BuildingComponents.RoomPath(room);
		this.roomLayer.add(this.roomShapes[id]);
		this.pathLayer.add(p);
	},
	
	addWarning : function AddWarning(id, warning) {
		this.warningShapes[id] = [new BuildingComponents.WarningCircle(id, warning), new BuildingComponents.WarningMark(id, warning)];
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
	
	function draw() {
		// canvas = document.getElementById('buildingContainer');
		// canvas.width = window.innerWidth-120;
		// canvas.height = window.innerHeight-84;
		// var ctx = canvas.getContext('2d'); 
		
		
		
		//~ var wall1 = {type:0, wall:new BuildingComponents.Wall(10, 10, 100, 10)};
		//~ var wall21 = {type:0, wall:new BuildingComponents.Wall(100, 10, 100, 40)};
		//~ var door = {type:1, door:new BuildingComponents.Door(100, 40, 100, 60)};
		//~ var wall22 = {type:0, wall:new BuildingComponents.Wall(100, 60, 100, 100)};
		//~ var wall3 = {type:0, wall:new BuildingComponents.Wall(100, 100, 10, 100)};
		//~ var wall4 = {type:0, wall:new BuildingComponents.Wall(10, 100, 10, 10)};

		//~ door.door.isOpen = true;
		//~ var walls = [wall1, wall21, door, wall22, wall3, wall4];

		//~ var room = new BuildingComponents.Room("Ch111", walls);
		
		//~ var wall1_10 = {type:0, wall:new BuildingComponents.Wall(10, 100, 100, 100)};
		//~ var wall21_10 = {type:0, wall:new BuildingComponents.Wall(100, 100, 100, 150)};
		//~ var door_10 = {type:1, door:new BuildingComponents.Door(100, 150, 100, 170)};
		//~ var wall22_10 = {type:0, wall:new BuildingComponents.Wall(100, 170, 100, 240)};
		//~ var wall3_10 = {type:0, wall:new BuildingComponents.Wall(100, 240, 10, 240)};
		//~ var wall4_10 = {type:0, wall:new BuildingComponents.Wall(10, 240, 10, 100)};

		//~ door_10.door.isOpen = false;
		//~ var walls_10 = [wall1_10, wall21_10, door_10, wall22_10, wall3_10, wall4_10];

		//~ var room10 = new BuildingComponents.Room("Ch112", walls_10);
		
		//~ var wall1_11 = {type:0, wall:new BuildingComponents.Wall(10, 240, 100, 240)};
		//~ var wall21_11 = {type:0, wall:new BuildingComponents.Wall(100, 240, 100, 270)};
		//~ var door_11 = {type:1, door:new BuildingComponents.Door(100, 270, 100, 290)};
		//~ var wall22_11 = {type:0, wall:new BuildingComponents.Wall(100, 290, 100, 370)};
		//~ var wall3_11 = {type:0, wall:new BuildingComponents.Wall(100, 370, 10, 370)};
		//~ var wall4_11 = {type:0, wall:new BuildingComponents.Wall(10, 370, 10, 240)};

		//~ door_11.door.isOpen = true;
		//~ var walls_11 = [wall1_11, wall21_11, door_11, wall22_11, wall3_11, wall4_11];

		//~ var room11 = new BuildingComponents.Room("Ch113", walls_11);
		
		//~ var wall1_2 = {type:0, wall:new BuildingComponents.Wall(130, 10, 270, 10)};
		//~ var wall2_2 = {type:0, wall:new BuildingComponents.Wall(270, 10, 270, 100)};
		//~ var wall3_2 = {type:0, wall:new BuildingComponents.Wall(270, 100, 130, 100)};
		//~ var wall41_2 = {type:0, wall:new BuildingComponents.Wall(130, 100, 130, 60)};
		//~ var wall42_2 = {type:0, wall:new BuildingComponents.Wall(130, 40, 130, 10)};
		//~ var door_2 = {type:1, door:new BuildingComponents.Door(130, 60, 130, 40)};

		//~ door_2.door.isOpen = true;
		//~ var walls2 = [wall1_2, wall2_2, wall3_2, wall41_2, door_2, wall42_2];

		//~ var room2 = new BuildingComponents.Room("Ch114", walls2);
		
		//~ var wall1_21 = {type:0, wall:new BuildingComponents.Wall(130, 130, 300, 130)};
		//~ var wall2_21 = {type:0, wall:new BuildingComponents.Wall(300, 130, 300, 240)};
		//~ var wall3_21 = {type:0, wall:new BuildingComponents.Wall(300, 240, 130, 240)};
		//~ var wall41_21 = {type:0, wall:new BuildingComponents.Wall(130, 240, 130, 180)};
		//~ var wall42_21 = {type:0, wall:new BuildingComponents.Wall(130, 160, 130, 130)};
		//~ var door_21 = {type:1, door:new BuildingComponents.Door(130, 180, 130, 160)};

		//~ door_21.door.isOpen = true;
		//~ var walls21 = [wall1_21, wall2_21, wall3_21, wall41_21, door_21, wall42_21];

		//~ var room21 = new BuildingComponents.Room("Ch115", walls21);
		
		//~ var wall1_22 = {type:0, wall:new BuildingComponents.Wall(130, 240, 300, 240)};
		//~ var wall2_22 = {type:0, wall:new BuildingComponents.Wall(300, 240, 300, 340)};
		//~ var wall3_22 = {type:0, wall:new BuildingComponents.Wall(300, 340, 130, 340)};
		//~ var wall41_22 = {type:0, wall:new BuildingComponents.Wall(130, 340, 130, 300)};
		//~ var wall42_22 = {type:0, wall:new BuildingComponents.Wall(130, 280, 130, 240)};
		//~ var door_22 = {type:1, door:new BuildingComponents.Door(130, 300, 130, 280)};

		//~ door_22.door.isOpen = true;
		//~ var walls22 = [wall1_22, wall2_22, wall3_22, wall41_22, door_22, wall42_22];
		//~ var room22 = new BuildingComponents.Room("Ch116", walls22);
		
		//~ var wall1_23 = {type:0, wall:new BuildingComponents.Wall(360, 10, 530, 10)};
		//~ var wall2_23 = {type:0, wall:new BuildingComponents.Wall(360, 100, 360, 10)};
		//~ var wall3_23 = {type:0, wall:new BuildingComponents.Wall(530, 100, 360, 100)};
		//~ var wall41_23 = {type:0, wall:new BuildingComponents.Wall(530, 60, 530, 100)};
		//~ var wall42_23 = {type:0, wall:new BuildingComponents.Wall(530, 10, 530, 40)};
		//~ var door_23 = {type:1, door:new BuildingComponents.Door(530, 40, 530, 60)};

		//~ door_23.door.isOpen = true;
		//~ var walls23 = [wall1_23, wall42_23, door_23, wall41_23, wall3_23, wall2_23];

		//~ var room23 = new BuildingComponents.Room("Ch117", walls23);
		
		//~ var wall1_24 = {type:0, wall:new BuildingComponents.Wall(330, 130, 530, 130)};
		//~ var wall2_24 = {type:0, wall:new BuildingComponents.Wall(330, 240, 330, 130)};
		//~ var wall3_24 = {type:0, wall:new BuildingComponents.Wall(530, 240, 330, 240)};
		//~ var wall41_24 = {type:0, wall:new BuildingComponents.Wall(530, 180, 530, 240)};
		//~ var wall42_24 = {type:0, wall:new BuildingComponents.Wall(530, 130, 530, 160)};
		//~ var door_24 = {type:1, door:new BuildingComponents.Door(530, 160, 530, 180)};

		//~ door_24.door.isOpen = true;
		//~ var walls24 = [wall1_24, wall42_24, door_24, wall41_24, wall3_24, wall2_24];

		//~ var room24 = new BuildingComponents.Room("Ch118", walls24);
		
		//~ var wall1_25 = {type:0, wall:new BuildingComponents.Wall(330, 240, 530, 240)};
		//~ var wall2_25 = {type:0, wall:new BuildingComponents.Wall(330, 340, 330, 240)};
		//~ var wall3_25 = {type:0, wall:new BuildingComponents.Wall(530, 340, 330, 340)};
		//~ var wall41_25 = {type:0, wall:new BuildingComponents.Wall(530, 300, 530, 340)};
		//~ var wall42_25 = {type:0, wall:new BuildingComponents.Wall(530, 240, 530, 280)};
		//~ var door_25 = {type:1, door:new BuildingComponents.Door(530, 280, 530, 300)};

		//~ door_25.door.isOpen = true;
		//~ var walls25 = [wall1_25, wall42_25, door_25, wall41_25, wall3_25, wall2_25];

		//~ var room25 = new BuildingComponents.Room("Ch119", walls25);
		
		
		//~ var wall1_14 = {type:0, wall:new BuildingComponents.Wall(560, 10, 660, 10)};
		//~ var wall21_14 = {type:0, wall:new BuildingComponents.Wall(560, 40, 560, 10)};
		//~ var door_14 = {type:1, door:new BuildingComponents.Door(560, 60, 560, 40)};
		//~ var wall22_14 = {type:0, wall:new BuildingComponents.Wall(560, 100, 560, 60)};
		//~ var wall3_14 = {type:0, wall:new BuildingComponents.Wall(660, 100, 560, 100)};
		//~ var wall4_14 = {type:0, wall:new BuildingComponents.Wall(660, 10, 660, 100)};

		//~ door_14.door.isOpen = true;
		//~ var walls_14 = [wall1_14, wall4_14, wall3_14, wall22_14, door_14, wall21_14];

		//~ var room14 = new BuildingComponents.Room("Ch120", walls_14);
		
		//~ var wall1_15 = {type:0, wall:new BuildingComponents.Wall(560, 100, 660, 100)};
		//~ var wall21_15 = {type:0, wall:new BuildingComponents.Wall(560, 150, 560, 100)};
		//~ var door_15 = {type:1, door:new BuildingComponents.Door(560, 170, 560, 150)};
		//~ var wall22_15 = {type:0, wall:new BuildingComponents.Wall(560, 240, 560, 170)};
		//~ var wall3_15 = {type:0, wall:new BuildingComponents.Wall(660, 240, 560, 240)};
		//~ var wall4_15 = {type:0, wall:new BuildingComponents.Wall(660, 100, 660, 240)};

		//~ door_15.door.isOpen = true;
		//~ var walls_15 = [wall1_15, wall4_15, wall3_15, wall22_15, door_15, wall21_15];

		//~ var room15 = new BuildingComponents.Room("Ch121", walls_15);
		
		//~ var wall1_16 = {type:0, wall:new BuildingComponents.Wall(560, 240, 660, 240)};
		//~ var wall21_16 = {type:0, wall:new BuildingComponents.Wall(560, 280, 560, 240)};
		//~ var door_16 = {type:1, door:new BuildingComponents.Door(560, 300, 560, 280)};
		//~ var wall22_16 = {type:0, wall:new BuildingComponents.Wall(560, 370, 560, 300)};
		//~ var wall3_16 = {type:0, wall:new BuildingComponents.Wall(660, 370, 560, 370)};
		//~ var wall4_16 = {type:0, wall:new BuildingComponents.Wall(660, 240, 660, 370)};

		//~ door_16.door.isOpen = false;
		//~ var walls_16 = [wall1_16, wall4_16, wall3_16, wall22_16, door_16, wall21_16];

		//~ var room16 = new BuildingComponents.Room("Ch122", walls_16);

		
		//~ var wall11_3 = {type:0, wall:new BuildingComponents.Wall(10, 370, 110, 370)};
		//~ var wall12_3 = {type:0, wall:new BuildingComponents.Wall(130, 370, 300, 370)};
		//~ var wall21_3 = {type:0, wall:new BuildingComponents.Wall(300, 370, 300, 380)};
		//~ var wall22_3 = {type:0, wall:new BuildingComponents.Wall(300, 400, 300, 420)};
		//~ var wall3_3 = {type:0, wall:new BuildingComponents.Wall(300, 420, 260, 420)};
		//~ var wall4_3 = {type:0, wall:new BuildingComponents.Wall(260, 420, 260, 440)};
		//~ var wall5_3 = {type:0, wall:new BuildingComponents.Wall(260, 440, 10, 400)};
		//~ var wall6_3 = {type:0, wall:new BuildingComponents.Wall(10, 400, 10, 370)};
		//~ var door_31 = {type:1, door:new BuildingComponents.Door(110, 370, 130, 370)};
		//~ var door_32 = {type:1, door:new BuildingComponents.Door(300, 380, 300, 400)};

		//~ door_31.door.isOpen = false;
		//~ door_32.door.isOpen = true;
		//~ var walls3 = [wall11_3, door_31, wall12_3, wall21_3, door_32, wall22_3, wall3_3, wall4_3, wall5_3, wall6_3];

		//~ var room3 = new BuildingComponents.Room("Bl11", walls3);
		
		//~ var wall1_31 = {type:0, wall:new BuildingComponents.Wall(330, 380, 330, 370)};
		//~ var door_312 = {type:1, door:new BuildingComponents.Door(330, 400, 330, 380)};
		//~ var wall11_3 = {type:0, wall:new BuildingComponents.Wall(330, 420, 330, 400)};
		//~ var wall2_3 = {type:0, wall:new BuildingComponents.Wall(370, 420, 330, 420)};
		//~ var wall3_3 = {type:0, wall:new BuildingComponents.Wall(370, 440, 370, 420)};
		//~ var wall4_3 = {type:0, wall:new BuildingComponents.Wall(660, 400, 370, 440)};
		//~ var wall5_3 = {type:0, wall:new BuildingComponents.Wall(660, 370, 660, 400)};
		//~ var wall6_3 = {type:0, wall:new BuildingComponents.Wall(430, 370, 660, 370)};
		//~ var door_311 = {type:1, door:new BuildingComponents.Door(410, 370, 430, 370)};
		//~ var wall7_3 = {type:0, wall:new BuildingComponents.Wall(330, 370, 410, 370)};		

		//~ door_311.door.isOpen = true;
		//~ door_312.door.isOpen = true;
		//~ var walls31 = [wall7_3, door_311, wall6_3, wall5_3, wall4_3, wall3_3, wall2_3, wall11_3, door_312, wall1_31];

		//~ var room31 = new BuildingComponents.Room("Bl12", walls31);

		//~ var wall1_90 = {type:0, wall:new BuildingComponents.Wall(270, 10, 360, 10)};
		//~ var wall2_90 = {type:0, wall:new BuildingComponents.Wall(360, 10, 360, 100)};
		//~ var wall31_90 = {type:0, wall:new BuildingComponents.Wall(360, 100, 330, 100)};
		//~ var wall32_90 = {type:0, wall:new BuildingComponents.Wall(300, 100, 270, 100)};
		//~ var wall4_90 = {type:0, wall:new BuildingComponents.Wall(270, 100, 270, 10)};
		//~ var door_90 = {type:1, door:new BuildingComponents.Door(330, 100, 300, 100)};

		//~ door_90.door.isOpen = false;
		//~ var walls90 = [wall1_90, wall2_90, wall31_90,door_90, wall32_90, wall4_90];

		//~ var room90 = new BuildingComponents.Room("Dep11", walls90);		

		//~ BuildingGenerator.addRoom(1, room);
		//~ BuildingGenerator.addRoom(2, room2);
		//~ BuildingGenerator.addRoom(3, room3);
		//~ BuildingGenerator.addRoom(15, room31);
		//~ //BuildingGenerator.addRoom(4, couloir);
		//~ BuildingGenerator.addRoom(5, room10);
		//~ BuildingGenerator.addRoom(6, room11);
		//~ BuildingGenerator.addRoom(7, room21);
		//~ BuildingGenerator.addRoom(8, room22);
		//~ BuildingGenerator.addRoom(9, room23);
		//~ BuildingGenerator.addRoom(10, room24);
		//~ BuildingGenerator.addRoom(11, room25);
		//~ BuildingGenerator.addRoom(12, room14);
		//~ BuildingGenerator.addRoom(13, room15);
		//~ BuildingGenerator.addRoom(14, room16);
		//~ BuildingGenerator.addRoom(16, room90);
		
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
		var warning = new BuildingComponents.Warning(BuildingGenerator.roomShapes[1].room, 'Danger!');
		BuildingGenerator.addWarning(1, warning);	
		var warning2 = new BuildingComponents.Warning(BuildingGenerator.roomShapes[2].room, 'Patient #42 - Fatal Error!');
		BuildingGenerator.addWarning(2, warning2);	
		var warning3 = new BuildingComponents.Warning(BuildingGenerator.roomShapes[3].room, 'L\'opération tourne mal !');
		BuildingGenerator.addWarning(3, warning3);	
		var warning4 = new BuildingComponents.Warning(BuildingGenerator.roomShapes[3].room, 'Trop tard ...');
		BuildingGenerator.addWarning(4, warning4);
		
		// AJOUT DE PATIENTS :
		//~ var pat1 = new BuildingComponents.Patient("Arnaud", true, "Cuite sévère", 1);
		//~ room.addPatient(pat1);
		//~ var pat2 = new BuildingComponents.Patient("Thibaut", true, "Idem", 1);
		//~ room.addPatient(pat2);
		//~ var pat3 = new BuildingComponents.Patient("Jérémy", true, "Idem", 1);
		//~ room.addPatient(pat3);
		//~ var pat4 = new BuildingComponents.Patient("Daniel", true, "Idem", 1);
		//~ room.addPatient(pat4);
		//~ var pat5 = new BuildingComponents.Patient("Boule", true, "Idem", 2);
		//~ room2.addPatient(pat5);
		//~ var pat6 = new BuildingComponents.Patient("Bill", true, "Idem", 2);
		//~ room2.addPatient(pat6);
		//~ var pat7 = new BuildingComponents.Patient("Jeanne", false, "Tronchage", 3);
		//~ room3.addPatient(pat7);
		//~ var pat8 = new BuildingComponents.Patient("Jeannette", false, "Idem", 6);
		//~ room10.addPatient(pat8);
		//~ var pat9 = new BuildingComponents.Patient("Arnaud", true, "Idem", 5);
		//~ room11.addPatient(pat9);
		//~ var pat10 = new BuildingComponents.Patient("Arnaud", true, "Idem", 5);
		//~ room11.addPatient(pat10);
		
		
		// AJOUT DE CAPTEURS :
		//~ var sen1 = new BuildingComponents.Sensor("3");
		//~ sen1.setSubject(1, true);
		//~ sen1.setMeasure({type: "3", time: new Date(), value: 30});
		//~ room.addSensor(sen1);
		//~ var sen2 = new BuildingComponents.Sensor("3");
		//~ sen2.setSubject(1, true);
		//~ sen2.setMeasure({type: "3", time: new Date(), value: 10});
		//~ room.addSensor(sen2);
		for (var i in BuildingGenerator.roomShapes) {
			// Temp & Hum sensor :
			var s = new BuildingComponents.Sensor("3");
			s.setSubject(i, true);
			s.setMeasure({type: "3", time: new Date(), value: Math.round(Math.random()*40)});
			s.setMeasure({type: "4", time: new Date(), value: Math.round(Math.random()*100)});
			BuildingGenerator.roomShapes[i].room.addSensor(s);
			
			// Hum sensor :
			s = new BuildingComponents.Sensor("4");
			s.setSubject(i, true);
			s.setMeasure({type: "4", time: new Date(), value: Math.round(Math.random()*100)});
			BuildingGenerator.roomShapes[i].room.addSensor(s);
			
			// Lum sensor :
			s = new BuildingComponents.Sensor("5");
			s.setSubject(i, true);
			s.setMeasure({type: "5", time: new Date(), value: Math.round(Math.random()*3000)});
			BuildingGenerator.roomShapes[i].room.addSensor(s);
			
			// CO2 sensor :
			s = new BuildingComponents.Sensor("7");
			s.setSubject(i, true);
			s.setMeasure({type: "7", time: new Date(), value: Math.round(Math.random()*1700+300)});
			BuildingGenerator.roomShapes[i].room.addSensor(s);
			
			for (var j in BuildingGenerator.roomShapes[i].room.walls) {
				var wall = BuildingGenerator.roomShapes[i].room.walls[j];
				if (wall.isOpen != null) { wall.isOpen = true; }
			}
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
