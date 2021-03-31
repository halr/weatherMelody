/**
 * This sketch  accesses the ITP Weather Band's database and get weather data.
 * 
 * Board: Arduino SAMD Boards: Arduino MKR 1000
 */
#include <SPI.h>
#include <WiFi101.h>            // https://www.arduino.cc/en/Reference/WiFi101
#include "arduino_secrets.h"
#include <ArduinoHttpClient.h>  // https://www.arduino.cc/reference/en/libraries/arduinohttpclient/
#include "MIDIUSB.h"

const int mkrLED = 6;             // Onboard LED pin, Is this LED_BUILTIN???
unsigned long previousMillis = 0;
const int bpm = 120;  // beats per minute
const int beatDuration = (60 * 1000)/bpm;
int lastNote = 0;

// WiFi
int status = WL_IDLE_STATUS;      // the WiFi radio's status
WiFiClient wifi;

// Arduino Http Client
const char serverAddress[] = "weatherband.itp.io";
const int port = 3000;
int counter = 2;
HttpClient http = HttpClient(wifi, serverAddress, port);

void setup() {
  pinMode(mkrLED, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
  while (!Serial);
  Serial.println("attempting to connect to WiFi network...");
  while ( status != WL_CONNECTED) {
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to WiFi network.");
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= beatDuration) {
    previousMillis = currentMillis;

    sendNoteOff(0,lastNote,0);
    
    // Fetch data based on id
    digitalWrite(LED_BUILTIN, HIGH);
    String path = "/data/id/";
    path+= counter;
    Serial.print("Fetch data: ");
    Serial.println(path);
    http.get(path);
    counter+=100;

    // read the status code and body of the response
    int statusCode = http.responseStatusCode();
    String weatherRsp = http.responseBody();
    Serial.print("statusCode: ");
    Serial.println(statusCode);
    if (statusCode == 200) {
      digitalWrite(LED_BUILTIN, LOW);
      //Serial.print("response: ");
      //Serial.println(weatherRsp);
      int temperature = parseJsonForValue(weatherRsp, "temperature");
      int humidity = parseJsonForValue(weatherRsp, "humidity");
      
      int note = constrain(temperature, 0, 127);
      int velocity = constrain(humidity, 0, 127);
      // play data
      sendNoteOn(0,note,velocity);
      lastNote = note;
    }
  }
}

float parseJsonForValue(String json, String key) {
  // parse the response looking for key:
  int labelStart = json.indexOf(key);
  int dataStart = json.indexOf(" ", labelStart);
  int dataEnd = json.indexOf(",", dataStart);
  String dataStr = json.substring(dataStart + 1, dataEnd);
  Serial.println(dataStr);
  float returnValue = dataStr.toFloat();
  returnValue+=0.5; //to handle rounding
  return returnValue;
}

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void sendNoteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t midiMsg = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(midiMsg);
}

void sendNoteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t midiMsg = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(midiMsg);
}
