#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <ESPmDNS.h>
#include "common.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;

AsyncWebServer server(HTTP_PORT);
LiquidCrystal lcd = LiquidCrystal(LCD_RST, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
DHT dht(SENSOR_PIN, SENSOR_TYPE);

static float humidity = MAXFLOAT;
static float temperature = MAXFLOAT;

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setup() {
    Serial.begin(BAUD_RATE);
    lcd.begin(16,2);
    dht.begin();
    WiFi.mode(WIFI_STA);
    WiFi.setHostname("ws-esp");
    
    if(!MDNS.begin("ws-esp")) {
      Serial.printf("Error starting mDNS\n");
    } else {
      if (MDNS.addService("ws-station","tcp",80)) {
        Serial.printf("mDNS service ws-station started\n");
      }
    }
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        AsyncResponseStream *response = request->beginResponseStream("application/json");
        DynamicJsonDocument json(JSON_BUFFER);
        json["status"] = "ok";
        json["ip"] = WiFi.localIP().toString();
        json["humidity"] = humidity;
        json["temperature"] = temperature;
        serializeJsonPretty(json, *response);
        request->send(response);
    });

    server.onNotFound(notFound);

    server.begin();

}

int connection_attempts = 0;

void loop() {
    lcd.clear();
    lcd.setCursor(0,0);
    humidity = dht.readHumidity() + SENSOR_HUMIDITY_OFFSET;
    temperature = dht.readTemperature() + SENSOR_TEMPERATURE_OFFSET;

  if (isnan(humidity) || isnan(temperature)) {
    Serial.print("Failed to read DHT sensor!");
    return;
  }

  if (WiFi.status() != WL_CONNECTED) {
    connection_attempts++;
    if (connection_attempts > WIFI_MAX_ATTEMPTS) {
        Serial.printf("Wifi connection to SSID: %s failed\n", ssid);
        Serial.printf("Reseting WS-ESP");
        lcd.print("Reseting WS-ESP");
        ESP.restart();
    }
    lcd.print("Connecting...");
    Serial.printf("WiFi Status: %d\n", WiFi.status());
    Serial.printf("WiFi MAC: %s\n", WiFi.macAddress().c_str());
    WiFi.begin(ssid, password);
  } else {
    connection_attempts = 0;
    lcd.printf("IP:%s",WiFi.localIP().toString().c_str());
  }

  lcd.setCursor(0,1);
  lcd.printf("%.1fC %.1f%% Hum.",temperature, humidity);
  delay(UPDATE_INTERVAL);
    
}