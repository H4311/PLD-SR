function addDevice(idDevice, type, subject, callback) {
	var req = {
		id: idDevice,
		type: type ,
		subject: subject
	};
	
	$.ajax({
		type: 'POST',
		url: rest+'/add_device',
		data: JSON.stringify(req),
		success:  callback,
		dataType: 'json',
		async:true
	});
}

function addSensor(idDevice, type, idSubject, isGlobal, callback) {
	addDevice(idDevice, type, {i: idSubject, g:(isGlobal?1:0)}, callback);
}

function addActuator(idDevice, type, subjects, callback) {
	var objSub = new Array();
	for (var s in subjects) {
		objSub.push({i: subjects[s][0], g:(subjects[s][1]?1:0)});
	}	
	addDevice(idDevice, type, objSub, callback);
}

function deleteDevice(idDevice) {
	var req = {
		id: idDevice,
	};
	
	$.ajax({
		type: 'POST',
		url: rest+'/remove_device',
		data: JSON.stringify(req),
		success:  callback,
		dataType: 'json',
		async:true
	});
}