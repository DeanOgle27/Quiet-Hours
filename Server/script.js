/*
	Vish Anand 2019
*/

var express = require('express');
const exec = require('child_process').exec;
var mustache = require('mustache');
var fs = require('fs');
var app = express();

// server defaults, can be changed in settings page!
var myDeviceId = "cIcDgTYwwIODUEYGWIg5ov4dqdlVIcT1DJzOmpHdF4CoSfKEtMxrtVqHgdoL9mubhFMbkLJDEtvYAEwEiO3JoCkAPtq2tmmqKBFvJkX6aTNExhVSPtxIRuKzbOm98UOx9iSBfLdOv7jWjm0oV4E2vmUg1xlCEbTa";
var myBotId = "a20e1e25f21f5e22070c6bed00";
var myThreshold = 500;
var myTiming = 30;
var myWarningMessages = ["Hi guys can you be a little quieter please!", "Quiet hours are in effect!"];
var settingsTemplate = fs.readFileSync('settingsTemplate.html', 'utf8');
var lastTen = [];
var warningsOn = true;
var lastWarning = 0;

app.get('/', function(req, res){
	res.sendFile(__dirname + '/index.html');
});

app.get('/settings', function(req, res){
	var view = {
		threshold: myThreshold,
		botId: myBotId,
		deviceId: myDeviceId,
		theTime: myTiming,
		warningMessages: function() {
			var text = myWarningMessages[0];
			for (i=1; i<myWarningMessages.length; i++){
				text += "\n";
				text += myWarningMessages[i];
			}
			return text;
		},
		checkbox: warningsOn
	};


	var html = mustache.to_html(settingsTemplate, view);
	res.send(html);
});

app.get('/submitSettings', function(req, res){
	myThreshold = req.query.threshold;
	myDeviceId = req.query.deviceId;
	myTiming = req.query.time;
	myWarningMessages = req.query.warnings.split(/\r\n|\r|\n/g);
	checkbox = req.query.checkBox;
	res.send("successful settings update!<br><a href=\"/settings\">Go Back!</a>");
	console.log("settings updated!");
});

app.get('/jon', function(req, res){
	var mNum = Math.floor(Math.random() * myWarningMessages.length);
	var message = myWarningMessages[mNum];
	exec('curl -d \'{"text" : "' + message + '", "bot_id" : "' + myBotId + '"}\' https://api.groupme.com/v3/bots/post');
	console.log("Floor has been warned!");
});

app.get('/log', function(req, res){
	var html = "<!DOCTYPE html><html lang=\"en\"><head><title>Log - Quiet Hours</title>";
	html += "<meta http-equiv=\"refresh\" content=\"10; URL=http://quiethours.vishanand.com/log\"></head>";
	html += "<body><h2>Loudness Values from most to least recent (10 second increments):</h2>";
	for (i=lastTen.length-1;i>=0;i--){
		html += lastTen[i];
		html += "<br>";
	}
	html += "</body></html>";
	res.send(html);
});

app.get('/send_data', function(req, res){
	var loudness = Number(req.query.mic);
	if (!isNaN(loudness)){
		lastTen.push(loudness);
		if (lastTen.length > 1000){
			lastTen.shift();
		}
	}
	if (!isNaN(loudness) && loudness > myThreshold){
		res.send("Loudness warning triggered!");
	} else {
		res.send("Data sent to server successfully!");
	}
	console.log("Mic Value: " + req.query.mic);
	var currTime = Date.now() / 1000;
	console.log(currTime);
	if (warningsOn && req.query.deviceId == myDeviceId && !isNaN(loudness) && loudness > myThreshold && (currTime - lastWarning > myTiming)){
		var mNum = Math.floor(Math.random() * myWarningMessages.length);
		var message = myWarningMessages[mNum];
		exec('curl -d \'{"text" : "' + message + '", "bot_id" : "' + myBotId + '"}\' https://api.groupme.com/v3/bots/post');
		console.log("Floor has been warned!");
		lastWarning = Date.now() / 1000;
	}
});

app.listen(80);
