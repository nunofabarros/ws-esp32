#ifndef WS_COMMON
#define WS_COMMON

#define BAUD_RATE 115200
#define JSON_BUFFER 1024

#define UPDATE_INTERVAL 2000

// Wi-Fi Settings 
// SSID and password should be define on settings.conf file see settings.conf.example

#ifndef WIFI_SSID
#define WIFI_SSID "MY SSID"
#endif

#ifndef WIFI_PASS
#define WIFI_PASS "my password"
#endif

#define WIFI_MAX_ATTEMPTS 50

// Web server settings

#define HTTP_PORT 80

// LCD Settings

#define LCD_RST 19
#define LCD_EN 23
#define LCD_D4 18
#define LCD_D5 17
#define LCD_D6 16
#define LCD_D7 15

// Sensor Setting

#define SENSOR_PIN 27
#define SENSOR_TYPE DHT22
#define SENSOR_TEMPERATURE_OFFSET 0.0f
#define SENSOR_HUMIDITY_OFFSET 0.0f

#endif
