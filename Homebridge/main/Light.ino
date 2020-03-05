
#define light_bedroom 2


void setup_Light() {
  // Initialize the output variables as outputs
  pinMode(light_bedroom, OUTPUT);
  // Set outputs to LOW
  digitalWrite(light_bedroom, LOW);
}

void light_Bedroom() {
  // turns the GPIOs on and off
  if (header.indexOf("GET /light_bedroom/on") >= 0) {
    lightState = "on";
    digitalWrite(light_bedroom, HIGH);
  } else if (header.indexOf("GET /light_bedroom/off") >= 0) {
    lightState = "off";
    digitalWrite(light_bedroom, LOW);
  }
}


void loop_light() {

}
