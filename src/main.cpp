/*  Project EHAM: Ethernet, Home Assistant, Arduino, MQTT
    Code, licence and attributions are here:
    https://github.com/bingo-bango/EHAM

    Usage instructions:
    ===================
    - Modify settings.h as needed for your hardware and network configuration
    - Add your project code in the main loop below and/or setup if you have specific needs

    Examples are given in the main github repo

*/

#include <Arduino.h>
#include <MQTT.h>
#include <SPI.h>
#include <Ethernet.h>
#include <settings.h>

// these values are defined in settings.h
int dbg = DEBUG;
int dhcp = DHCP;
const char hostname[] = HOSTNAME;
byte mac[] = MAC;
byte ip[] = IP;
byte gateway[] = GATEWAY;
byte server[] = SERVER;

EthernetClient net;
MQTTClient client;

unsigned long lastMillis = 0;
int fcon = 0;
std::string localIP;

void connect() {
  // if(dbg==1){Serial.print("connecting...");}
  Serial.print("connecting...");
  while (!client.connect("arduino", "public", "public")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/hello");
  
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void send_discovery() {
  /* this sends an MQTT message for each component to enable
     Home Assistant to discover it. It can be set to repeat every
     n minutes, see settings.h   
  */
  char discovery_topic[] = "<discovery_prefix>/<component>/[<node_id>/]<object_id>/config";
  char discovery_payload[] = "{json payload}";
  client.publish(discovery_topic);

}

void setup() {
  // setup ethernet 
  

  Serial.begin(9600);

  delay(1024);//<--important for W5100 module CHECK IF NEEDED

    // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // no point in carrying on, so do nothing forevermore:
    while (true) {
      delay(1);
    }
  }

  localIP = (Ethernet.localIP());
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());

  client.begin("192.168.0.2", net);
  client.onMessage(messageReceived);
  

}

void loop() {

  client.loop();

  if (!client.connected()) {
    connect();
    fcon = 0;
  }

  if (client.connected()) {
    if (fcon==0) {
      client.publish("/hello", "MQTT connected, IP address is ");
      fcon = 1;
    }
  }
  



  
  // publish a message roughly every second.
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    client.publish("/hello", "world");
  }
  
}