#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "common.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;

const int count_interval = 2000;

static unsigned long count = 0; 

AsyncWebServer server(HTTP_PORT);

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setup() {
    Serial.begin(BAUD_RATE);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if(WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("Wifi connection to SSID: %s failed\n", ssid);
        return;
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello, world");
    });

    server.onNotFound(notFound);

    server.begin();

}

void loop() {
    count++;
    Serial.printf("Value: %lu\n",count);
    delay(count_interval);
    
}