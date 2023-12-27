#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

const char* ssid = "DANBAYNUR";
const char* password = "05021983god";

long demoAmount;

Adafruit_NeoPixel a_block = Adafruit_NeoPixel(500, 12, NEO_RGB + NEO_KHZ800);
int bright = 255;

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

      if (value == "_") {
        for(int i = 0; i < 300; i++){
          a_block.setBrightness(bright);
          a_block.setPixelColor(i, a_block.Color(0, 0, 0));
          a_block.show();
        }
      } else if (value == "D") {
        for(int i = 0; i < 300; i++){
          if ( i % 5 == 0 ) {
            a_block.setBrightness(bright);
            a_block.setPixelColor(i, a_block.Color(255, 255, 255));
            a_block.show();
          }
        }
      } else if (value == "v") {
        for(int i = 0; i < 300; i++){
          a_block.setBrightness(bright);
          a_block.setPixelColor(i, a_block.Color(255, 255, 255));
          a_block.show();
        }
      }
    }
  } else {
    Serial.println("HTTP request failed");
  }

  // Освобождение ресурсов
  http.end();

  // Пауза между запросами
  delay(1);
}
