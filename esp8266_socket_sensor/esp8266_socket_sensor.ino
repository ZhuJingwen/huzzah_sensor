#include <ESP8266WiFi.h>

const char* ssid = "Yami-Yichi-2G";
const char* password = "p0rkbun5";
const char* host = "192.168.0.6";
const int port = 8080;  // port for the socket connection

WiFiClient socket;      // variable for the socket connection

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  socket.setTimeout(10);

  
   WiFi.begin(ssid, password);
  Serial.print("Connecting to ");   // connect to access point
  Serial.println(ssid);
  // wait for connection to network access point:
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // when connected to access point, acknowledge it:
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); // print device's IP address

}

boolean login() {
  socket.connect(host, port);   // attempt to connect

  while (!socket.connected()) { // While not connected, try again
    delay(1000);
    if (socket.connected()) {   // if you connected,
      socket.println("hello");  // say hello to the server
    } else {
      // if not connected, try again:
      Serial.println("connection failed, trying again");
      socket.connect(host, port);
    }
  }
}

void loop() {
    // Read the reply from server and print them to serial port:
  while (socket.available()) {
    Serial.print("Got something");
    String input = socket.readString();
    Serial.print(input);
  }

    // Read the reply from serial port and print them to server:
  while (Serial.available()) {
    char input = Serial.read();
    // turn on the LEDs depending on what comes in the serial:
    switch (input) {
      case 'l':       // left
        //digitalWrite(leftPin, HIGH);
        socket.print("sensor1=25");
        break;
      case 'r':       // right
        socket.print(input);
        //digitalWrite(rightPin, HIGH);
        break;
      case 'u':       // up
        socket.print(input);
        //digitalWrite(upPin, HIGH);
        break;
      case 'd':      // down
        socket.print(input);
        //digitalWrite(downPin, HIGH);
        break;
      case '1':      // button pushed
        if (socket.connected()) {   // if the socket's connected, disconnect
          socket.print('x');        // by sending an x
        } else {                    // if the socket's not connected,
          login();                  // login to the server
        }
        break;
    }
  }
}


