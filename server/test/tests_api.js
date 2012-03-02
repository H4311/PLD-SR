var APIeasy = require('api-easy'),
    assert = require('assert');

var suite = APIeasy.describe('Tests for REST server');

suite.use('localhost', 1337)
     .setHeader('Content-Type', 'application/json')
     // sensors
     .post("/sensors", {sensors:[{"id":1, "from": 1}]})
         .expect(200)
         .expect('Sensors: Checks results are coherent with not null values', function (err, res, body) {
			var result = JSON.parse(body);
			assert.isNotNull(result.records);
			assert.isNotNull(result.records["1"][0].time);
			assert.isNotNull(result.records["1"][0].value);
			console.log("Test sensors is OK");
		 })
	.next()
	// actuators
	.post("/actuators", {id:1, type:17105409, active:1, value:10})
         .expect(200)
         .expect('Actuators: Checks status', function (err, res, body) {
			var result = JSON.parse(body);
			console.log("Body : " + body);
			assert.equal(result.status, "ok");
			console.log("Test actuators is OK");
		 })
	.next()
     // list_sensors
     .post("/list_sensors", {})
         .expect(200)
         .expect('List sensors without id : Checks results are sensors with not null values', function (err, res, body) {
			var result = JSON.parse(body);
			assert.isNotNull(result.hits);
			assert.isNotNull(result.hits[0].id);
			assert.isNotNull(result.hits[0].type);
			assert.isNotNull(result.hits[0].numeroCapteur);
			assert.isNotNull(result.hits[0].isGlobal);
			assert.isNotNull(result.hits[0].idSujet);
			console.log("Test list sensors without id is OK");
		 })
	.next()
	.post("/list_sensors", {idRoom: 1})
         .expect(200)
         .expect('List sensors with id Room : Checks results are sensors with not null values', function (err, res, body) {
			var result = JSON.parse(body);
			assert.isNotNull(result.hits);
			assert.isNotNull(result.hits[0].id);
			assert.isNotNull(result.hits[0].type);
			assert.isNotNull(result.hits[0].numeroCapteur);
			assert.isNotNull(result.hits[0].isGlobal);
			assert.isNotNull(result.hits[0].idSujet);
			console.log("Test list sensors with idRoom is OK");
		 })
	.next()
	.post("/list_sensors", {idPatient: 1001})
         .expect(200)
         .expect('List sensors with id Patient : Checks results are sensors with not null values', function (err, res, body) {
			var result = JSON.parse(body);
			assert.isNotNull(result.hits);
			assert.isNotNull(result.hits[0].id);
			assert.isNotNull(result.hits[0].type);
			assert.isNotNull(result.hits[0].numeroCapteur);
			assert.isNotNull(result.hits[0].isGlobal);
			assert.isNotNull(result.hits[0].idSujet);
			console.log("Test list sensors with idPatient is OK");
		 })
	// /list_actuators
	.post("/list_actuators", {})
         .expect(200)
         .expect('List actuators : Checks results are actuators with not null values', function (err, res, body) {
			var result = JSON.parse(body);
			assert.isNotNull(result.hits);
			assert.isNotNull(result.hits[0].id);
			assert.isNotNull(result.hits[0].type);
			console.log("Test list actuators is OK");
		 })
	.next()
	// /patients
	.post("/patients", {})
         .expect(200)
         .expect('Patients : Checks results with not null values', function (err, res, body) {
			var result = JSON.parse(body);
			assert.isNotNull(result.hits);
			assert.isNotNull(result.hits[0].id);
			assert.isNotNull(result.hits[0].nom);
			assert.isNotNull(result.hits[0].isMan);
			assert.isNotNull(result.hits[0].raisonHospitalisation);
			assert.isNotNull(result.hits[0].idPiece);
			console.log("Test patients without id is OK");
		 })
	.next()
	.post("/patients", {id:1001})
         .expect(200)
         .expect('Patients with id : Checks results with not null values', function (err, res, body) {
			var result = JSON.parse(body);
			assert.isNotNull(result.hits);
			assert.isNotNull(result.hits[0].id);
			assert.isNotNull(result.hits[0].nom);
			assert.isNotNull(result.hits[0].isMan);
			assert.isNotNull(result.hits[0].raisonHospitalisation);
			assert.isNotNull(result.hits[0].idPiece);
			console.log("Test patients with id is OK");
		 })
	.next()
	// /rooms
	.post("/rooms", {})
         .expect(200)
         .expect('Rooms without id : Checks results with not null values', function (err, res, body) {
			var result = JSON.parse(body);
			assert.isNotNull(result.hits);
			assert.isNotNull(result.hits[0].id);
			assert.isNotNull(result.hits[0].nom);
			assert.isNotNull(result.hits[0].description);
			console.log("Test rooms without id is OK");
		 })
	.next()
	.post("/rooms", {id:1})
         .expect(200)
         .expect('Rooms with id : Checks results with not null values', function (err, res, body) {
			var result = JSON.parse(body);
			assert.isNotNull(result.hits);
			assert.isNotNull(result.hits[0].id);
			assert.isNotNull(result.hits[0].nom);
			assert.isNotNull(result.hits[0].description);
			console.log("Test rooms with id is OK");
		 })
	.next()
	// /alerts
	.post("/alerts", {from: 1})
         .expect(200)
         .expect('Alerts : Checks results with not null values', function (err, res, body) {
			var result = JSON.parse(body);
			assert.isNotNull(result.alerts);
			assert.isNotNull(result.alerts[0]);
			assert.isNotNull(result.alerts[0].time);
			assert.isNotNull(result.alerts[0].name);
			console.log("Test alerts with id is OK");
		 })
	.next()
	// /murs
	.post("/murs", {id: 1})
         .expect(200)
         .expect('Murs : Checks results with not null values', function (err, res, body) {
			var result = JSON.parse(body);
			assert.isNotNull(result.hits);
			assert.isNotNull(result.hits[0]);
			assert.isNotNull(result.hits[0].id);
			assert.isNotNull(result.hits[0].idPiece);
			assert.isNotNull(result.hits[0].x1);
			assert.isNotNull(result.hits[0].ordre);
			console.log("Test murs with id is OK");
		 })
	.next()
	// add_device
	.post("/add_device", {id: 1, type: 1})
         .expect(200)
         .expect('Add device : Checks status is ok', function (err, res, body) {
			var result = JSON.parse(body);
			assert.isNotNull(result.status);
			assert.equal(result.status, "ok");
			console.log("Add device is OK");
		 })
	.next()
	// remove_device
	.post("/remove_device", {id: 1})
         .expect(200)
         .expect('Remove device : Checks status is ok', function (err, res, body) {
			var result = JSON.parse(body);
			assert.isNotNull(result.status);
			assert.equal(result.status, "ok");
			console.log("Remove device is OK");
		 })
	.next()
	// rules
	.post("/rules", {
					"nom" : "Règle froid",
					"createsAlert" : 1,
				   
					"idCapteur" : 23,
					"typeMesure": 1,
					"debIT" : -10,
					"finIT" :18,
				  
					"idActionneur" : 34,
					"valeur" : 42,
					"isActive" : 1
				 })
         .expect(200)
         .expect('Adds or updates rule device', function (err, res, body) {
			var result = JSON.parse(body);
			assert.isNotNull(result);
			console.log("Adds rules is OK");
		 })
	.next()
.export(module);
