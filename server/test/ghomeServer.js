var net = require('net');

var server = net.createServer(function(c) {
	console.log('Fake ghome server connection.\n');
	
	c.on('end', function() {
		console.log('Connection aborted.\n');
	});
	
	c.on('data', function(json) {
		var data = JSON.parse(json);
		
		console.log('Data received : ');
		for (var key in data) {
			console.log(key + " : " + data[key]);
		}
		console.log('');
	});
});

server.listen(1234, function() {
	console.log('Fake ghome server  bound.\n');
});
