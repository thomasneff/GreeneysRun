Pebble.addEventListener('appmessage', function(e) {
//  console.log('PebbleKit JS ready!');
  console.log(e.payload.score);
  // The exact date
  var date = new Date();
  //date.setHours(date.getHours() + 1);
  if(!Pebble.getActiveWatchInfo) //this is supported in SDK 3
    return;
  // Create the pin
  var pin = {
    "id": "pin-Greeneys-Run-HighScore",
    "time": date.toISOString(),
    "layout": {
      "type": "genericPin",
      "lastUpdated" : date.toISOString(),
      "backgroundColor" : "#00AA00",
      "title": "Greeney's Run",
      "subtitle" : "High Score: " + e.payload.score,
      "body" : "Congratulations, you achieved a new High Score in Greeney's Run!\n" + "Score: " + e.payload.score,
      "tinyIcon": "system://images/GLUCOSE_MONITOR",
      "smallIcon": "system://images/GLUCOSE_MONITOR",
      "largeIcon": "system://images/GLUCOSE_MONITOR"
    },
    "createNotification": {
      "layout": {
        "type": "genericNotification",
        "title": "Greeney's Run",
        "subtitle" : "High Score!",
        "backgroundColor" : "#00AA00",
        "tinyIcon": "system://images/NOTIFICATION_FLAG",
        "body": "Your Score of " + e.payload.score + " points was added to the timeline!"
      }
    },
      "updateNotification": {
        "time": date.toISOString(),
    "layout": {
      "type": "genericNotification",
      "title": "Greeney's Run",
      "subtitle" : "High Score!",
      "backgroundColor" : "#00AA00",
      "tinyIcon": "system://images/NOTIFICATION_FLAG",
      "body": "Your new High Score of " + e.payload.score + " points was added to the timeline!"}
    },
    "actions": [
  {
    "title": "Play Greeney's Run",
    "type": "openWatchApp",
    "launchCode": 0
  }]
    
  };

 //console.log('Inserting pin in the future: ' + JSON.stringify(pin));

  insertUserPin(pin, function(responseText) { 
    console.log('Result: ' + responseText);
  });
});


// Copyright by Pebble Technology, 2015 Licensed under the MIT license: https://raw.githubusercontent.com/pebble-examples/timeline-push-pin/master/LICENSE
/******************************* timeline lib *********************************/

// The timeline public URL root
var API_URL_ROOT = 'https://timeline-api.getpebble.com/';

/**
 * Send a request to the Pebble public web timeline API.
 * @param pin The JSON pin to insert. Must contain 'id' field.
 * @param type The type of request, either PUT or DELETE.
 * @param callback The callback to receive the responseText after the request has completed.
 */
function timelineRequest(pin, type, callback) {
  // User or shared?
  var url = API_URL_ROOT + 'v1/user/pins/' + pin.id;

  // Create XHR
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
   // console.log('timeline: response received: ' + this.responseText);
    callback(this.responseText);
  };
  xhr.open(type, url);

  // Get token
  Pebble.getTimelineToken(function(token) {
    // Add headers
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.setRequestHeader('X-User-Token', '' + token);

    // Send
    xhr.send(JSON.stringify(pin));
   // console.log('timeline: request sent.');
  }, function(error) { console.log('timeline: error getting timeline token: ' + error); });
}

/**
 * Insert a pin into the timeline for this user.
 * @param pin The JSON pin to insert.
 * @param callback The callback to receive the responseText after the request has completed.
 */
function insertUserPin(pin, callback) {
  timelineRequest(pin, 'PUT', callback);
}

/**
 * Delete a pin from the timeline for this user.
 * @param pin The JSON pin to delete.
 * @param callback The callback to receive the responseText after the request has completed.
 */
function deleteUserPin(pin, callback) {
  timelineRequest(pin, 'DELETE', callback);
}

/***************************** end timeline lib *******************************/