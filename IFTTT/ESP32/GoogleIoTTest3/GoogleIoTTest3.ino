 /***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution

  Code is edited by Sachin Soni for it's project called
  Ultimate Home Automation

  For Project video, visit his YouTube channel named "CreativeDesk"

 
  From: https://www.youtube.com/watch?v=XTa6r6hLNB8
 
 ****************************************************/
//for esp32 use <wifi.h> ,for esp8266 use <esp8266wifi.h>
// this code is for esp32 for using esp8266 you just need to change <wifi.h> into <esp8266wifi.h> and also change the relay pin 
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "switchKaKu.h"
#include "GoogleIOT.h"
#include <ESP32_Servo.h>





/************************* Pin Definition *********************************/

//Relays for switching appliances
#define Coffee            22
#define buzzer            26

//buzzer to know the status of MQTT connections and can be used for any other purpose according to your project need.




/************************* WiFi Access Point *********************************/

#define WLAN_SSID       IOT_SSID
#define WLAN_PASS       IOT_PASSWORD

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    IOT_AIO_USERNAME
#define AIO_KEY         IOT_AIO_KEY

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe MakeCoffee = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/coffee");
Adafruit_MQTT_Publish   ReadyMachine  = Adafruit_MQTT_Publish  (&mqtt, AIO_USERNAME "/feeds/coffee");
Adafruit_MQTT_Subscribe CoffeeReady   = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/coffee-ready");
Adafruit_MQTT_Publish   ReadyPublish  = Adafruit_MQTT_Publish  (&mqtt, AIO_USERNAME "/feeds/coffee-ready");
Adafruit_MQTT_Subscribe CoffeeMachine = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/coffee-machine");
//Adafruit_MQTT_Subscribe MakingCoffee  = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/making-coffee");



/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();




Servo servo;
uint8_t servo_position = 0;



void setup() {
  Serial.begin(115200);

  delay(10);

  pinMode(Coffee, OUTPUT);


  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
  
  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&MakeCoffee);
  mqtt.subscribe(&CoffeeReady);
  mqtt.subscribe(&CoffeeMachine);

  servo.attach(21, 500, 2000);
  servo.write(0);
}


void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();
  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {
    static uint8_t readyToMakeCoffee = 0;
    static uint8_t coffeeMachine = 0;
    if (subscription == &CoffeeMachine) {
      if (atoi((char *)CoffeeMachine.lastread)) {
        Serial.println(F("Turning the coffee machine on."));
      }
      else {
        Serial.println(F("Turning the coffee machine off."));
      }
      coffeeMachine = coffee_machine(atoi((char *)CoffeeMachine.lastread));
    }
    if (subscription == &MakeCoffee) {
      if (atoi((char *)MakeCoffee.lastread)) {
        if (coffeeMachine) {
          if (readyToMakeCoffee) {
            Serial.println(F("Making coffee."));
            COFFEE();
          }
          else {
            Serial.println(F("Can't make coffee, because the coffee machine isn't ready."));
            delay(5000);
            ReadyMachine.publish(0);
          }
        }
      }
    }
    if (subscription == &CoffeeReady) {
      if (atoi((char *)CoffeeReady.lastread)) {
        Serial.println(F("The coffee machine is ready to make coffee."));
      }
      else {
        Serial.println(F("The coffee machine isn't ready to make coffee."));
      }
      readyToMakeCoffee = atoi((char *)CoffeeReady.lastread);
    }
  }




 
  
  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
    if(! mqtt.ping()) {
    mqtt.disconnect();
    }
  */
}


uint8_t coffee_machine(uint8_t MachineStatus) {
  switchKaku(23, 33477418, 1, 1, MachineStatus, 10);
  return MachineStatus;
}

uint8_t COFFEE() {
  digitalWrite(Coffee, HIGH);
  servo.write(60);
  delay(1000);
  servo.write(0);
  delay(4000);
  digitalWrite(Coffee, LOW);
  ReadyPublish.publish(0);
  delay(5000);
  ReadyMachine.publish(0);
  return 0;
}


// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
  digitalWrite(buzzer, HIGH);
  delay(2000);
  digitalWrite(buzzer, LOW);
}
