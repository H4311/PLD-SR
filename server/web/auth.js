var loginPagePathname = "/users/index.html";

function checkAuth(req, resp, next) {
	if (req.session.auth) {
		console.log("User identified. Continue, please.");
		next();
	} else {
		// redirects to /login
		console.log("User not identified, has to login.");
		serveStatic(loginPagePathname, resp);
	}
}

function login(req, resp, next) {
	var formLogin = "docteur";
	var formPwd = "maboul";
	
	if (formLogin === "docteur" && formPwd === "maboul") {
		console.log("Good authentification, welcome doctor :)");
		req.session.auth = true;
		serveStatic("/", resp);
	} else {
		console.log("Bad tentative of authentification. Cheater!");
		req.session.auth = false;
		serveStatic(loginPagePathname, resp);
	}	
}

function logout(req) {
	req.session.destroy();
}

exports.login = login;
exports.logout = logout;
exports.checkAuth = checkAuth;
