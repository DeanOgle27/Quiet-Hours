#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
// Authors:
//     Vish Anand
//     Dean Ogle
// <---------------------------------------2019----------------------------------->

// Counter for the LEDs so they blink
int ledCounter = 0;

// Keeps track of if each of the LEDs should be on
boolean blueOn = false;
boolean redOn = true;
boolean yellowOn = false;
boolean greenOn = false;

// Keeps track of the previous light states, so it knows when a change occurs
// So it can immediately turn on
boolean bluePrev = false;
boolean redPrev = true;
boolean yellowPrev = false;
boolean greenPrev = false;

// Initializes and declares values for the sound
double micVal = 0;
double maxVol = 0;
double smallMax = 0;
// Initializes and declares strings for the connection to Wifi and Server
const char* ssid = "WiFi@OSU";
const char* deviceId = "cIcDgTYwwIODUEYGWIg5ov4dqdlVIcT1DJzOmpHdF4CoSfKEtMxrtVqHgdoL9mubhFMbkLJDEtvYAEwEiO3JoCkAPtq2tmmqKBFvJkX6aTNExhVSPtxIRuKzbOm98UOx9iSBfLdOv7jWjm0oV4E2vmUg1xlCEbTa";
int run = 1;

// Pins for the LEDs and how long it should flash for (in 1/100ths of seconds)
const int red=D3;
const int blue=D2;
const int green=D1;
const int yellow=D0;
const int flashTime = 45;

void updateLED(){
    // Resets counter to 0 if any of the light states change from off to on
    if((!bluePrev && blueOn) || (!redPrev && redOn) ||(!greenPrev && greenOn) ||(!yellowPrev && yellowOn)){
      ledCounter = 0;
      bluePrev = blueOn;
      redPrev = redOn;
      greenPrev = greenOn;
      yellowPrev = yellowOn;
    }
    // Makes sure all prev values are equal to current values
    bluePrev = blueOn;
    redPrev = redOn;
    greenPrev = greenOn;
    yellowPrev = yellowOn;

    // Flashes the lights if they should be flashed
    if(ledCounter < flashTime){
      if(blueOn){
        digitalWrite(blue, HIGH);
      }else{
        digitalWrite(blue, LOW);
      }
      if(greenOn){
        digitalWrite(green, HIGH);
      }else{
        digitalWrite(green, LOW);
      }
      if(yellowOn){
        digitalWrite(yellow, HIGH);
      }else{
        digitalWrite(yellow, LOW);
      }
      if(redOn){
        digitalWrite(red, HIGH);
      }else{
        digitalWrite(red, LOW);
      }
    }
    // Off part of the blink stage
    else{
      digitalWrite(blue, LOW);
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
      digitalWrite(yellow, LOW);
    }
    // Resets conuter when it gets too big
    if(ledCounter >150){
      ledCounter = 0;
    }
    ledCounter++;
}

void wifiSetup(){
  // Begins to set up wifi
  blueOn = false;
  WiFi.begin(ssid);
  updateLED();
  while (WiFi.status() != WL_CONNECTED) {
    // Tries to connect every 1 second
    delay(1000);
    Serial.print("Connecting to ");
    Serial.println(ssid);
  }
  // Prints to serial monitor that the wifi setup is complete, turns blue led on
  Serial.println("WiFi Setup done");
  blueOn = true;
  updateLED();
}

void setup() {
  // Initializes IO pins
  pinMode(A0, INPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  // Initialize the LED_BUILTIN pin as an output
  // Sets up the serial whatever its called
  Serial.begin(115200);
  delay(2000);
  Serial.println("Serial Console Setup done");
  updateLED();
  wifiSetup();
}

// the loop function runs over and over again forever
void loop() {
  //Serial.println(WiFi.macAddress());
  micVal = analogRead(A0);
  if (micVal > smallMax){
    smallMax = micVal; // 1 second max
  }
  if (micVal > maxVol){
    maxVol = micVal; // 10 second max
  }

  run++;
  if (run > 1000){
    run = 0; // every 10 seconds resets the counter
  }

  if (run == 0){ // every 10 seconds
    // updates or attempts to update the server with information, checks if still connected
    // to wifi as well
    yellowOn = false;
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      char str[400]; 
      snprintf(str, 400, "http://quiethours.vishanand.com/send_data?mic=%f&deviceId=%s", maxVol, deviceId);
      http.begin(str);    
      int httpCode = http.GET();
      if (httpCode > 0 ){
        String payload = http.getString();
        Serial.println(payload);
        if (payload == "Loudness warning triggered!"){
          yellowOn = true;
        }
        greenOn = true;
      } else {
        Serial.println("Server could not be reached!");
        greenOn = false;
      }
      http.end();
    } else {
      wifiSetup(); // reconfigure wifi if connection is lost
    }
    maxVol = 0; //reset max
  } else if (run % 100 == 0){ // every 1 second
    Serial.println(smallMax);
    smallMax = 0; //reset max
  }
  // updates the lights for flashing purposes, delays appropriately
  updateLED();
  delay(10);
}
