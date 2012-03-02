var users = require('./model/users');

var badPwdError = "La combinaison login / password que vous avez entrée"+
" est incorrecte";

var credentials = users.getCredentials();
var handler;

var authObject = {
	// Inits the auth module.
	// p_handler is the handler of views.
	init: function init(p_handler) {
		handler = p_handler;
	},
	
	// Factory which makes functions that check whether the user is
	// authenticated or not. Returns a function(req, res) which does that, 
	// redirecting to the correct URL.
	checkAuth: function checkAuth(url) {
		// The mecanism obviously must not work if the user is on the
		// login page.
		if (url == '/login') {
			return handler[url];
		} else {
			return function (req, res) {
				if (!req.session.auth) {
					logger.debug("User unauthentified tries to go to " + url);
					res.redirect('/login?next=' + url);
				} else {
					handler[url](req, res);
				}		
			}
		}
	},
	
	/*
	 * Tries to authenticate the user, and if it works, redirects him to
	 * the page he asked.
	 */
	auth: function auth(req, res) {
		var f_login = req.param("login", null);
		var f_pwd = req.param("password", null);
		var next = req.param("next", null);
		
		if (credentials[f_login] && credentials[f_login] === f_pwd) {
			// The user has been correctly authentified ==> redirects to
			// the page he asked
			req.session.auth = true;
			if (!next) {
				// If there was no page, just redirects to index
				res.redirect('/');
			} if (!handler[next]) {
				// The user tries to go to a page which has no handler.
				logger.info("The user tries to go to not available page : " + next + ". Redirecting to 404.");
				res.redirect('*');
			} else {
				handler[next](req, res);
			}
		} else {
			logger.error("[AUTH] Bad credentials with login = " + f_login + " and password = " + f_pwd);
			res.render('login', 
				{title: "Login", next: null, error: badPwdError});
		}
	},
	
	/* 
	 * Logs out the current user, if there was one.
	 */
	logout: function logout(req, res) {
		logger.info("Logouts user.");
		if (req.session.auth !== undefined) {
			req.session.destroy();
		}
		res.redirect('/login');
	}
};

exports.authModule = authObject;
