
// ------------------------------------------------------------------------------------
// 		 			OBJECTS
// ------------------------------------------------------------------------------------	

var RithmObjects = {}

	// ---------------------
	// 		 SEGMENT
	// ---------------------
	RithmObjects.Segment = function Segment(x1, y1, x2, y2) {
		this.x1 = x1;
		this.x2 = x2;
		this.y1 = y1;
		this.y2 = y2;
	};

	RithmObjects.Segment.prototype.stroke = function SegmentStroke(ctx) {
		ctx.moveTo(this.x1,this.y1);  
		ctx.lineTo(this.x2,this.y2);  
	};

	RithmObjects.Segment.prototype.scale = function SegmentScale(scaX, scaY) {
		this.x1 = this.x1*scaX;
		this.y1 = this.y1*scaY;
		this.x2 = this.x2*scaX;
		this.y2 = this.y2*scaY;
	};

	RithmObjects.Segment.prototype.translate = function SegmentTranslate(x,y) {
		this.x1 += x;
		this.x2 += x;
		this.y1 += y;
		this.y2 += y;
	};
	
	RithmObjects.Segment.prototype.copy = function SegmentCopy(seg) {
		this.x1 = seg.x1;
		this.x2 = seg.x2;
		this.y1 = seg.y1;
		this.y2 = seg.y2;
	};

	// ---------------------
	// 		   WALL
	// ---------------------

	RithmObjects.Wall = function Wall(x1, y1, x2, y2) {
		this.segment = new RithmObjects.Segment(x1, y1, x2, y2);
		this.segmentPlot = new RithmObjects.Segment(x1, y1, x2, y2);
		this.scaleX = 1;
		this.scaleY = 1;
		this.origine = [0,0];
	};

	RithmObjects.Wall.prototype.scale = function WallScale(scaX, scaY) {
		this.segmentPlot.scale(scaX/this.scaleX, scaY/this.scaleY);
		this.scaleX = scaX;
		this.scaleY = scaY;
	};

	RithmObjects.Wall.prototype.translate = function WallTranslate(x,y) {
		this.segmentPlot.translate(x-this.origine[0], y-this.origine[1]);
		this.origine[1] = y;
		this.origine[0] = x;
	};

	// ---------------------
	// 		   DOOR
	// ---------------------
	
	RithmObjects.Door = function Door(x1, y1, x2, y2) {
		this.plotClosed = new RithmObjects.Wall(x1, y1, x2, y2);
		var d = Math.sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
		var angle = Math.acos((x2-x1)/d);
		if (y2<y1) { angle = -angle; }
		
		this.plotOpen = new RithmObjects.Wall(x1, y1, x1+d*Math.cos(0.785+angle), y1+d*Math.sin(0.785+angle));
		this.isOpen = false;
		this.roomIn = null;
		this.roomOut = null;
	};
	
	RithmObjects.Door.prototype.scale = function DoorScale(scaX, scaY) {
		this.plotClosed.segmentPlot.scale(scaX, scaY);		
		this.plotOpen.segmentPlot.scale(scaX, scaY);
	};


	// ---------------------
	// 		   ROOM
	// ---------------------	

	RithmObjects.Room = function Room(name, walls) {
		this.name = name;
		this.walls = walls;
		this.sensors = new Array();
		this.actuators = new Array();
		this.patients = new Array();
		this.measures = { "3" : 0, "4" : 0, "5" : 0, "7": 0};
		this.warning = 0;
	};
	
	RithmObjects.Room.prototype.scale = function(scaX, scaY) {
		for (var i = 0; i < this.walls.length; i++) {
			if (this.walls[i].isOpen == null) {
				this.walls[i].scale(scaX, scaY);
			}
			else {
				this.walls[i].scale(scaX, scaY);
			}
		}
	};
	
	RithmObjects.Room.prototype.getAverageValue = function(typeValue) {
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
	
	RithmObjects.Room.prototype.addSensor = function(sensor) {
		this.sensors.push(sensor);
	};

	RithmObjects.Room.prototype.addActuator = function(actu) {
		this.actuators.push(actu);
	};

	RithmObjects.Room.prototype.addPatient = function(pat) {
		this.patients.push(pat);
	};
	
	// ---------------------
	//		 SENSOR WITH LOG
	// ---------------------
	RithmObjects.SensorLog = function SensorLog(type) {
		this.type = type;
		this.measures = new Array();
		this.subject = {
			id : 0,
			isGlobal : false
		};
	};
		
	RithmObjects.SensorLog.prototype.setSubject = function(s, glo) {
		this.subject.id = s;
		this.subject.isGlobal = glo;
	};
	
	RithmObjects.SensorLog.prototype.addMeasure = function(measure) {
		if (this.measures[measure.type] == null) {
			// Updating if it's a new value :
			this.measures[measure.type] = new Array();
		}
		this.measures[measure.type]. push({"time" : measure.time, "value" : measure.value});
	};
	
	// ---------------------
	//		 SENSOR
	// ---------------------
	RithmObjects.Sensor = function Sensor(type) {
		this.type = type;
		this.measures = new Array();
		this.subject = {
			id : 0,
			isGlobal : false
		};
	};
		
	RithmObjects.Sensor.prototype.setSubject = function(s, glo) {
		this.subject.id = s;
		this.subject.isGlobal = glo;
	};
	
	RithmObjects.Sensor.prototype.setMeasure = function(measure) {
		if ((this.measures[measure.type] == null) || (this.measures[measure.type]["time"] < measure.time)) {
			// Updating if it's a new value :
			this.measures[measure.type] = {"time" : measure.time, "value" : measure.value};
			// Updating the canvas :
			//~ if (!this.subject.isGlobal) {
				//~ BuildingGenerator.roomShapes[this.subject.id].draw();
			//~ }
		}
	};
	
	// ---------------------
	// 		 ACTUATOR
	// ---------------------
	RithmObjects.Actuator = function Actuator (type) {
		this.type = type;
		this.subjectID = new Array();
	};
		
	RithmObjects.Actuator.prototype.addSubject = function(s, glo) {
		this.subjectID.push({ id : 0, isGlobal : false});
	};
	
	
	// ---------------------
	// 		 PATIENT
	// ---------------------	
	
	RithmObjects.Patient = function Patient(name, isMan, reasonHosp, roomID) {
		this.name = name;
		this.isMan = isMan;
		this.reasonHosp = reasonHosp;
		this.idRoom = roomID;
		this.sensors = new Array();
		this.actuators = new Array();
	};
	
	RithmObjects.Patient.prototype.addSensor = function(sensor) {
		this.sensors.push(sensor);
	};

	RithmObjects.Patient.prototype.addActuator = function(actu) {
		this.actuators.push(actu);
	};
	
		
	// ---------------------
	// 		 WARNING
	// ---------------------	
	RithmObjects.Warning = function Warning (room, content) {
		this.room = room;
		room.warning++;
		this.content = content;
	};
	