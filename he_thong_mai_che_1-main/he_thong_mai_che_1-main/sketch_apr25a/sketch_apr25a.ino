#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <SPIFFS.h>

const char* ssid = "Realme";
const char* password = "123456789@";
const char* serverUrl = "http://192.168.165.221:5000/data";  // IP của server Flask

const int rainSensorPin = 34;  // Cảm biến mưa (chân analog)
const int lightSensorPin = 35; // Cảm biến ánh sáng (chân analog)

const int motorPin1 = 14;     // Chân điều khiển motor (GPIO14)
const int motorPin2 = 27;     // Chân điều khiển motor (GPIO27)

// Khởi tạo WiFi và kết nối
void setup() {
  Serial.begin(115200);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Thử gửi dữ liệu lên server
  sendDataToServer(true, false, "open");
}

// Hàm gửi dữ liệu lên server Flask
void sendDataToServer(bool rain, bool light, String roofStatus) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<200> doc;
    doc["rain"] = analogRead(rainSensorPin);
    doc["light"] = analogRead(lightSensorPin);
    doc["roof"] = roofStatus;
    doc["timestamp"] = millis();

    String jsonData;
    serializeJson(doc, jsonData);

    int httpResponseCode = http.POST(jsonData);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    http.end();
  }
}

// Hàm mở mái che
void openRoof() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  sendDataToServer(true, false, "open");
}

// Hàm đóng mái che
void closeRoof() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  sendDataToServer(false, false, "closed");
}

void loop() {
  int rainValue = analogRead(rainSensorPin);
  int lightValue = analogRead(lightSensorPin);

  bool isRaining = rainValue < 3000;     // tùy chỉnh ngưỡng mưa
  bool isLight = lightValue > 1500;      // tùy chỉnh ngưỡng ánh sáng

  String roofStatus = "closed";
  if (isRaining || isLight) {
    openRoof();
    roofStatus = "open";
  } else {
    closeRoof();
    roofStatus = "closed";
  }

  sendDataToServer(isRaining, isLight, roofStatus);

  delay(10000);  // Gửi dữ liệu mỗi 10 giây
}
