var socket = io.connect('http://localhost:3000/');

socket.on('connect', function() {
  console.log("Connected");
});

socket.on('data1', function(data) {
  console.log(data);
  drawData(data);
});

function setup() {
  var canvasContainer = document.getElementById("canvasContainer");
  var myCanvas = createCanvas((windowWidth - 100), (windowHeight - 100));
  myCanvas.parent(canvasContainer);
  background(255);
}

function drawData(data) {
  // fill(200, 100, 100);
  // noStroke();
  // ellipse(data, data, 20, 20);
}
