function fetchAlerts(callback) {
	function getLastAlerts() {
		var toDate = new Date();
	
		var req = {
			"from" : dateToString(getLastAlerts.lastUpdate),
			"to" : dateToString(toDate)
		};
		getLastAlerts.lastUpdate = toDate; // Using the fact that JS functions can have attributes to store the last date.
		return req;
	}
	getLastAlerts.lastUpdate = new Date(0);	
	
	createComet('alerts', 'POST', getLastAlerts, callback); // Function defined in common.js
}