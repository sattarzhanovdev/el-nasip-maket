#include <WiFi.h> 
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

const char* ssid = "TP-Link_3A5E";
const char* password = "90815690";

const char* host = "el-nasi-default-rtdb.asia-southeast1.firebasedatabase.app";
const int httpsPort = 443; // HTTPS port

Adafruit_NeoPixel a_block = Adafruit_NeoPixel(104, 12, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pod = Adafruit_NeoPixel(50, 14, NEO_RGB + NEO_KHZ800);
int bright = 255;
int r = 255;
int g = 157;
int b = 15;
int lastRandomPixels[3] = {-1, -1, -1};

// Диапазоны светодиодов для каждой стороны
int side1Start = 0;
int side1End = 51;
int side2Start = 52;
int side2End = 103;

long lastFloor;
unsigned long lastRandomTime = 0;
unsigned long randomInterval = 1000; // Интервал случайного выключения в миллисекундах


void turnOnAllLeds() {
  a_block.clear();
  for (int i = 0; i < 104; i++) {
    a_block.setBrightness(bright);
    a_block.setPixelColor(i, a_block.Color(g, r, b));
  }
  a_block.show();
}

void turnOffAllLeds() {
  a_block.clear();
  pod.clear();
  for (int i = 0; i < 104; i++) {
    a_block.setBrightness(bright);
    a_block.setPixelColor(i, a_block.Color(0, 0, 0));
  }
  for(int i = 0; i < 50; i++){
    pod.setBrightness(bright);
    pod.setPixelColor(i, pod.Color(0, 0, 0));
    pod.show();
  }
  a_block.show();
}

int getRandomPixel(int start, int end, int lastRandomPixel) {
  int randomPixel;
  do {
    randomPixel = random(start, end + 1);
  } while (randomPixel == lastRandomPixel);
  return randomPixel;
}



void turnOnFloor(char floorLetter) {
  int floor = floorLetter - 'a' + 1;
  int startPixel = (floor - 1) * 8;
  Serial.println("s" + String(startPixel));

  a_block.clear();

  if(floorLetter == 'k'){
    for (int i = 80; i < 88 + 8; i++) {
      a_block.setBrightness(bright);
      a_block.setPixelColor(i, a_block.Color(g, r, b));
    }
  }else{
    for (int i = startPixel; i < startPixel + 8; i++) {
      a_block.setBrightness(bright);
      a_block.setPixelColor(i, a_block.Color(g, r, b));
    }
  }
  a_block.show();
}

void turnOnSubpattern(int subpattern) {
  int startPixel = (subpattern - 1) * 2;
  a_block.clear();
  
  if(lastFloor == 1){
    if(subpattern == 3){
      for (int i = startPixel; i < startPixel + 3; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }else if(subpattern == 4){
      a_block.setBrightness(bright);
      a_block.setPixelColor(7, a_block.Color(g, r, b));
    }else{
      for (int i = startPixel; i < startPixel + 2; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
  
      }
    }
    a_block.show();
  }

  if(lastFloor == 2){
    if(subpattern == 3){
      for (int i = startPixel + 8; i < startPixel + 3 + 8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }else if(subpattern == 4){
      a_block.setBrightness(bright);
      a_block.setPixelColor(7+8, a_block.Color(g, r, b));
    }else{
      for (int i = startPixel +8; i < startPixel + 2 +8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }
    a_block.show();
  }

  if(lastFloor == 3){
    if(subpattern == 3){
      for (int i = startPixel + 8 + 8; i < startPixel + 3 + 8 + 8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }else if(subpattern == 4){
      a_block.setBrightness(bright);
      a_block.setPixelColor(7+8+8, a_block.Color(g, r, b));
    }else{
      for (int i = startPixel + 8 + 8; i < startPixel + 2 + 8 + 8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }
    a_block.show();
  }

  if(lastFloor == 4){
    if(subpattern == 3){
      for (int i = startPixel + 8 + 8 + 8; i < startPixel + 3 + 8 + 8 + 8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }else if(subpattern == 4){
      a_block.setBrightness(bright);
      a_block.setPixelColor(7+8+8+8, a_block.Color(g, r, b));
    }else{
      for (int i = startPixel + 8 + 8 + 8; i < startPixel + 2 + 8 + 8 + 8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }
    a_block.show();
  }

  if(lastFloor == 5){
    if(subpattern == 3){
      for (int i = startPixel+8+8+8+8; i < startPixel+3+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }else if(subpattern == 4){
      a_block.setBrightness(bright);
      a_block.setPixelColor(7+8+8+8+8, a_block.Color(g, r, b));
    }else{
      for (int i = startPixel+8+8+8+8; i < startPixel+2+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }
    a_block.show();
  }
  
  if(lastFloor == 6){
    if(subpattern == 3){
      for (int i = startPixel+8+8+8+8+8; i < startPixel+3+8+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }else if(subpattern == 4){
      a_block.setBrightness(bright);
      a_block.setPixelColor(7+8+8+8+8+8, a_block.Color(g, r, b));
    }else{
      for (int i = startPixel+8+8+8+8+8; i < startPixel+2+8+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }
    a_block.show();
  }

  if(lastFloor == 7){
    if(subpattern == 3){
      for (int i = startPixel+8+8+8+8+8+8; i < startPixel+3+8+8+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }else if(subpattern == 4){
      a_block.setBrightness(bright);
      a_block.setPixelColor(7+8+8+8+8+8+8, a_block.Color(g, r, b));
    }else{
      for (int i = startPixel+8+8+8+8+8+8; i < startPixel+2+8+8+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }
    a_block.show();
  }

  if(lastFloor == 8){
    if(subpattern == 3){
      for (int i = startPixel+8+8+8+8+8+8+8; i < startPixel+3+8+8+8+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }else if(subpattern == 4){
      a_block.setBrightness(bright);
      a_block.setPixelColor(7+8+8+8+8+8+8+8, a_block.Color(g, r, b));
    }else{
      for (int i = startPixel+8+8+8+8+8+8+8; i < startPixel+2+8+8+8+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }
    a_block.show();
  }

  if(lastFloor == 9){
    if(subpattern == 3){
      for (int i = startPixel+8+8+8+8+8+8+8+8; i < startPixel+3+8+8+8+8+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }else if(subpattern == 4){
      a_block.setBrightness(bright);
      a_block.setPixelColor(7+8+8+8+8+8+8+8+8, a_block.Color(g, r, b));
    }else{
      for (int i = startPixel+8+8+8+8+8+8+8+8; i < startPixel+2+8+8+8+8+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }
    a_block.show();
  }

  if(lastFloor == 10){
    if(subpattern == 3){
      for (int i = startPixel+8+8+8+8+8+8+8+8+8; i < startPixel+3+8+8+8+8+8+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }else if(subpattern == 4){
      a_block.setBrightness(bright);
      a_block.setPixelColor(7+8+8+8+8+8+8+8+8+8, a_block.Color(g, r, b));
    }else{
      for (int i = startPixel+8+8+8+8+8+8+8+8+8; i < startPixel+2+8+8+8+8+8+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }
    a_block.show();
  }

  if(lastFloor == 11){
    if(subpattern == 3){
      a_block.clear();
      for (int i = startPixel+8+8+8+8+8+8+8+8+8+8; i < startPixel+3+8+8+8+8+8+8+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
      for (int i = startPixel+8+8+8+8+8+8+8+8+8+8+8; i < startPixel+3+8+8+8+8+8+8+8+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }else if(subpattern == 4){
      a_block.setBrightness(bright);
      a_block.setPixelColor(7+8+8+8+8+8+8+8+8+8+8, a_block.Color(g, r, b));
      a_block.setBrightness(bright);
      a_block.setPixelColor(7+8+8+8+8+8+8+8+8+8+8+8, a_block.Color(g, r, b));
    }else if(subpattern == 2){
      for (int i = startPixel+8+8+8+8+8+8+8+8+8+8+8; i < startPixel+8+8+8+8+8+8+8+8+8+8+8+2; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
      for (int i = startPixel+8+8+8+8+8+8+8+8+8+8; i < startPixel+8+8+8+8+8+8+8+8+8+8+2; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }else if(subpattern == 1){
      for (int i = startPixel+8+8+8+8+8+8+8+8+8+8+8; i < startPixel+8+8+8+8+8+8+8+8+8+8+8+2; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
      for (int i = startPixel+8+8+8+8+8+8+8+8+8+8; i < startPixel+8+8+8+8+8+8+8+8+8+8+2; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }
    a_block.show();
  }

  if(lastFloor == 12){
    if(subpattern == 3){
      for (int i = startPixel+8+8+8+8+8+8+8+8+8+8+8; i < startPixel+3+8+8+8+8+8+8+8+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }else if(subpattern == 4){
      a_block.setBrightness(bright);
      a_block.setPixelColor(7+8+8+8+8+8+8+8+8+8+8+8, a_block.Color(g, r, b));
    }else{
      for (int i = startPixel+8+8+8+8+8+8+8+8+8+8+8; i < startPixel+2+8+8+8+8+8+8+8+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }
    a_block.show();
  }

  if(lastFloor == 13){
    if(subpattern == 3){
      for (int i = startPixel+8+8+8+8+8+8+8+8+8+8+8+8; i < startPixel+3+8+8+8+8+8+8+8+8+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }else if(subpattern == 4){
      a_block.setBrightness(bright);
      a_block.setPixelColor(7+8+8+8+8+8+8+8+8+8+8+8+8, a_block.Color(g, r, b));
    }else{
      for (int i = startPixel+8+8+8+8+8+8+8+8+8+8+8+8; i < startPixel+2+8+8+8+8+8+8+8+8+8+8+8+8; i++) {
        a_block.setBrightness(bright);
        a_block.setPixelColor(i, a_block.Color(g, r, b));
      }
    }
    a_block.show();
  }
}

void turnOffRandomLed() {
  int randomPixel = getRandomPixel(0, 103, -1);
  a_block.setBrightness(bright);
  a_block.setPixelColor(randomPixel, a_block.Color(0, 0, 0));
  a_block.show();
}

void randomPattern() {
  for(int i = 0; i < 104; i++){
    if(i % 3 == 0){
      a_block.setBrightness(bright);
      a_block.setPixelColor(i, a_block.Color(g, r, b));
      a_block.show();
    }else{
      a_block.setBrightness(bright);
      a_block.setPixelColor(i, a_block.Color(0, 0, 0));
      a_block.show();
    }
  }

  for (int i = 0; i < 3; i++) {
    int randomPixel = getRandomPixel((i == 0) ? side1Start : side2Start, (i == 0) ? side1End : side2End, lastRandomPixels[i]);
    
    a_block.setBrightness(bright);
    a_block.setPixelColor(randomPixel, a_block.Color(g, r, b));
    a_block.show();

    lastRandomPixels[i] = randomPixel; // Сохраняем значение последнего включенного светодиода
    turnOffRandomLed();
  }

}


void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void loop() {
  // Make HTTP GET request to retrieve data
  HTTPClient https;
  String url = "https://el-nasi-default-rtdb.asia-southeast1.firebasedatabase.app/value.json";
  
  if (https.begin(url)) {  // HTTPS
    int httpCode = https.GET();
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        // Parse JSON response
        DynamicJsonDocument jsonDocument(1024);
        DeserializationError error = deserializeJson(jsonDocument, https.getString());
        if (error) {
          Serial.print("deserializeJson() failed: ");
          Serial.println(error.c_str());
        } else {
          // Access the value data
          String value = jsonDocument["value"];
          Serial.print("Value: ");
          Serial.println(value);
          if (value == "v") {
            turnOnAllLeds();
          } else if (value == "_") {
            turnOffAllLeds();
          } else if (value == "D") {
            randomPattern();
          } else if (value >= "a" && value <= "m") {
            turnOnFloor(value[0]);
            if(value == "a"){
              lastFloor = 1;
            }else if(value == "b"){
              lastFloor = 2;
            }else if(value == "c"){
              lastFloor = 3;
            }else if(value == "d"){
              lastFloor = 4;
            }else if(value == "e"){
              lastFloor = 5;
            }else if(value == "f"){
              lastFloor = 6;
            }else if(value == "g"){
              lastFloor = 7;
            }else if(value == "h"){
              lastFloor = 8;
            }else if(value == "i"){
              lastFloor = 9;
            }else if(value == "g"){
              lastFloor = 10;
            }else if(value == "k"){
              lastFloor = 11;
            }else if(value == "l"){
              lastFloor = 12;
            }else if(value == "m"){
              lastFloor = 13;
            }
          }else if(value >= "1" && value <= "4"){
            turnOnSubpattern(value.toInt());
          } else if(value == "P"){
            for(int i = 0; i < 50; i++){
              pod.setBrightness(bright);
              pod.setPixelColor(i, pod.Color(255, 255, 255));
              pod.show();
            }
          }else if(value == "p"){
            for(int i = 0; i < 50; i++){
              pod.setBrightness(bright);
              pod.setPixelColor(i, pod.Color(0, 0, 0));
              pod.show();
            }
          }
        }
      } else {
        Serial.print("HTTP request failed with error code: ");
        Serial.println(httpCode);
      }
    } else {
      Serial.println("HTTP request failed");
    }
    
    https.end(); // Close connection
  } else {
    Serial.println("Unable to connect");
  }

  // Wait before making the next request
}