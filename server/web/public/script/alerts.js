function fetchAlertsComet(callback) {
	function getLastAlerts() {
		var toDate = new Date();
	
		var req = {
			"from" : dateToString(getLastAlerts.lastUpdate)
		};
		getLastAlerts.lastUpdate = toDate; // Using the fact that JS functions can have attributes to store the last date.
		return req;
	}
	getLastAlerts.lastUpdate = new Date(0);	
	
	createComet('alerts', 'POST', 1000, getLastAlerts, callback); // Function defined in common.js
}

function fetchAlerts(callback) {
	function getLastAlerts() {
		var toDate = new Date();
		var strDate = dateToString(getLastAlerts.lastUpdate)
		var req = {
			"from" : strDate
		};
		getLastAlerts.lastUpdate = toDate; // Using the fact that JS functions can have attributes to store the last date.
		
		$.ajax({
			type: 'POST',
			url: rest+'/alerts',
			data: req,
			success: callback,
			dataType: 'json',
			async:true
		});	
	};
	getLastAlerts.lastUpdate = new Date();
	setInterval(getLastAlerts,1000);
}

function displayAlerts(ul) {
	fetchAlerts(function(data) {
		for(var i in data.alerts) {
			var a = data.alerts[i];
			var notifTime = dateToString(new Date(a.time/1000));
			$(ul).append('<li class="alert alert-error fade in"><a class="close" data-dismiss="alert">&times;</a><i class="icon-time"></i>&nbsp;'+a.nom+' : '+ $.timeago.inWords(new Date(a.time/1000)) + '</li>');
		}
	})
}