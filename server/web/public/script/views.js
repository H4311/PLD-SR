	
// ------------------------------------------------------------------------------------
// 		 			VIEWS
// ------------------------------------------------------------------------------------		

var RithmViews = {}
	// ---------------------
	// 		 ROOMSHAPE
	// ---------------------	
	RithmViews.RoomShape = function RoomShape (id, room) {
		var shape = new Kinetic.Shape(function() {
			var ctx = this.getContext();
			
			ctx.beginPath();
			var x0, y0;
			if (this.room.walls[0].isOpen == null) {
				x0 = this.room.walls[0].segmentPlot.x1;
				y0 = this.room.walls[0].segmentPlot.y1;
			}
			else {
				x0 = this.room.walls[0].plotClosed.segmentPlot.x1;
				y0 = this.room.walls[0].plotClosed.segmentPlot.y1;
			}
			var previousStyle = ctx.fillStyle;
			
			// Updating the wanted value :
			this.room.measures[BuildingGenerator.wantedMeasure] = this.room.getAverageValue(BuildingGenerator.wantedMeasure);
			
			var color = ProportionalColor(this.room.measures[BuildingGenerator.wantedMeasure], BuildingGenerator.minArrays[BuildingGenerator.wantedMeasure], BuildingGenerator.maxArrays[BuildingGenerator.wantedMeasure], BuildingGenerator.colorArrays[BuildingGenerator.wantedMeasure]);
			
			ctx.fillStyle = 'rgb('+color.red+', '+color.green+','+color.blue+')';
			ctx.moveTo(x0, y0);
			for (var i = 0; i < this.room.walls.length; i++) {
				if (this.room.walls[i].isOpen == null) { // Wall
					ctx.lineTo(this.room.walls[i].segmentPlot.x2, this.room.walls[i].segmentPlot.y2);
				}
				else { // Door
					ctx.lineTo(this.room.walls[i].plotClosed.segmentPlot.x2, this.room.walls[i].plotClosed.segmentPlot.y2);
				}
			}
			ctx.closePath();
			ctx.fill();
			ctx.fillStyle = previousStyle;
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
			location.href = 'room?id='+ this.idRoom;
		});
		shape.room = room;
		shape.idRoom = id;
		shape.color = "grey";
		return shape;
	};
	RithmViews.RoomShape.prototype = new Kinetic.Shape;
	RithmViews.RoomShape.prototype.constructor = this.RoomShape;
	RithmViews.RoomShape.prototype.parent = Kinetic.Shape.prototype;
	
	// ---------------------
	// 		 ROOMPATH
	// ---------------------	
	RithmViews.RoomPath = function RoomPath (room) {
		var shape = new Kinetic.Shape(function() {
			var ctx = this.getContext();
			
			// Stroke :
			var colorWall = (this.room.warning > 0)? BuildingGenerator.colorWallWarning : BuildingGenerator.colorWall;
			var lineWidthWall = (this.room.warning > 0)? BuildingGenerator.lineWidthWallWarning : BuildingGenerator.lineWidthWall;
			var previousWidth = ctx.lineWidth;
			var previousStyle = ctx.strokeStyle;
			ctx.lineWidth = lineWidthWall;
			ctx.strokeStyle = colorWall;  
			ctx.lineJoin = 'round';
			ctx.beginPath();
			for (var i = 0; i < this.room.walls.length; i++) {
				if (this.room.walls[i].isOpen == null) { // Wall
					ctx.moveTo(this.room.walls[i].segmentPlot.x1,this.room.walls[i].segmentPlot.y1);  
					ctx.lineTo(this.room.walls[i].segmentPlot.x2, this.room.walls[i].segmentPlot.y2);
				}
				else { // Door
					ctx.stroke();
					ctx.beginPath();
					ctx.lineWidth = BuildingGenerator.lineWidthDoor;
					ctx.strokeStyle = BuildingGenerator.colorDoor;  
					
					if (this.isOpen) {
						ctx.moveTo(this.room.walls[i].plotOpen.segmentPlot.x1,this.room.walls[i].plotOpen.segmentPlot.y1);  
						ctx.lineTo(this.room.walls[i].plotOpen.segmentPlot.x2,this.room.walls[i].plotOpen.segmentPlot.y2); 
						ctx.moveTo(this.room.walls[i].plotClosed.segmentPlot.x2, this.room.walls[i].plotClosed.segmentPlot.y2);
					}
					else {
						ctx.moveTo(this.room.walls[i].plotClosed.segmentPlot.x1,this.room.walls[i].plotClosed.segmentPlot.y1);  
						ctx.lineTo(this.room.walls[i].plotClosed.segmentPlot.x2,this.room.walls[i].plotClosed.segmentPlot.y2); 
					}
					
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
			
			// Print name :
			previousFont = ctx.font;
			previousColor = ctx.fillStyle;
			ctx.font = "12pt Calibri";
			ctx.fillStyle = "black";
			ctx.fillText(this.room.name, this.room.walls[0].segmentPlot.x1+10, this.room.walls[0].segmentPlot.y1+16);
			ctx.font = previousFont;
			ctx.fillStyle = previousColor;
		});
		shape.room = room;
		shape.color = "grey";
		return shape;
	};
	RithmViews.RoomPath.prototype = new Kinetic.Shape;
	RithmViews.RoomPath.prototype.constructor = this.RoomPath;
	RithmViews.RoomPath.prototype.parent = Kinetic.Shape.prototype;
	
	// ---------------------
	// 		 WARNINGCIRCLE
	// ---------------------	
	RithmObjects.WarningCircle = function WarningCircle (id, warning) {
		var shapeW = new Kinetic.Shape(function() {
			var context = this.getContext();
			drawCircle(context, this.warning.room.walls[0].segmentPlot.x1+25, this.warning.room.walls[0].segmentPlot.y1+28, 10, 'rgb(200,50,50)');
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
	RithmObjects.WarningCircle.prototype = new Kinetic.Shape;
	RithmObjects.WarningCircle.prototype.constructor = this.WarningCircle;
	RithmObjects.WarningCircle.prototype.parent = Kinetic.Shape.prototype;
	
	// ---------------------
	// 		 WARNINGMARK
	// ---------------------	
	RithmObjects.WarningMark = function WarningMark (id, warning) {
		var shapeW = new Kinetic.Shape(function() {
			var context = this.getContext();
			drawExclame(context, this.warning.room.walls[0].segmentPlot.x1+25, this.warning.room.walls[0].segmentPlot.y1+28, 10, 'rgb(255,255,255)');
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
	RithmObjects.WarningMark.prototype = new Kinetic.Shape;
	RithmObjects.WarningMark.prototype.constructor = this.WarningMark;
	RithmObjects.WarningMark.prototype.parent = Kinetic.Shape.prototype;