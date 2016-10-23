/*---------------------------------------------------------------------------------------------
NodeMCU gets data from Python server, sends to 3pi
--------------------------------------------------------------------------------------------- */
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>

char ssid[] = "PhysCompLab";          // your network SSID (name)
char pass[] = "ideate60223";          // your network password

SoftwareSerial mySerial(1, 0);      // RX, TX

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;

// this is the port that our computer is sending the data to
const unsigned int localPort = 1410;        // local port to listen for UDP packets (here's where we send the packets)

OSCErrorCode error;

void setup() {

  Serial.begin(115200);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  //wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(Udp.localPort());

}

// we will call this function when we recieve a message
void led(OSCMessage &msg) {
  // check if the first piece of data is an int and if so, use it
  int strLen = 0;
  if (msg.isInt(0)) {
    Serial.println("MESSAGE GOES HERE");
  }
}

void loop() {
  OSCMessage msg;
  //get the data from the network
  int size = Udp.parsePacket();

  //only do stuff if we actually got data
  if (size > 0) {
    while (size--) {
      /*
       * if your client was sending an osc bundle 
       * instead of a message, this line would be:
       * bundle.fill(Udp.read());
       */
      msg.fill(Udp.read());
    }
    
    if (!msg.hasError()) {
      /* if the bundle has a message with the
       * address "/led", call the function led.
       * If the message that the client is sending
       * does not have this address, the NodeMCU 
       * wont do anything.
       */
      msg.dispatch("/led", led);

      /* If you are also sending a separate message that has
       *  the address "/motor", you could do something
       *  with it here. 
       */
       //msg.dispatch("/motor", motor_function);
    } else {
      error = msg.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }
}
