#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

const char* ssid = "WiFi name";
const char* password = "WiFi password";

long demoAmount;

Adafruit_NeoPixel a_block = Adafruit_NeoPixel(104, 12, NEO_RGB + NEO_KHZ800);
int bright = 255;
int r = 255;
int g = 157;
int b = 15;

long lastFloor;

void setup() {
  Serial.begin(115200);
  a_block.begin();

  // Подключение к Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  pinMode(12, OUTPUT);
}

void loop() {
  // Создание объекта HTTPClient
  HTTPClient http;

  // Формирование URL-адреса с параметрами
  String url = "https://el-nasip-default-rtdb.asia-southeast1.firebasedatabase.app/value.json";

  // Установка URL-адреса для запроса
  http.begin(url);

  // Отправка GET-запроса
  int httpCode = http.GET();
  if (httpCode > 0) {
    // Получение ответа в виде JSON
    DynamicJsonDocument doc(1024); // Размер документа может быть изменен в зависимости от ваших потребностей
    DeserializationError error = deserializeJson(doc, http.getString());

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
    } else {
      String value = doc["value"].as<String>();
      Serial.println(value);

      switch (value) {
        case 'v':
          a_block.clear();
          for (int i = 0; i < 104; i++) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(i, a_block.Color(g, r, b));
            a_block.show();
          }
          break;
        
        case '_':
          a_block.clear();
          for (int i = 0; i < 104; i++) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(i, a_block.Color(0, 0, 0));
            a_block.show();
          }
          break;

        case 'D':
          a_block.clear();
          for (int i = 0; i < 104; i++) {
            if (i % 2 == 0) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }
          break;

        case '1' :
          lastFloor = 1;
          for (int i = 0; i < 8; i++) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(i, a_block.Color(g, r, b));
            a_block.show();
          }
          break;
        
        case '2' :
          lastFloor = 2;
          for (int i = 8; i < 16; i++) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(i, a_block.Color(g, r, b));
            a_block.show();
          }
          break;

        case '3' :
          lastFloor = 3;
          for (int i = 16; i < 24; i++) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(i, a_block.Color(g, r, b));
            a_block.show();
          }
          break;

        case '4' :
          lastFloor = 4;
          for (int i = 24; i < 32; i++) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(i, a_block.Color(g, r, b));
            a_block.show();
          }
          break;

        case '5' :
          lastFloor = 5;
          for (int i = 32; i < 40; i++) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(i, a_block.Color(g, r, b));
            a_block.show();
          }
          break;
        
        case '6' :
          lastFloor = 6;
          for (int i = 40; i < 48; i++) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(i, a_block.Color(g, r, b));
            a_block.show();
          }
          break;

        case '7' :
          lastFloor = 7;
          for (int i = 48; i < 56; i++) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(i, a_block.Color(g, r, b));
            a_block.show();
          }
          break;

        case '8' :
          lastFloor = 8;
          for (int i = 56; i < 64; i++) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(i, a_block.Color(g, r, b));
            a_block.show();
          }
          break;

        case '9' :
          lastFloor = 9;
          for (int i = 64; i < 72; i++) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(i, a_block.Color(g, r, b));
            a_block.show();
          }
          break;

        case '10' :
          lastFloor = 10;
          for (int i = 72; i < 80; i++) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(i, a_block.Color(g, r, b));
            a_block.show();
          }
          break;

        case '11' :
          lastFloor = 11;
          for (int i = 80; i < 88; i++) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(i, a_block.Color(g, r, b));
            a_block.show();
          }
          break;

        case '12' :
          lastFloor = 12;
          for (int i = 88; i < 96; i++) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(i, a_block.Color(g, r, b));
            a_block.show();
          }
          break;

        case '13' :
          lastFloor = 13;
          for (int i = 96; i < 104; i++) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(i, a_block.Color(g, r, b));
            a_block.show();
          }
          break;

        case 'a' :
          if(lastFloor == 1) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(1-1, a_block.Color(g, r, b));
            a_block.show();
          }else if(lastFloor == 2) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(1-1+8, a_block.Color(g, r, b));
            a_block.show();
          }else if(lastFloor == 3) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(1-1+8+8, a_block.Color(g, r, b));
            a_block.show();
          }else if(lastFloor == 4) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(1-1+8+8+8, a_block.Color(g, r, b));
            a_block.show();
          }else if(lastFloor == 5) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(1-1+8+8+8+8, a_block.Color(g, r, b));
            a_block.show();
          }else if(lastFloor == 6) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(1-1+8+8+8+8+8, a_block.Color(g, r, b));
            a_block.show();
          }else if(lastFloor == 7) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(1-1+8+8+8+8+8+8, a_block.Color(g, r, b));
            a_block.show();
          }else if(lastFloor == 8) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(1-1+8+8+8+8+8+8+8, a_block.Color(g, r, b));
            a_block.show();
          }else if(lastFloor == 9) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(1-1+8+8+8+8+8+8+8+8, a_block.Color(g, r, b));
            a_block.show();
          }else if(lastFloor == 10) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(1-1+8+8+8+8+8+8+8+8+8, a_block.Color(g, r, b));
            a_block.show();
          }else if(lastFloor == 11) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(1-1+8+8+8+8+8+8+8+8+8+8, a_block.Color(g, r, b));
            a_block.show();
          }else if(lastFloor == 12) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(1-1+8+8+8+8+8+8+8+8+8+8+8, a_block.Color(g, r, b));
            a_block.show();
          }else if(lastFloor == 13) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(1-1+8+8+8+8+8+8+8+8+8+8+8+8, a_block.Color(g, r, b));
            a_block.show();
          }
          break;
        
        case 'b' :
          if(lastFloor == 1) {
            for(int i = 4; i < 6; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 2) {
            for(int i = 4+8; i < 6+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 3) {
            for(int i = 4+8+8; i < 6+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 4) {
            for(int i = 4+8+8+8; i < 6+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 5) {
            for(int i = 4+8+8+8+8; i < 6+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 6) {
            for(int i = 4+8+8+8+8+8; i < 6+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 7) {
            for(int i = 4+8+8+8+8+8+8; i < 6+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 8) {
            for(int i = 4+8+8+8+8+8+8+8; i < 6+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 9) {
            for(int i = 4+8+8+8+8+8+8+8+8; i < 6+8+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 10) {
            for(int i = 4+8+8+8+8+8+8+8+8+8; i < 6+8+8+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 11) {
            for(int i = 4+8+8+8+8+8+8+8+8+8+8; i < 6+8+8+8+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 12) {
            for(int i = 4+8+8+8+8+8+8+8+8+8+8+8; i < 6+8+8+8+8+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 13) {
            for(int i = 4+8+8+8+8+8+8+8+8+8+8+8+8; i < 6+8+8+8+8+8+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }
          break;

        case 'c' :
          if(lastFloor == 1) {
            for(int i = 6; i < 8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 2) {
            for(int i = 6+8; i < 8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 3) {
            for(int i = 6+8+8; i < 8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 4) {
            for(int i = 6+8+8+8; i < 8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 5) {
            for(int i = 6+8+8+8+8; i < 8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 6) {
            for(int i = 6+8+8+8+8+8; i < 8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 7) {
            for(int i = 6+8+8+8+8+8+8; i < 8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 8) {
            for(int i = 6+8+8+8+8+8+8+8; i < 8+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 9) {
            for(int i = 6+8+8+8+8+8+8+8+8; i < 8+8+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 10) {
            for(int i = 6+8+8+8+8+8+8+8+8+8; i < 8+8+8+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 11) {
            for(int i = 6+8+8+8+8+8+8+8+8+8+8; i < 8+8+8+8+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 12) {
            for(int i = 6+8+8+8+8+8+8+8+8+8+8+8; i < 8+8+8+8+8+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 13) {
            for(int i = 6+8+8+8+8+8+8+8+8+8+8+8+8; i < 8+8+8+8+8+8+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }
          break;

        case 'd' :
          if(lastFloor == 1) {
            for(int i = 1; i < 4; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 2) {
            for(int i = 1+8; i < 4+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 3) {
            for(int i = 1+8+8; i < 4+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 4) {
            for(int i = 1+8+8+8; i < 4+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 5) {
            for(int i = 1+8+8+8+8; i < 4+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 6) {
            for(int i = 1+8+8+8+8+8; i < 4+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 7) {
            for(int i = 1+8+8+8+8+8+8; i < 4+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 8) {
            for(int i = 1+8+8+8+8+8+8+8; i < 4+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 9) {
            for(int i = 1+8+8+8+8+8+8+8+8; i < 4+8+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 10) {
            for(int i = 1+8+8+8+8+8+8+8+8+8; i < 4+8+8+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 11) {
            for(int i = 1+8+8+8+8+8+8+8+8+8+8; i < 4+8+8+8+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 12) {
            for(int i = 1+8+8+8+8+8+8+8+8+8+8+8; i < 4+8+8+8+8+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }else if(lastFloor == 13) {
            for(int i = 1+8+8+8+8+8+8+8+8+8+8+8+8; i < 4+8+8+8+8+8+8+8+8+8+8+8+8; i++) {
              a_block.setBrightness(bright);
              a_block.setPixelColor(i, a_block.Color(g, r, b));
              a_block.show();
            }
          }
          break;
      }
  } else {
    Serial.println("HTTP request failed");
  }

  // Освобождение ресурсов
  http.end();

  // Пауза между запросами
  delay(1);
}
