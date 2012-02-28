function commandActuator(idDevice, type, active, value, callback) {
	var req = {
		id: idDevice,
		type: type ,
		active: active,
		value : value
	};
	
	$.ajax({
		type: 'POST',
		url: rest+'/actuators',
		data: JSON.stringify(req),
		success:  callback,
		dataType: 'json',
		async:true
	});
}