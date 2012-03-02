function fetchSensorLogComet(idSensor, sensorLog, callback) {
	function getLastMeasures() {
		var toDate = new Date();
	
		var req = {
			sensors: [{
				id: idSensor,
				from: new Date(getLastMeasures.lastUpdate).getTime(),
			}]	
		};
		getLastMeasures.lastUpdate = toDate; // Using the fact that JS functions can have attributes to store the last date.
		return req;
	}
	getLastAlerts.lastUpdate = new Date(0);	
	
	function addValues(data) {
		var records = data.records[idSensor];
		for( var i in records) {
			sensorLog.addMeasure(measure);
		}
	}
	
	function callBackFinal(data) {
		addValues(data);
		callback(sensorLog);
	}
	createComet('sensors', 'POST', 1000, getLastMeasures, callBackFinal); // Function defined in common.js
}

function fetchSensorLog(idSensor, sensorLog, callback) {
	function getLastMeasures() {
		var toDate = new Date();
		var strDate = getLastMeasures.lastUpdate.getTime();
		var req = {
			"from" : strDate
		};
		getLastMeasures.lastUpdate = toDate; // Using the fact that JS functions can have attributes to store the last date.
		
		function addValues(data) {
			var records = data.records[idSensor];
			for( var i in records) {
				sensorLog.addMeasure(measure);
			}
		}
		
		function callBackFinal(data) {
			addValues(data);
			callback(sensorLog);
		}
		
		$.ajax({
			type: 'POST',
			url: rest+'/sensors',
			data: req,
			success: callBackFinal,
			dataType: 'json',
			async:true
		});	
	};
	getLastMeasures.lastUpdate = new Date(0);
	setInterval(getLastMeasures,2000);
}

function getSensorValues(idSensor, callback, from, to) {
	var req = {
		sensors: [
			{
				id: idSensor,
				from: new Date(from).getTime(),
			}
		]
	};
	if(to) req.sensors[0].to =  new Date(to).getTime()
	
	$.post(rest + '/sensors',
	  req,
	  callback,
	  "json");
}

function getSensorValuesByType(idSensor, callback, typeMesure, from, to) {
	var req = {
		sensors: [
			{
				id: idSensor,
				from: new Date(from).getTime(),
				type: typeMesure
			}
		]
	};
	if(to) req.sensors[0].to =  new Date(to).getTime()
	
	$.post(rest + '/sensors',
	  req,
	  callback,
	  "json");
}

function getSensors(idPatient, callback) {
	var req = {
		idPatient: idPatient
	};
	$.post(rest + '/list_sensors',
	  req,
	  callback,
	  "json");
}

// TODO create a service to get these values
function getRecordtypesBySensortype(sensortype) {
	switch(sensortype) {
		case 0x0060001:
			return [1];
		case 0x0050201:
			return [2];
		case 0x0070205:
			return [3];
		case 0x0070401:
			return [3,4];
		case 0x0070801:
			return [5,6];
		case 0x0070901:
			return [8];
		case 0x0070A01:
			return [9];
		case 0x00A0001:
			return [3,5,7];
	}
}

// TODO create a service to get these values
function recordtypeToString(recordtype) {
	switch(recordtype) {
		case 1:
			return "contact";
		case 2:
			return "bouton";
		case 3:
			return "température";
		case 4:
			return "humidité";
		case 5:
			return "luminosité";
		case 6:
			return "présence";
		case 7:
			return "mouvement";
		case 8:
			return "niveau CO2";
		case 9:
			return "rythme cardiaque";
		default:
			return "inconnu";
	}
}
