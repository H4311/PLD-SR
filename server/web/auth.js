var handler;
var login;
var pwd;

var authObject = {
	init: function init(p_handler, p_login, p_pwd) {
		handler = p_handler;
		login = p_login;
		pwd = p_pwd;
	},
	
	checkAuth: function checkAuth(url) {
		if (url == '/auth' || url == '/(login)?') 
			return handler[url];
		else
			return function (req, res) {
				if (req.session.auth === undefined) {
					// redirect to login page with next = url
					// console.log("Url de redirection : " + url);
					res.redirect('/login?next=' + url);
				} else {
					// calls handler
					handler[url](req, res);
				}		
			}
	},
	
	auth: function auth(req, res) {
		var f_login = req.param("login", null);
		var f_pwd = req.param("password", null);
		var next = req.param("next", null);
		
		//console.log("Tentative de connexion avec login = " + login + " / password = " + pass);
		if (login === f_login && pwd === f_pwd) {
			//console.log("Connexion OK. Redirection vers bonne page : " + next);
			req.session.auth = true;
			if (!next) {
				//console.log("Next est non défini...");
				res.redirect('/index');
			} else {
				handler[next](req, res);
			}
	
		} else {
			//console.log("Connexion infructueuse, redirection vers Login");
			res.redirect('/login' + (next) ? '?next=' + next : '');
		}
	},
	
	logout: function logout(req, res) {
		if (req.session.auth !== undefined) {
			req.session.destroy();
		}
		res.redirect('/login');
	}
};

exports.authModule = authObject;
