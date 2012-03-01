/* This file contains all the functions needed by all the pages. */

/* This extension allows to retrieve query string parameters. */
$.extend({
	  getUrlVars: function(){
		var vars = [], hash;
		var hashes = window.location.href.slice(window.location.href.indexOf('?') + 1).split('&');
		for(var i = 0; i < hashes.length; i++)
		{
		  hash = hashes[i].split('=');
		  vars.push(hash[0]);
		  vars[hash[0]] = hash[1];
		}
		return vars;
	  },
	  getUrlVar: function(name){
		return $.getUrlVars()[name];
	  }
	});

/* Create Comet service (Long Polling Request) */
function createComet(service, action, timeOut, getData, callback) {
    function connectComet () {
	var req = getData();
        $.ajax({
            url: rest + '/' + service,
            timeout: timeOut,
            type: action,
	    data: req,
	    dataType: 'json',
            async: true,
            success: function (data) {
                    connectComet();
                    callback(data);
                },
            error: function (jqXHR) {
                        connectComet();
                }		
        });
    }
    connectComet();
}

/* Time functions */
function dateToString(date) {
	var s = "";
	s += date.getFullYear();
	s += "/";
	s += twoDigits(date.getMonth()+1);
	s += "/";
	s += twoDigits(date.getDate());
	s += " ";
	s += twoDigits(date.getHours());
	s += ":";
	s += twoDigits(date.getMinutes());
	s += ":";
	s += twoDigits(date.getSeconds());
	return s;
}

function twoDigits(nb) {
	var retour = nb < 10 ? "0" + nb : "" + nb;
	return retour;
}
