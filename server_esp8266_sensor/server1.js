var net = require('net');
var socketio = require('socket.io-client')('http://localhost:3000');

var connected = false;
/*
 * Callback method executed when a new TCP socket is opened.
 */

 socketio.on('connect', function(){
 	console.log("connected to socket.io server");
 	connected = true;
 });

 socketio.on('disconnect', function(){
 	console.log("Disconnected to socket.io server");
 	connected = false;
 });

function newSocket(socket) {
	console.log("new connection");
	//console.log(socket.address());
	socket.write('Welcome to the Telnet server!');

	socket.on('data', function(data) {
		//console.log(data.toString('utf8'));
		var inputString = data.toString('utf8');
		var inputChar = inputString.split("");
		var dataToSend;
		//find data source
		var indexSensor1 = inputString.indexOf("sensor1");
		if(indexSensor1 > -1){
			//the data is from sensor 1
			dataToSend = inputChar.slice(indexSensor1+8, inputChar.length-indexSensor1);
			dataToSend = dataToSend.join("");
		}
		if(connected == true){
			socketio.emit('data1', dataToSend);
			socket.write(dataToSend); //echo back
		}else{
			console.log("no socket io connection")
		}

		
	});
}
 
// Create a new server and provide a callback for when a connection occurs
var server = net.createServer(newSocket);
 
// Listen on port 8888
server.listen(8080, function(){
	console.log('listening on *:8080'); 
});