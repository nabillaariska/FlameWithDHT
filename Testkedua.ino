
#include <AntaresESP8266HTTP.h>
#define ACCESSKEY "849297a495603cd9:ad71a5d63346e13c"
#define WIFISSID "Nabillarsk"
#define PASSWORD "boenboen"
#define projectName "FlameWithDHT"
#define deviceName "NodeMCU"
AntaresESP8266HTTP antares(ACCESSKEY);
int redLed = 4;
int buzzer = 5;
int api = 16;
int smokeA0 = A0;
// Your threshold value
int sensorThres = 400;
int data;

void setup() {
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID,PASSWORD);
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
   pinMode(api, INPUT);
  Serial.begin(9600);
}

void loop() {
  int data = digitalRead(api);
  int analogSensor = analogRead(smokeA0);

  Serial.print("Deteksi Asap: ");
  Serial.println(analogSensor);
  Serial.print("Deteksi Api: ");
  Serial.println(data);
  // Checks if it has reached the threshold value
  if (data == LOW)
  {
    digitalWrite(redLed, HIGH);
    tone(buzzer, 1000, 100);
    antares.add(analogSensor);
    //antares.add(data);
    delay(100);
  }
  else if (analogSensor > sensorThres){
    digitalWrite(redLed, HIGH);
    tone(buzzer, 500, 80);
    antares.add(analogSensor);
  //antares.add(data);
    delay (100);
  }
  else
  {
    digitalWrite(redLed, LOW);
    noTone(buzzer);
    antares.add(analogSensor);
  //antares.add(data);
    delay (100);
  }
  antares.send(projectName,deviceName);
  delay(100);
}
