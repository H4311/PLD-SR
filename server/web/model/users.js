var logger = require("../logger");

var credentials = {
	arnal: "4rn4l",
	tibal: "t!b4l",
	jerem: "j3r3m",
	danny: "d4nny",
	bill : "b!ll",
	boule: "b0ul3"
};

/*
 * Stub which simulates the retrieval of credentials in a database.
 * Could be implemented, couldn't it ?
 */
function getCredentials() {
	logger.info("Gettings credentials...");
	return credentials;
}

exports.getCredentials = getCredentials;
