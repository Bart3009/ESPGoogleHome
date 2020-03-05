// Load Wi-Fi library
#include <WiFi.h>

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String lightState = "off";

// Assign output variables to GPIO pins




void setup() {
  Serial.begin(115200);

  setup_Light();
  setup_WiFi();

}

void loop() {
  loop_WiFi();
}
